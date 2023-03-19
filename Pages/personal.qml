import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Qt.labs.qmlmodels

Item {
    height: 800
    width: parent.width
    //anchors.fill: parent

    Rectangle {
        id: table
        color: "#ffffff"
        anchors.fill: parent
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0

        //required property var model
        // ...

        ColumnLayout {
            anchors.fill: parent
            spacing: 0

            HorizontalHeaderView {
                id: horizontalHeader
                reuseItems: false
                syncView: tableView
                height: 30
                Layout.fillWidth: true
                boundsBehavior:Flickable.StopAtBounds

                TableModelColumn { display: "type" }
                TableModelColumn { display: "speed" }
                TableModelColumn { display: "ammunition" }
                TableModelColumn { display: "active" }
                TableModelColumn { display: "coordinates" }
                // ...
            }

            TableView {
                id: tableView
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
                boundsBehavior:Flickable.StopAtBounds

                model: table.model

                // ...
            }

        } // ColumnLayout

    } // Rectangle table
}
