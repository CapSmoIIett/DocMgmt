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
        icon.source: 'qrc:/images/baseline-menu-24px.svg'
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
        icon.source: 'qrc:/images/baseline-more_vert-24px.svg'
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

  signal hello()

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
          icon.source: 'qrc:/images/baseline-category-24px.svg'
          text: 'List ' + index
          Layout.fillWidth: true
      MouseArea {
            anchors.fill: parent

            // By clicking on the menu item is replaced component in the Loader
            onClicked: {
            loader.loadFragment(index)
                hello()
            }
        }
        }
      }
    }
  }
  Loader {
     id: loader
     anchors.fill: parent
     source: "qrc:/Pages/Test.qml"

     function loadFragment(index){

            switch(index){
            case 0:
                loader.source = "qrc:/Pages/Test.qml"
                break;
            case 1:
                loader.source = "qrc:/Pages/files.qml"
                break;
            }
        }
  }

}
