import QtQuick
import QtQuick.Layouts
import QtQuick.Controls 2.2


Rectangle {
      anchors.fill: parent
      width: parent.width
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

      ColumnLayout {
              anchors.left: parent.left
              anchors.top: parent.top
            width: parent.width

          // Define the header row
          RowLayout {
              anchors.left: parent.left
              anchors.top: parent.top
              spacing: 4
              Rectangle {
                  Layout.fillWidth: true
                  height: 20
                  color: "lightgray"
                  Text {
                      text: "Name"
                      anchors.centerIn: parent
                  }
              }
              Rectangle {
                  Layout.fillWidth: true
                  height: 20
                  color: "lightgray"
                  Text {
                      text: "Title"
                      anchors.centerIn: parent
                  }
              }
              Rectangle {
                  Layout.fillWidth: true
                  height: 20
                  color: "lightgray"
                  Text {
                      text: "Office"
                      anchors.centerIn: parent
                  }
              }
              Rectangle {
                  Layout.fillWidth: true
                  height: 20
                  color: "lightgray"
                  Text {
                      text: "Department"
                      anchors.centerIn: parent
                  }
              }
              Rectangle {
                  Layout.fillWidth: true
                  height: 20
                  color: "lightgray"
                  Text {
                      text: "Teams"
                      anchors.centerIn: parent
                  }
              }
         }

          // Define the table rows
          Repeater {
              model: myModel
              delegate: RowLayout {
                  spacing: 4
                  Rectangle {
                      Layout.fillWidth: true
                      height: 20
                      color: index % 2 == 0 ? "white" : "lightgray"
                      Text {
                          text: name
                          anchors.centerIn: parent
                      }
                  }
                  Rectangle {
                      Layout.fillWidth: true
                      height: 20
                      color: index % 2 == 0 ? "white" : "lightgray"
                      Text {
                          text: title
                          anchors.centerIn: parent
                      }
                  }
                  Rectangle {
                      Layout.fillWidth: true
                      height: 20
                      color: index % 2 == 0 ? "white" : "lightgray"
                      Text {
                          text: office
                          anchors.centerIn: parent
                      }
                  }
                  Rectangle {
                      Layout.fillWidth: true
                      height: 20
                      color: index % 2 == 0 ? "white" : "lightgray"
                      Text {
                          text: department
                          anchors.centerIn: parent
                      }
                  }
                  Rectangle {
                      Layout.fillWidth: true
                      height: 20
                      color: index % 2 == 0 ? "white" : "lightgray"
                      Text {
                          text: teams
                          anchors.centerIn: parent
                      }
                  }
              }
          }
      }
  }
