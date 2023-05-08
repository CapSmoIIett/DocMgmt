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

        anchors.leftMargin: 15
        anchors.rightMargin: 15

        RowLayout {
            anchors.fill: parent

            ToolButton {
                id: updateButton

                text: "Update"
                onClicked: {
                    console.log("Update")
                    app.loadFilesRequest(path.text)
                }
            }

            Label {
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }

            ToolButton {
                width: 30
                text: 'Add right'
                onClicked: {
                    console.log("Add right")
                    app.addRightsRequest()
                }
            }
        }
    }

    RowLayout {
        id: pathLine
        Layout.preferredHeight: 40
        width: parent.width

        anchors.top: toolBar.bottom
        anchors.left: parent.left

        TextField {
            id: path
            enabled: true
            text: folderModel.folder
            Layout.fillWidth: true
        }
        Button {
            text: "..."
            onClicked: folderDialog.open();
        }

        Component.onCompleted: {
            path.text = ""
        }
    }

    HorizontalHeaderView {
        id: horizontalHeader
        syncView: table
        anchors.top: pathLine.bottom
        anchors.left: parent.left

        delegate: Text {
            horizontalAlignment: Text.AlignHCenter
            text:  model.display
        }
    }

    TableView {
        id: table

        anchors.fill: parent
        anchors.topMargin: toolBar.height + pathLine.height + horizontalHeader.height
        clip: true


        columnWidthProvider: function (column) {
            return table.width / 3//table.model.columnCount();
        }

        onWidthChanged: table.forceLayout()

        model: filesTableModel

        delegate: Rectangle {
            implicitWidth: table.columnWidthProvider(column)
            implicitHeight: 30

            color: mouseArea.containsMouse ? "#DDDDDD" : "#FFFFFF"

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
                        //console.log(personalTableModel.getIDbyRow(row))
                        //main.loadUserPage(personalTableModel.getIDbyRow(row))
                        //personalTableModel.loadUserPage(personalTableModel.getIDbyRow(row))
                    }
                }
            }
        }


        Menu {
            id: menu
            //y: openMenuButton.height

            property int curRow

            MenuItem {
                text: 'download'

                onClicked: {
                    app.downloadFileRequest(path.text, filesTableModel.getNameByRow(menu.curRow))
                }
            }

            MenuItem {
                text: 'remove'

                onClicked: {
                    //app.removeUserRequest(menu.curRow)
                }
            }
        }

        Component.onCompleted: {
            app.loadFilesRequest(path.text)
        }
    }
}
