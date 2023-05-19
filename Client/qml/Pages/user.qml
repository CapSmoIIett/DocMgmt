
import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Controls.Universal
import QtCharts

import Qt.labs.folderlistmodel

Pane {
    anchors.fill: parent

    Row {
    anchors.fill: parent

    Rectangle {
        width: (app.id === userPage.id) ? parent.width : parent.width / 2
        height: parent.height
        id: left


    Rectangle {
        id: top
        color: Material.color(Material.Purple)
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

        //messenger.clear()
        //messenger.clear()
        //app.uploadMessages(userPage.id)


    }
    }


    Rectangle {
        id: chat

        visible: app.id !== userPage.id

        width: parent.width / 2
        height: parent.height

        ListView {
            //anchors.top: parent
            rotation:180
            anchors.fill: parent
            anchors.bottomMargin:  line.height + 30
            anchors.rightMargin: 25
            anchors.margins: 15
            anchors.leftMargin: 30
            //Layout.fillHeight: true
            //anchors.left: chat.left
            //anchors.top: chat.top

            //color: "green"
            //verticalLayoutDirection: ListView.BottomToTop

            model: messenger
            //model:
                ListModel {
                ListElement{
                    display: "name1"
                    user: 0
                }
                ListElement{
                    display: "name2"
                    user: 1
                }
                ListElement{
                    display: "name1"
                    user: 0
                }
            }

            delegate: Rectangle {
                rotation:180
                width: parent.width
                height: 30;
                anchors.leftMargin: 40//user === 0 ? 0 : 20

                color: "red"//"DDDDDD"
                border.width: 1
                //text:  model.display
                Label {
                    text: display
                    anchors.centerIn: parent
                    horizontalAlignment: Qt.AlignHCenter
                    //anchors.
                }
            }
        }

        RowLayout {
            id: line
            Layout.preferredHeight: 40
            width: parent.width
            anchors.bottom: chat.bottom
            anchors.margins: 15

            TextField {
                id:text
                enabled: true
                Layout.fillWidth: true
            }
            Button {
                text: "Send"
                onClicked: {
                    //userPage.addMessage(text.text);

                    messenger.addMessage(text.text)
                    app.sendMessage(text.text, userPage.id)
                    text.text = ""

                    //messenger.update()
                    //Qt.inputMethod.reset(text)
                }
            }

            Component.onCompleted: {
                app.uploadMessages(userPage.id)
            }
    }

    }
}
}
