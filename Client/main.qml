import QtQuick 2.6
import QtQuick.Window 2.2
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

    color: "#DDDDDD"

    /*

    Material.theme: Material.Light
    Material.primary: "#1de9b6"
    Material.accent:"#3d5afe"
    /*
    Material.theme: Material[subTheme.currentText]
    Material.accent: Material[accentColor.currentText]
    Material.primary: Material[primaryColor.currentText]
    Universal.theme: Universal[subTheme.currentText]
    Universal.accent: Universal[accentColor.currentText]
    */

 /***********************************************************************/

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
    //*/

 /***********************************************************************/

    header: ToolBar {
        RowLayout {
            anchors.fill: parent

            ToolButton {
                icon.source: 'qrc:/images/baseline-menu-24px.svg'
                onClicked: drawer.open()
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
    //*/

 /***********************************************************************/

    /*
    Drawer {
        id: drawer
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

            Button {
                flat: true
                background.anchors.fill: this
            //    Layaout.fillWidth:true
                width: parent.width

                text: 'personal'

                MouseArea {
                width: parent.width
                anchors.fill: parent

                // By clicking on the menu item is replaced component in the Loader
                onClicked: {
                    loader.loadFragment(0)
                    hello()
                }
                }
                //horizontalAlignment: Text.AlignHCenter
            }

            Button {
                id: button
                width: parent.width
                flat: true
                background.anchors.fill: this
                spacing: 40

                contentItem: Text {
                    text: 'files'
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                MouseArea {
                    anchors.fill: parent

                    // By clicking on the menu item is replaced component in the Loader
                    onClicked: {
                        loader.loadFragment(1)
                        hello()
                    }
                }
            }

            Button {
                flat: true
                background.anchors.fill: this
                spacing: 40

                text: 'test'
                MouseArea {
                    anchors.fill: parent

                    // By clicking on the menu item is replaced component in the Loader
                    onClicked: {
                        loader.loadFragment(2)
                        hello()
                    }
                }
            }
        }
    }
    //*/

    Drawer {
        id: drawer
        width: 200
        height: parent.height

        ListModel {
            id: pages

            ListElement {
                name: 'personal'
                page_source: "qrc:/Pages/personal.qml"
            }
            ListElement {
                name: 'files'
                page_source: "qrc:/Pages/files.qml"
            }
            ListElement {
                name: 'calendar'
                page_source: "qrc:/Pages/calendar.qml"
            }
            ListElement {
                name: 'Test'
                page_source: "qrc:/Pages/Test.qml"
            }
        }

        Rectangle {

            anchors.fill: parent
            color: "#FFFFFF"

            ColumnLayout {
                anchors.fill: parent

                Label {
                    id: label
                    text: 'Drawer'
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 20
                    Layout.fillWidth: true
                    width: parent
                }

                Component {
                    id: drawerButton

                    Rectangle {
                        id: wrapper
                        //anchors.fill: parent


                        color: mouseArea.containsMouse ? "#DDDDDD" : "#FFFFFF"
                        width: parent.width
                        height: 40

                        Text {
                            anchors.centerIn: parent
                            text: model.name
                        }

                        MouseArea {
                            id: mouseArea
                            anchors.fill: parent
                            hoverEnabled: true

                            // By clicking on the menu item is replaced component in the Loader
                            onClicked: {
                                loader.loadFragment(model.page_source)
                                drawer.close()
                                hello()
                            }
                        }

                    }
                }

                ListView {
                    anchors.fill: parent
                    anchors.topMargin: label.height


                    model: pages

                    delegate:drawerButton
                    focus: true

                }

            }

        }

    }
    //*/

 /***********************************************************************/

    Loader {
        id: loader
        anchors.fill: parent
        source: "qrc:/Pages/personal.qml"

        function loadFragment(page_source){
            loader.source = page_source
        }
    }
    //*/
}
