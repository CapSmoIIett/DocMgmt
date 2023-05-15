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

    GridLayout {
        id: grid
        rows: 2
        columns: 6
        flow: GridLayout.TopToBottom
        anchors.top: separator.bottom
        width: parent.width


        Label {
            id: accessLvlLabel
            anchors.margins: 15

            text: "Right: "
        }

        ComboBox {
            id: accessLvl
            anchors.margins: 15
            width: 100
            //Layout.fillWidth: true

            model: 8

            onEditTextChanged: save.enabled = true

        }
    }

    Button {
        id: save
        anchors.top: grid.bottom
        anchors.margins: 15
        Layout.fillWidth: true
        enabled: false

        text: "Save Changes"

        onClicked: {
            console.log(accessLvl.currentIndex)
            rightPage.lvl = accessLvl.currentIndex

            rightPage.uploadData()
        }
    }

    Component.onCompleted: {
        //rightPage.loadRightRequest(0)
    }
}
