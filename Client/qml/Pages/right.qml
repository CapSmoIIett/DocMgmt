import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Controls.Universal
import QtCharts

import Qt.labs.folderlistmodel

Pane {
    anchors.fill: parent

    Rectangle {
        id: top
        color: "#EBD4D1"
        height: parent.height / 6
        width: parent.width
        anchors.margins: 0

    }

    Label {
        id: labelName
        anchors.top: top.bottom
        anchors.left: parent.left
        anchors.margins: 15

        text: rightPage.name;
    }

    MenuSeparator {
        id: separator
        anchors.top: labelName.bottom
        anchors.left: parent.left
        anchors.topMargin: 15
        anchors.bottomMargin: 15
        width: parent.width
    }

    Component.onCompleted: {
        //rightPage.loadRightRequest(0)
    }
}
