import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Qt.labs.qmlmodels


//import PersonalModel 1.0


Rectangle {
    anchors.fill: parent

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

        x: 50
        y:50

        //width: parent.width
        anchors.fill: parent
        anchors.topMargin: toolBar.height + horizontalHeader.height
        //anchors.left: parent.left
        clip: true


        columnWidthProvider: function (column) {
            return table.width / 3//table.model.columnCount();
        }

        onWidthChanged: table.forceLayout()

        model: personalTableModel

        delegate: Rectangle {
            implicitWidth: table.columnWidthProvider(column)
            implicitHeight: 30

            Label {
                text: display

                width: parent.width
                elide: Text.ElideRight
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignHCenter
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
