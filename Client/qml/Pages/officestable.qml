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
                app.loadOfficesRequest()
                }
            }

            Label {
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }

            ToolButton {
                text: 'Add office'
                onClicked: {
                    console.log("Add office")
                    app.addOfficesRequest()
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

    Rectangle {

        anchors.fill: parent

        anchors.topMargin: toolBar.height + 15
        anchors.margins: 15

    HorizontalHeaderView {
        id: horizontalHeader
        syncView: table
        anchors.top: toolBar.bottom
        anchors.left: parent.left


        delegate: Rectangle {
            color: "#CE93D8"

            Label {
                width: parent.width
                elide: Text.ElideRight
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignHCenter

                text:  model.display
                font.family: "Helvetica"
                font.weight: Font.Bold
            }
        }
    }

    TableView {
        id: table
        anchors.fill: parent
        anchors.topMargin:  horizontalHeader.height
        clip: true

        columnWidthProvider: function (column) {
            return table.width / table.model.columnCount();
        }

        onWidthChanged: table.forceLayout()

        model: officeTableModel

        delegate: Rectangle {
            implicitWidth: table.columnWidthProvider(column)
            implicitHeight: 30


            color: mouseArea.containsMouse ? "#DDDDDD" : "#FFFFFF"

            MouseArea {
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
                        console.log(row);
                        menu.curRow = row
                        menu.popup()
                    }
                    else if (mouse.button === Qt.LeftButton)
                    {
                        console.log("left");
                        console.log(row);
                        console.log(officeTableModel.getIDbyRow(row))
                        //main.loadUserPage(personalTableModel.getIDbyRow(row))
                        //officeTableModel.loadOfficePage(officeTableModel.getIDbyRow(row))
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
            app.loadOfficesRequest()
        }
    }
    }
}
