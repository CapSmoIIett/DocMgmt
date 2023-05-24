import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Qt.labs.qmlmodels


Rectangle {
    anchors.fill: parent

    ToolBar {
        id: toolBar
        width: parent.width
        height: updateButton.height + 10


        RowLayout {
            anchors.fill: parent

            Label {
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                width: 30
            }

            ToolButton {
                id: updateButton

                text: "Update"
                onClicked: {
                    console.log("Update")
                    app.loadRightsRequest()
                }
            }

            Label {
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }

            ToolButton {
                text: 'Add right'
                onClicked: {
                    console.log("Add right")
                    app.addRightsRequest()
                }
            }

            Label {
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                width: 30
            }
        }
    }

   Rectangle  {
        anchors.fill: parent

        anchors.topMargin: toolBar.height + 15
        anchors.margins: 15

    HorizontalHeaderView {
        id: horizontalHeader
        syncView: table
        anchors.top: toolBar.bottom
        anchors.left: parent.left

        delegate: Rectangle {
            height: parent.height
            width: table.columnWidthProvider(column)
            color: "#CE93D8"


            Label {
                width: parent.width
                elide: Text.ElideRight
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignHCenter

                text:  model.display
                font.family: "Helvetica"
                font.weight: Font.Bold
                //font.pointSize: 20
            }
        }
    }

    TableView {
        id: table
        anchors.fill: parent
        anchors.topMargin: horizontalHeader.height
        clip: true

        columnWidthProvider: function (column) {
            return table.width / table.model.columnCount();
        }

        onWidthChanged: table.forceLayout()

        model: rightsTableModel

        delegate: Rectangle {
            implicitWidth: table.columnWidthProvider(column)
            implicitHeight: 30

            color: mouseArea.containsMouse ? "#DDDDDD" : "#FFFFFF"

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton

                hoverEnabled: true

                Label {
                    text: display
                    anchors.centerIn: parent
                }

                onClicked: {

                    if (mouse.button === Qt.RightButton)
                    {
                        menu.curRow = row
                        menu.popup()
                    }
                    else if (mouse.button === Qt.LeftButton)
                    {
                        console.log("left");
                        console.log(row);
                        console.log(rightsTableModel.getIDbyRow(row))
                        //main.loadUserPage(personalTableModel.getIDbyRow(row))

                        rightsTableModel.loadRightPage(rightsTableModel.getIDbyRow(row))
                    }
                }
            }
        }

        Menu {
            id: menu
            y: openMenuButton.height

            property int curRow

            MenuItem {
                text: 'remove'

                onClicked: {
                    //app.removeUserRequest(menu.curRow)
                }
            }
        }

        Component.onCompleted: {
            app.loadRightsRequest()
        }
    }
    }
}
