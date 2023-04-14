import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Layouts
import QtQuick.Controls 2.2

import QtQuick.Controls.Material
import QtQuick.Controls.Universal
import QtCharts
import Qt.labs.qmlmodels


ApplicationWindow {
    id: root
    width: 100; height: 100

    Label {
        id: labelLogin
        anchors.left: parent.left
        text: 'Login'
    }

    Text {
        id: textLogin
        anchors.left: labelLogin.right
    }

    Label {
        id: labelPassword
        anchors.top: labelLogin.bottom
        anchors.left: parent.left
        text: 'Password'
    }

    Text {
        anchors.left: labelPassword.right
        anchors.top: textLogin.bottom
    }
}
