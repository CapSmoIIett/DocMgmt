import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Qt.labs.qmlmodels

Rectangle {
    anchors.fill: parent
    width: parent.width

    HorizontalHeaderView {
        id: horizontalHeader
        syncView: table
        anchors.left: tableView.left
    }


    TableModel {
        id: model

        TableModelColumn {display: "name" }
        TableModelColumn {display: "title" }
        TableModelColumn {display: "office" }
        TableModelColumn {display: "depatment" }
        TableModelColumn {display: "teams" }

        rows: [
        {
            "name": "John",
            "title": "Programmer",
            "office": "New York",
            "department": "IT",
            "teams": "External project"
        },
        {
            "name": "John",
            "title": "Programmer",
            "office": "New York",
            "department": "IT",
            "teams": "External project"
        },
        {
            "name": "Alice",
            "title": "Sound designer",
            "office": "Paris",
            "department": "Art",
            "teams": "External project"
        },
        {
            "name": "Bob",
            "title": "Producer",
            "office": "London",
            "department": "Art",
            "teams": "External project"
        },
        {
            "name": "John",
            "title": "Programmer",
            "office": "New York",
            "department": "IT",
            "teams": "External project"
        },
        {
            "name": "Alice",
            "title": "Sound designer",
            "office": "Paris",
            "department": "Art",
            "teams": "External project"
        },
        {
            "name": "Bob",
            "title": "Producer",
            "office": "London",
            "department": "Art",
            "teams": "External project"
        },
        {
            "name": "John",
            "title": "Programmer",
            "office": "New York",
            "department": "IT",
            "teams": "External project"
        },
        {
            "name": "Alice",
            "title": "Sound designer",
            "office": "Paris",
            "department": "Art",
            "teams": "External project"
        },
        {
            "name": "Alice",
            "title": "Sound designer",
            "office": "Paris",
            "department": "Art",
            "teams": "External project"
        },
        {
            "name": "Bob",
            "title": "Producer",
            "office": "London",
            "department": "Art",
            "teams": "External project of USA"
        }
        ]
    }



    TableView {
        id: table
        anchors.fill: parent
        anchors.topMargin: header.height
        columnSpacing: 1
        rowSpacing: 1
        clip: true

        model: model

        /*columnWidthProvider: function (column) {
            return model ? table.width / model.columnCount() : 0// Width(column)
        }*/

        delegate: Rectangle {
            //implicitWidth: text.implicitwidth > 100 ? text.implicitWidth : 100
            //implicitWidth: table.columnWidthProvider(column)

            //implicitWidth: 100
            implicitHeight: 50
            border.width: 1

            Text {
                id: text
                text: display
                anchors.centerIn: parent
            }
        }

        Row {
            id: header
            Repeater {
                //model: model.columnCount()
                model: table.columns > 0 ? columns : 1

                Rectangle {
                    //width: model.columnWidth(index)
                    //height: parent.height
                    //width: table.columnWidthProvider()

                    implicitWidth: 100
                    implicitHeight: 50
                    border.width: 1

                    Text {
                        text: display
                        anchors.centerIn: parent
                    }
                }
            }
        }
    }
}
