
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

    TableView {
        anchors.fill: parent

        model: rightsTableModel

        delegate: Rectangle {
            implicitHeight: 30
            implicitWidth: 50

            Label {
                text: display
                anchors.centerIn: parent
            }
        }
    }
}
