import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Layouts
import QtQuick.Controls 2.2

import QtQuick.Controls.Material
import QtQuick.Controls.Universal
import QtCharts
import Qt.labs.qmlmodels

ApplicationWindow {
    id: mainWindow
    visible: false
    minimumHeight: 600
    minimumWidth: 1300

    color: "#DDDDDD"

    Material.theme: Material.Light
    Material.primary: Material.Purple
    Material.accent:"#3d5afe"

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


    Window{
        id: loginWindow
        minimumWidth: 450
        minimumHeight: 230

        x: (Screen.width - loginWindow.width) / 2
        y: (Screen.height - loginWindow.height) / 2

        signal onLogin

        GroupBox {
            id: gridBox
            title: "Verification"
            Layout.fillWidth: true
            //Layout.minimumWidth: grid.Layout.minimumWidth + 30
            //anchors.fill: parent
            width: parent.width

            GridLayout {
                id: grid
                rows: 3
                flow: GridLayout.TopToBottom
                anchors.fill: parent
                width: parent.width


                Label {
                    id: labelLogin
                    text: "Login"
                }
                Label {
                    id: labelPassword
                    text: "Password"
                }
                Label {
                    id: labelIp
                    text: "IP"
                }

                TextField {
                    id: textLogin
                    Layout.fillWidth: true
                }
                TextField {
                    id: textPassword
                    Layout.fillWidth: true
                }
                TextField {
                    id: textIP
                    Layout.fillWidth: true

                }
            }
        }
        Label {
            id: error
            anchors.top: gridBox.bottom
            anchors.left: parent.left
            anchors.margins: 15
            visible:false

            text: "Error to login!"
        }

        Button {
            text: "login"
            anchors.top: gridBox.bottom
            anchors.right: parent.right
            anchors.margins: 15

            width: 100

            onClicked: {
                console.log("clicked")
                loginWindow.onLogin()

                app.userName = textLogin.text
                app.password = textPassword.text
                app.ip = textIP.text

                //loginWindow.hide()
                //mainWindow.show()

                app.verify()


            }
        }

        Component.onCompleted: {
            textLogin.text = "supervisor"
            textPassword.text = "1111"
            textIP.text =  "127.0.0.1"
        }

        Connections {
            target: app


            onVerified : {
                //var isVerified = result
                    console.log("verified")

                if (result)
                {
                    console.log("true")
                    app.loadCurUserDataRequest()
                    loginWindow.hide()
                    mainWindow.show()

                    rightsTableModel.loadrightsRequest()
                    officeTableModel.loadOfficesRequest()
                }
                else
                {
                }
            }
        }
    }//*/


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

            ToolButton {

                /*Label {
                    anchors.centerIn: parent.Center
                    text: app.userName
                }*/
                text: '_' + app.userName + "shit"

                onClicked: {
                    loader.loadFragment("qrc:/qml/Pages/user.qml")
                }
            }
            ToolSeparator {}
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
    Drawer {
        id: drawer
        width: 200
        height: parent.height

        ListModel {
            id: pages

            ListElement {
                name: 'personal'
                page_source: "qrc:/qml/Pages/personal.qml"
            }
            ListElement {
                name: 'files'
                page_source: "qrc:/qml/Pages/files.qml"
            }
            ListElement {
                name: 'calendar'
                page_source: "qrc:/qml/Pages/calendar.qml"
            }
            ListElement {
                name: 'Test'
                page_source: "qrc:/qml/Pages/Test.qml"
            }
            ListElement {
                name: 'Rights'
                page_source: "qrc:/qml/Pages/rightstable.qml"
            }
            ListElement {
                name: 'Offices'
                page_source: "qrc:/qml/Pages/officestable.qml"
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
                    //height: menuBar.height + ToolBar.height
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
        source: "qrc:/qml/Pages/personal.qml"

        function loadFragment(page_source){
            loader.source = page_source
        }

    }

    // Call User page
    Connections {
        target: personalTableModel
        onLoadUserPage: function (id) {
            console.log("show user")
            console.log (id)

            console.log("##############################################")
            userPage.loadUserRequest(id)
        }
    }
    Connections {
        target: userPage
        onGetedUser: {
            loader.loadFragment("qrc:/qml/Pages/user.qml")
        }
    }


    // Call Right page
    Connections {
        target: rightsTableModel
        onLoadRightPage: function (id) {
            console.log("show right")
            console.log (id)

            rightPage.loadRightRequest(id)
        }
    }
    Connections {
        target: rightPage
        onGetedRight: {
            loader.loadFragment("qrc:/qml/Pages/right.qml")
        }
    }

    // Call Right page
    Connections {
        target: officeTableModel
        onLoadOfficePage: function (id) {
            console.log("show office")
            console.log (id)

            officePage.loadOfficeRequest(id)
        }
    }
    Connections {
        target: officePage
        onGetedOffice: {
            loader.loadFragment("qrc:/qml/Pages/office.qml")
        }
    }


    Connections {
        target: app
        onChangeIP: {
            app.ip = textIP.text
        }
    }


    Component.onCompleted: {
        loginWindow.showNormal()

            x: 1000//Screen.width / 2 - loginWindow.width / 2;
            y: 0 //Screen.height / 2 - loginWindow.height / 2;
    }

    //*/
}
