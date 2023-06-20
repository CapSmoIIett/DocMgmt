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
        color: Material.color(Material.Purple)
        height: parent.height / 6
        width: parent.width
        anchors.margins: 0
    }

    /*Label {
        id: labelName
        anchors.top: top.bottom
        anchors.left: parent.left
        anchors.margins: 15

        text: officePage.name;
    }*/
    TextInput {
        id: labelName

        anchors.top: top.bottom
        anchors.left: parent.left
        anchors.margins: 15
        text: officePage.name

        onTextEdited: {
            save.enabled = true
        }
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

        anchors.leftMargin: 45

        rows: 1
        columns: 4
        flow: GridLayout.TopToBottom
        anchors.top: separator.bottom
        width: parent.width

        Label {
            text: "Address: "
        }

        Rectangle {
            width: parent.width / 2
            height: 25
            border.color: "grey"
            border.width: 1

            TextInput{
                id: inputAddress
                text: officePage.address
                width: parent.width / 2

                onTextEdited: {
                    save.enabled = true
                }
            }
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
            //console.log(accessLvl.currentIndex)
            officePage.name = labelName.text
            officePage.address = inputAddress.text

            officePage.uploadData()
        }
    }

    Component.onCompleted: {
        //rightPage.loadRightRequest(0)
    }
}
