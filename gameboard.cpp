#include "gameboard.h"

namespace
{
    bool isAdjacent(const GameBoard::Position f, const GameBoard::Position s) {
        if(f == s) {
            return false;
        }

        const auto calcDistance = [](const size_t pos1, size_t pos2) {
            int distance = static_cast<int>(pos1);
            distance -= static_cast<int>(pos2);
            distance = std::abs(distance);
            return distance;
        };

        bool result {false};

        if(f.first == s.first) { // находятся на одной стороке
            int distance = calcDistance(f.second, s.second);
            if(distance == 1) {
                result = true;
            }
        }
        else if(f.second == s.second) {
            int distance = calcDistance(f.first, s.first);
            if(distance == 1) {
                result = true;
            }
        }

        return result;
    }
}

GameBoard::GameBoard(const size_t boardDimension, QObject *parent)
    : QAbstractListModel {parent},
      m_dimention {boardDimension},
      m_boardSize {m_dimention*m_dimention} // важна последователность
{
    m_rawBoard.resize(m_boardSize);
    std::iota( m_rawBoard.begin(), m_rawBoard.end(), 1);
    shuffle();

}

int GameBoard::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_rawBoard.size();
}

QVariant GameBoard::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || role != Qt::DisplayRole) {
        return QVariant{};
    }

    const int rowIndex {index.row()};

    if(!isPositionValid(rowIndex)) {
        return {};
    }

    return QVariant::fromValue(static_cast<uint>(m_rawBoard[rowIndex].value));
}

void GameBoard::shuffle()
{
    static auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 generator(seed);

    std::shuffle(m_rawBoard.begin(), m_rawBoard.end(), generator);
}

bool GameBoard::isPositionValid(const size_t position) const
{
    return position < m_boardSize;
}

size_t GameBoard::boardSize() const
{
    return m_boardSize;
}

bool GameBoard::move(int index)
{
    if(!isPositionValid(static_cast<size_t> (index))) {
        return false;
    }


    const Position elementPosition {getRowCol(index)};

    auto hiddenElementIterator = std::find(m_rawBoard.begin(), m_rawBoard.end(),
                                           boardSize()); // hidden elemnt
    Q_ASSERT (hiddenElementIterator != m_rawBoard.end());

    Position hiddenElementPosition {getRowCol(std::distance(m_rawBoard.begin(), hiddenElementIterator))};

    if(!isAdjacent(elementPosition, hiddenElementPosition)) {
        return false;
    }

    std::swap(hiddenElementIterator->value, m_rawBoard[index].value);

    emit dataChanged(createIndex(0,0), createIndex(m_boardSize, 0));

    return true;
}

GameBoard::Position GameBoard::getRowCol(const size_t index) const
{
    Q_ASSERT(m_dimention > 0);

    size_t row = index / m_dimention;
    size_t column = index % m_dimention;

    return std::make_pair(row, column);
}

size_t GameBoard::dimention() const
{
    return m_dimention;
}
