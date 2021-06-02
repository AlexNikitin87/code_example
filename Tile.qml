import QtQuick 2.0

Rectangle {
    id: root

    property string displayText: ""

    color: "lightgreen"

    border {
        color : "black"
        width: 2
    }

    Text {
        id: _firstText
        anchors.centerIn: root
        text: displayText
        font.pointSize: Math.min(root.width, root.height) / 3.
        font.bold: true
    }



    radius: 10
}
