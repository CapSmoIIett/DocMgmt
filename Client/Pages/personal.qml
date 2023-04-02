import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Qt.labs.qmlmodels

Rectangle {
    anchors.fill: parent
    width: parent.width



    Rectangle {
        anchors.fill: parent
        color: "#FFFFFF"
    ListModel {
        id: myModel

        ListElement {
                name: "John"
                title: "Programmer"
                office: "New York"
                department: "IT"
                teams: "External project"

        }
        ListElement {
                name: "Alice"
                title: "Sound designer"
                office: "Paris"
                department: "Art"
                teams: "External project"
        }
        ListElement {
                name: "Bob"
                title: "Producer"
                office: "London"
                department: "Art"
                teams: "External project"
        }
        ListElement {
                name: "John"
                title: "Programmer"
                office: "New York"
                department: "IT"
                teams: "External project"

        }
        ListElement {
                name: "Alice"
                title: "Sound designer"
                office: "Paris"
                department: "Art"
                teams: "External project"
        }
        ListElement {
            name: "Bob"
            title: "Producer"
            office: "London"
            department: "Art"
            teams: "External project"
        }
        ListElement {
            name: "John"
            title: "Programmer"
            office: "New York"
            department: "IT"
            teams: "External project"

        }
        ListElement {
            name: "Alice"
            title: "Sound designer"
            office: "Paris"
            department: "Art"
            teams: "External project"
        }
        ListElement {
            name: "Bob"
            title: "Producer"
            office: "London"
            department: "Art"
            teams: "External project"
        }
        ListElement {
            name: "John"
            title: "Programmer"
            office: "New York"
            department: "IT"
            teams: "External project"

        }
        ListElement {
            name: "Alice"
            title: "Sound designer"
            office: "Paris"
            department: "Art"
            teams: "External project"
        }
        ListElement {
            name: "Bob"
            title: "Producer"
            office: "London"
            department: "Art"
            teams: "External project"
        }
        ListElement {
            name: "John"
            title: "Programmer"
            office: "New York"
            department: "IT"
            teams: "External project"

        }
        ListElement {
            name: "Alice"
            title: "Sound designer"
            office: "Paris"
            department: "Art"
            teams: "External project"
        }
        ListElement {
            name: "Bob"
            title: "Producer"
            office: "London"
            department: "Art"
            teams: "External project"
        }
        ListElement {
            name: "John"
            title: "Programmer"
            office: "New York"
            department: "IT"
            teams: "External project"

        }
        ListElement {
            name: "Alice"
            title: "Sound designer"
            office: "Paris"
            department: "Art"
            teams: "External project"
        }
        ListElement {
            name: "Bob"
            title: "Producer"
            office: "London"
            department: "Art"
            teams: "External project"
        }
        ListElement {
            name: "John"
            title: "Programmer"
            office: "New York"
            department: "IT"
            teams: "External project"

        }
        ListElement {
            name: "Alice"
            title: "Sound designer"
            office: "Paris"
            department: "Art"
            teams: "External project"
        }
        ListElement {
            name: "Bob"
            title: "Producer"
            office: "London"
            department: "Art"
            teams: "External project"
        }
        ListElement {
            name: "John"
            title: "Programmer"
            office: "New York"
            department: "IT"
            teams: "External project"

        }
        ListElement {
            name: "Alice"
            title: "Sound designer"
            office: "Paris"
            department: "Art"
            teams: "External project"
        }
        ListElement {
            name: "Bob"
            title: "Producer"
            office: "London"
            department: "Art"
            teams: "External project"
        }
        ListElement {
            name: "John"
            title: "Programmer"
            office: "New York"
            department: "IT"
            teams: "External project"

        }
        ListElement {
            name: "Alice"
            title: "Sound designer"
            office: "Paris"
            department: "Art"
            teams: "External project"
        }
        ListElement {
            name: "Bob"
            title: "Producer"
            office: "London"
            department: "Art"
            teams: "External project"
        }
        ListElement {
            name: "John"
            title: "Programmer"
            office: "New York"
            department: "IT"
            teams: "External project"

        }
        ListElement {
            name: "Alice"
            title: "Sound designer"
            office: "Paris"
            department: "Art"
            teams: "External project"
        }
        ListElement {
            name: "Bob"
            title: "Producer"
            office: "London"
            department: "Art"
            teams: "External project"
        }
        ListElement {
            name: "John"
            title: "Programmer"
            office: "New York"
            department: "IT"
            teams: "External project"

        }
        ListElement {
            name: "Alice"
            title: "Sound designer"
            office: "Paris"
            department: "Art"
            teams: "External project"
        }
        ListElement {
            name: "Bob"
            title: "Producer"
            office: "London"
            department: "Art"
            teams: "External project"
        }
        ListElement {
            name: "John"
            title: "Programmer"
            office: "New York"
            department: "IT"
            teams: "External project"

        }
        ListElement {
            name: "Alice"
            title: "Sound designer"
            office: "Paris"
            department: "Art"
            teams: "External project"
        }
        ListElement {
            name: "Bob"
            title: "Producer"
            office: "London"
            department: "Art"
            teams: "External project"
        }
        ListElement {
            name: "John"
            title: "Programmer"
            office: "New York"
            department: "IT"
            teams: "External project"

        }
        ListElement {
            name: "Alice"
            title: "Sound designer"
            office: "Paris"
            department: "Art"
            teams: "External project"
        }
        ListElement {
            name: "Bob"
            title: "Producer"
            office: "London"
            department: "Art"
            teams: "External project"
        }
        ListElement {
            name: "John"
            title: "Programmer"
            office: "New York"
            department: "IT"
            teams: "External project"

        }
        ListElement {
            name: "Alice"
            title: "Sound designer"
            office: "Paris"
            department: "Art"
            teams: "External project"
        }
        ListElement {
            name: "Bob"
            title: "Producer"
            office: "London"
            department: "Art"
            teams: "External project"
        }
    }



        // Define the table rows
        TableView {
            anchors.fill: parent
            id: table
            model: myModel
            clip: true

            //highlight:  Rectangle { width: 80; height: 80; color: "lightsteelblue" }

            TableViewColumn {
                role: "name"
                title: "name"
                width: 300
                horizontalAlignment: Text.AlignHCenter
            }

            relegate: Rectangle {

                /*Image {
                id: icon
                hight:parent.hight
                source: 'qrc:/images/baseline-more_vert-24px.svg'
                }*/

                Text {
                anchors.left: parent.left
                text: model.name
                }

            }
        }
    }
}

