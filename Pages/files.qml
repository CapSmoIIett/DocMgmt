import QtQml
import QtQuick
import Qt.labs.folderlistmodel

Item {
    ListView {
        width: 200; height: 400

        FolderListModel {
            id: folderModel
            nameFilters: ["*.qml"]
        }

        Component {
            id: fileDelegate
            Text { text: fileName }
        }

        model: folderModel
        delegate: fileDelegate
    }
}
