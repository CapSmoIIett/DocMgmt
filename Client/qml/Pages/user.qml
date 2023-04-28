
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
        id: labelUsername
        anchors.top: top.bottom
        anchors.left: parent.left
        anchors.margins: 15

        text: app.userName;
    }

    MenuSeparator {
        id: separator
        anchors.top: labelUsername.bottom
        anchors.left: parent.left
        anchors.topMargin: 15
        anchors.bottomMargin: 15
        width: parent.width
    }

    Label {
        id: officeLabel
        anchors.top: separator.bottom
        anchors.left: parent.left
        anchors.margins: 15

        text: "Office: "
    }

    Label {
        anchors.top: separator.bottom
        anchors.left: officeLabel.right
        anchors.margins: 15

        text: app.office
    }

    Label {
        id: rightLabel
        anchors.top: officeLabel.bottom
        anchors.left: parent.left
        anchors.margins: 15

        text: "Right: "
    }

    Label {
        anchors.top: officeLabel.bottom
        anchors.left: rightLabel.right
        anchors.margins: 15

        text: app.right
    }
}
