#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <QAbstractListModel>
#include <vector>
#include <tuple>
#include <algorithm>
#include <chrono>
#include <random>

class GameBoard : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int dimention READ dimention CONSTANT) // геттер после READ
    Q_PROPERTY(int hiddenElementValue READ boardSize CONSTANT)
public:
    static constexpr size_t defaultPuzzleDimension{4};
    using Position = std::pair<size_t, size_t>;

    GameBoard(const size_t boardDimension = defaultPuzzleDimension,
                QObject *parent = NULL);

    struct Tile {
        size_t value{};
        Tile& operator =(const size_t newValue) {
            value = newValue;
            return *this;
        }
        bool operator ==(const size_t other) {
            return other == value;
        }

    };

    int rowCount(const QModelIndex &parent = QModelIndex {}) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    size_t dimention() const;
    size_t boardSize() const;

    Q_INVOKABLE bool move(int index);


private:
    void shuffle();
    bool isPositionValid(const size_t position)const;
    Position getRowCol(const size_t index) const;

    std::vector <Tile> m_rawBoard;
    const size_t m_dimention;
    const size_t m_boardSize;
};

#endif // GAMEBOARD_H
