import QtQuick
import QtQuick.Window
import QtQuick.Controls 2.15

Window {
    id: window
    visible: true
    color: "#00ffffff"
    width: 1000
    height: 800
    title: qsTr("Hello World")

    Rectangle {
        id:bg
        color: "#36393f"
        anchors.fill: parent
        anchors.margins: 10

        Rectangle {
            id: left_menu_bg
            width: 65
            anchors.top:parent.top
            anchors.bottom: parent.bottom
            color: "#202225"

        }

        Rectangle {
            id: top_bar
            height: 22
            color: "#202225"
            anchors.left: left_menu_bg.right
            anchors.right: parent.right
            anchors.top: bg.top
            anchors.rightMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
        }

        Rectangle {
            id: tool_bar
            height: 70
            color: "#2f3136"
            anchors.left: left_menu_bg.right
            anchors.right: parent.right
            anchors.top: top_bar.bottom
            anchors.rightMargin: 0
            anchors.topMargin: 0
            anchors.leftMargin: 0
        }

        Rectangle {
            id: rectangle
            color: "#ffffff"
            anchors.left: left_menu_bg.right
            anchors.right: parent.right
            anchors.top: tool_bar.bottom
            anchors.bottom: parent.bottom
            anchors.rightMargin: 0
            anchors.leftMargin: 0
            anchors.bottomMargin: 0
            anchors.topMargin: 0

            Loader {
                id: page_loader
                anchors.fill:parent
                source: Qt.resolvedUrl("component/pages/homePage.qml")
            }
        }
    }

}
