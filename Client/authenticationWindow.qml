import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Layouts
import QtQuick.Controls 2.2

import QtQuick.Controls.Material
import QtQuick.Controls.Universal
import QtCharts
import Qt.labs.qmlmodels


Rectangle {
    //id: loginWindow
    //visible: true
    anchors.fill: parent
    signal onLogin

    //flags: Qt.Dialog
    //modality: Qt.ApplicationModal


    //Rectangle {
    //    id: bg

    //border.width: 0

    /*
    GroupBox {
        id: gridBox
        title: "Verification"
        Layout.fillWidth: true
        //Layout.minimumWidth: grid.Layout.minimumWidth + 30
        //anchors.fill: parent
        width: parent.width



        GridLayout {
            id: grid
            rows: 2
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

            TextField {
                id: textLogin
                Layout.fillWidth: true
            }
            TextField {
                id: textPassword
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
                loginWindow.onLogin
                //component.onCompleted:  console.log("HI") //Qt.createComponent("authenticationWindow.qml")
                //const QUrl url(u"qrc:/DocMgmtQt/main.qml"_qs);
                /*
                var component = Qt.createComponent("qrc:/DocMgmtQt/main.qml")

                if (component.status === Component.Ready)
                {
                    component.createObject(parent);
                }
                *//*
            }
        }

    //*/
}
