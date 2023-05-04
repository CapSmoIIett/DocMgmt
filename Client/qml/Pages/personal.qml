import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Qt.labs.qmlmodels


//import PersonalModel 1.0


Rectangle {
    anchors.fill: parent
    id: main

    signal loadUserPage(int userID)

    ToolBar {
        id: toolBar
        //anchors.top: parent.top
        //anchors.left: parent.left
        width: parent.width
        height: updateButton.height + 10


        RowLayout {
            anchors.fill: parent

            ToolButton {
                id: updateButton

                text: "Update"
                onClicked: {
                console.log("Update")
                app.usersListRequest()
                }
            }

            Label {
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }

            ToolButton {
                text: 'Add user'
                onClicked: {
                    console.log("Add user")
                    app.addUserRequest()
                }
            }
        }
    }
    //*/


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
    //*/

    TableView {
        id: table

        anchors.fill: parent
        anchors.topMargin: toolBar.height + horizontalHeader.height
        clip: true


        columnWidthProvider: function (column) {
            return table.width / 3//table.model.columnCount();
        }

        onWidthChanged: table.forceLayout()

        model: personalTableModel

        delegate: Rectangle {
            implicitWidth: table.columnWidthProvider(column)
            implicitHeight: 30

            color: selected ? "blue" : "lightgray"

            required property bool selected

            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton

                hoverEnabled: true

                Label {
                    text: display

                    width: parent.width
                    elide: Text.ElideRight
                    anchors.centerIn: parent
                    horizontalAlignment: Text.AlignHCenter
                }

                onClicked: {

                    if (mouse.button === Qt.RightButton)
                    {
                        console.log(row);
                        menu.curRow = row
                        menu.popup()
                    }
                    else if (mouse.button === Qt.LeftButton)
                    {
                        console.log("left");
                        console.log(row);
                        console.log(personalTableModel.getIDbyRow(row))
                        //main.loadUserPage(personalTableModel.getIDbyRow(row))
                        personalTableModel.loadUserPage(personalTableModel.getIDbyRow(row))
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
                    app.removeUserRequest(menu.curRow)
                }
            }
        }

        Component.onCompleted: {
            app.usersListRequest()
        }
    }

}
/*

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
                app.usersListRequest()
                }
            }

            Label {
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }

            ToolButton {
                text: 'Add user'
                onClicked: {
                    console.log("Add user")
                    app.addUserRequest()
                }
            }
        }
    }


    HorizontalHeaderView {
        id: horizontalHeader
        syncView: table
        anchors.left: tableView.left
        anchors.top: toolBar.bottom

        delegate: Text {
            horizontalAlignment: Text.AlignHCenter
            text:  model.display
        }
    }

    TableView {
        id: table
        anchors.top: horizontalHeader.bottom
        anchors.left: parent.left
        width: parent.width
        columnSpacing: 1
        rowSpacing: 1
        clip: true

        columnWidthProvider: function (column) {
            return table.width / table.model.columnCount();
        }

        onWidthChanged: table.forceLayout()

        model: personalTableModel

        delegate: Rectangle {
            implicitWidth: table.columnWidthProvider(column)
            implicitHeight: 50
            //border.width: 1

            Text {
                text: display
                horizontalAlignment: Text.AlignHCenter
                //verticalAlignment:  Text.AlignVCenter
                anchors.centerIn: parent
                //anchors.leftMargin: 50
                width: parent.width
                elide: Text.ElideRight

            }
        }


        Component.onCompleted: {
            app.usersListRequest()
        }

    }
}

//*/
