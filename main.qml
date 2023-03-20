import QtQuick
import QtQuick.Layouts
import QtQuick.Controls 2.2

import QtQuick.Controls.Material
import QtQuick.Controls.Universal
import QtCharts
import Qt.labs.qmlmodels

ApplicationWindow {
  visible: true
  minimumHeight: 600
  minimumWidth: 1300
  Material.theme: Material[subTheme.currentText]
  Material.accent: Material[accentColor.currentText]
  Material.primary: Material[primaryColor.currentText]
  Universal.theme: Universal[subTheme.currentText]
  Universal.accent: Universal[accentColor.currentText]
  menuBar: MenuBar {
    Menu {
      title: '&File'
      Action { text: '&New...' }
      Action { text: '&Open...' }
      Action { text: '&Save' }
      Action { text: 'Save &As...' }
      MenuSeparator {}
      Action { text: '&Quit' }
    }
    Menu {
      title: '&Edit'
      Action { text: 'Cu&t' }
      Action { text: '&Copy' }
      Action { text: '&Paste' }
    }
    Menu {
      title: '&Help'
      Action { text: '&About' }
    }
  }
  header: ToolBar {
    RowLayout {
      anchors.fill: parent
      ToolButton {
        icon.source: '../images/baseline-menu-24px.svg'
        onClicked: sideNav.open()
      }
      Label {
        elide: Label.ElideRight
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
        Layout.fillWidth: true
      }
      ToolButton { text: 'Action 1' }
      ToolButton { text: 'Action 2' }
      ToolSeparator {}
      ToolButton { text: 'Action 3' }
      ToolButton { text: 'Action 4' }
      ToolButton {
        icon.source: '../images/baseline-more_vert-24px.svg'
        onClicked: menu.open()
        Menu {
          id: menu
          y: parent.height
          MenuItem { text: 'New...' }
          MenuItem { text: 'Open...' }
          MenuItem { text: 'Save' }
        }
      }
    }
  }
  Drawer {
    id: sideNav
    width: 200
    height: parent.height
    ColumnLayout {
      width: parent.width
      Label {
          text: 'Drawer'
          horizontalAlignment: Text.AlignHCenter
          verticalAlignment: Text.AlignVCenter
          font.pixelSize: 20
          Layout.fillWidth: true
      }
      Repeater {
        model: 5
        SideNavButton {
          icon.source: '../images/baseline-category-24px.svg'
          text: 'List ' + index
          Layout.fillWidth: true
        }
      }
    }
  }
  Pane {
      id: loader
      padding: 10
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
}
