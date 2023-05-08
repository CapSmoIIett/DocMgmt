
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

        text: userPage.userName;
    }

    MenuSeparator {
        id: separator
        anchors.top: labelUsername.bottom
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
            id: officeLabel
            anchors.margins: 15

            text: "Office: "
        }

        Label {
            id: rightLabel
            anchors.margins: 15

            text: "Right: "
        }

        ComboBox {
            id: offices
            anchors.margins: 15
            width: 100
            //Layout.fillWidth: true

            model: officeTableModel.getOfficeNames()

            onEditTextChanged: save.enabled = true

        }

        ComboBox {
            id: rights
            anchors.margins: 15
            width: 100
            //Layout.fillWidth: true

            model: rightsTableModel.getRightNames()

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
            userPage.office = offices.currentText
            userPage.right = rights.currentText

            userPage.uploadData()
        }
    }

    Component.onCompleted: {
        //userPage.loadUserRequest(0)
        for(var i = 0; i < offices.model.count; ++i) if (offices.model.get(i) === userPage.right)  offices.currentIndex(i)
    }


}
