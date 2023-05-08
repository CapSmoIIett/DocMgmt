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
        }
    }

    HorizontalHeaderView {
        id: horizontalHeader
        syncView: table
        anchors.top: toolBar.bottom
        anchors.left: parent.left

        delegate: Text {
            horizontalAlignment: Text.AlignHCenter
            text:  model.display
        }
    }

    TableView {
        id: table
        anchors.fill: parent
        anchors.topMargin: toolBar.height + horizontalHeader.height
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
