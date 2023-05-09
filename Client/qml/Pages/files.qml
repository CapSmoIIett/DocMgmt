import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Qt.labs.qmlmodels



Rectangle {
    anchors.fill: parent

    property var borderColor: (drop.cantainsDrag)? "#FF9200" : "#909090"
    onBorderColorChanged: { requestPaint(); }

    DropArea {
    id: drop
    anchors.fill: parent

     property var fileExtensionFilters: (["Text (*.txt)", "Obj (*.o)"])

    property bool acceptedDrag: false
    property bool cantainsDrag: false

    onEntered: (drag) => {
        let acceptedCount = 0;
        for(let i=0; i<drag.urls.length; ++i) {
            if( validateFileExtension(drag.urls[i]) ) { acceptedCount++; }
        }
        drag.accepted = ( ((dropArea.multiple && drag.urls.length>0) || ( !dropArea.multiple && drag.urls.length===1)) && acceptedCount===drag.urls.length );
        drop.cantainsDrag = drag.accepted;
    }

    onExited: {
        drop.cantainsDrag = false;
    }

    onDropped: (drag) => {
                   console.log("drop");
        for(let i=0; i<drag.urls.length; ++i) {
             console.log(drag.urls[i])
            app.uploadFile(drag.urls[i])
        }
        drop.cantainsDrag = false;
    }

    function validateFileExtension(filePath)
    {
        return true;
        //if ( !filePath ) { return false; }
        //if ( dropArea.fileExtensionFilters.length===0 ) { return true; }
        //return ( _private.fileExtensionFiltersStr.indexOf("(*."+((""+filePath).split('.').pop())+")")>-1 );
    }




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
}
