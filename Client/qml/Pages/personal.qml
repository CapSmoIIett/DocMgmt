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
            Label {
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                width: 30
            }
        }
    }
    //*/

    ScrollBar {
        id: tableVerticalBar
        height: parent.height - toolBar.height - 15
        anchors.topMargin: 15

        anchors.top: toolBar.bottom
        anchors.right: parent.right
        active: tableHorizontalBar.active
        policy:ScrollBar.AlwaysOn
    }


    Rectangle {
        anchors.fill: parent

        anchors.topMargin: toolBar.height + 15
        anchors.margins: 15

       // border.width: 1

        HorizontalHeaderView {
            id: horizontalHeader
            syncView: table
            //anchors.top: toolBar.bottom
            anchors.left: parent.left
            height: 40

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
    }
    //*/

    TableView {
        id: table

        anchors.fill: parent
        anchors.topMargin: horizontalHeader.height + 85
        //anchors.leftMargin: tableVerticalBar.width
        clip: true

        Keys.onUpPressed: scrollBar.decrease()
        Keys.onDownPressed: scrollBar.increase()

        ScrollBar.vertical: tableVerticalBar


        columnWidthProvider: function (column) {
            return table.width / 4//table.model.columnCount();
        }

        onWidthChanged: table.forceLayout()

        model: personalTableModel

        delegate: DelegateChooser {
            role: "type"

            DelegateChoice {
                roleValue: "str"

                Rectangle {
                    Rectangle {
                        id:cell
                        implicitWidth: table.columnWidthProvider(column)
                        implicitHeight: 50

                        //color: mouseArea.containsMouse ? "#DDDDDD" : "#FFFFFF"

                        //color: (row % 2 == 0) ? "#FFFFFF" : "#f1dff4"


                        border.width: 1

                        MouseArea {
                            id: mouseArea
                            anchors.fill: parent
                            //anchors.width: main.width
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
                    /*Rectangle{
                        anchors.margins: 0
                        anchors.top: cell.bottom

                        border.width: 1

                        height: 0.2
                        width: parent.width
                    }*/
                }
            }
            DelegateChoice {
                Rectangle {

                    border.width: 1
                    Image {
                        anchors.centerIn: parent
                        source: app.getIcon100UrlById(display)
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
