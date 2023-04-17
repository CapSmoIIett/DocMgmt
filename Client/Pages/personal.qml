import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Qt.labs.qmlmodels

Rectangle {
    anchors.fill: parent


    HorizontalHeaderView {
        id: horizontalHeader
        syncView: table
        anchors.left: tableView.left

        //model: [ "Name" , "Title", "Office", "Department", "Teams"]

        delegate: Text {
            horizontalAlignment: Text.AlignHCenter
            text:  model.display//modelData//model.headerData()
        }
    }
    //border.width: 1
    //*/



    TableModel {
        id: model

        TableModelColumn {display: "name" }
        TableModelColumn {display: "title" }
        TableModelColumn {display: "office" }
        TableModelColumn {display: "department" }
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
            "teams": "External project of U.S.A."
        }
        ]
    }



    TableView {
        id: table
        anchors.fill: parent
        anchors.topMargin: horizontalHeader.implicitHeight
        columnSpacing: 1
        rowSpacing: 1
        clip: true

        columnWidthProvider: function (column) {
            return table.width / 5;/// table.model.columnCount();
        }
        onWidthChanged: table.forceLayout()


        model: model

        delegate: Rectangle {
            implicitWidth: table.columnWidthProvider(column)
            implicitHeight: 50
            //border.width: 1

            Text {
                text: display
                horizontalAlignment: Text.AlignHCenter
                //verticalAlignment:  Text.AlignVCenter
                anchors.centerIn: parent
                //anchors.leftMargin: 50
                width: parent.width
                elide: Text.ElideRight

            }


        }
        //*/


    }
}
