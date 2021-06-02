import QtQuick 2.0
import Game 1.0

GridView {
    id: root

    cellHeight: height/root.model.dimention
    cellWidth:  width/root.model.dimention

    model: GameBoardModel {

    }

    delegate : Item {
        id: _backgroundDelegate
        width: root.cellWidth
        height: root.cellHeight

        visible: display !== root.model.hiddenElementValue

        Tile {
            displayText: display
            anchors.fill: _backgroundDelegate // Заполнить
            anchors.margins: 5
            MouseArea { // Отрабатывает нажатие
                anchors.fill: parent
                onClicked: {
                    root.model.move(index);
                }
            }
        }
    }
}
