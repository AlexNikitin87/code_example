import QtQuick 2.6
import QtQuick.Window 2.2

Window {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("15Puzzle")

    GameBoard {
        anchors.fill: parent
    }
}
