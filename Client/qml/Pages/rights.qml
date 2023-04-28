import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Qt.labs.qmlmodels


Rectangle {
    anchors.fill: parent

    HorizontalHeaderView {
        id: horizontalHeader
        syncView: table

        delegate: Text {
            horizontalAlignment: Text.AlignHCenter
            text:  model.display
        }
    }

    TableView {
        id: table
        anchors.fill: parent
        anchors.topMargin: horizontalHeader.height
        clip: true


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
