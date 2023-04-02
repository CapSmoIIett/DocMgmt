import QtQuick
import QtQuick.Layouts
import QtQuick.Controls 2.2
import Qt.labs.folderlistmodel 2.2
import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.2
import Qt.labs.folderlistmodel 2.1
import Qt.labs.platform 1.0


Rectangle {
    anchors.fill: parent

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        RowLayout {
            Layout.preferredHeight: 40
            Layout.fillWidth: true
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
        }

        ListView {
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: FolderListModel {
                id: folderModel
                folder: ""
            }
            delegate: Text { text: fileName }
        }
    }

    FolderDialog {
        id: folderDialog
        currentFolder: ""
        folder: StandardPaths.standardLocations(StandardPaths.PicturesLocation)[0]
        onFolderChanged: {
            folderModel.folder = folder;
        }
    }
}
