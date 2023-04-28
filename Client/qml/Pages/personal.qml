import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Qt.labs.qmlmodels


//import PersonalModel 1.0


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
        //anchors.topMargin: toolBar.height

        //model: [ "Name" , "Title", "Office", "Department", "Teams"]

        delegate: Text {
            horizontalAlignment: Text.AlignHCenter
            text:  model.display//modelData//model.headerData()
        }
    }
    //border.width: 1
    //*/



    TableView {
        id: table
        //anchors.fill: parent
        anchors.top: horizontalHeader.bottom
        anchors.left: parent.left
        width: parent.width
        columnSpacing: 1
        rowSpacing: 1
        clip: true

        columnWidthProvider: function (column) {
            return table.width / 5;/// table.model.columnCount();
        }

        onWidthChanged: table.forceLayout()


        //model: model
        model: personalTableModel


        delegate: Rectangle {
            implicitWidth: table.columnWidthProvider(column)
            implicitHeight: 50
            //border.width: 1

            Text {
                text: "display"
                horizontalAlignment: Text.AlignHCenter
                //verticalAlignment:  Text.AlignVCenter
                anchors.centerIn: parent
                //anchors.leftMargin: 50
                width: parent.width
                elide: Text.ElideRight

            }
        }
        //*/


        Component.onCompleted: {
            console.log("Update")
            app.usersListRequest()
        }

    }
}

