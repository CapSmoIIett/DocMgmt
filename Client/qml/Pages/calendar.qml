import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Qt.labs.qmlmodels


Rectangle {
    anchors.fill: parent

Rectangle {
    anchors.fill: parent
    anchors.margins: 15

    Row {
        width: parent.width
        id: navigationButtons
        anchors.leftMargin: verticalHeader.width

        Label {
            Layout.fillWidth: true
            //anchors.leftMargin: parent.width / 2 - back.width - 30 - date.width
        }
        Button {
            id: back
            icon.source: "qrc:/images/back.png"
        }
        Label {
            width: 30
        }
        Label {
            id: date
            height: back.height
            text: calendar.getMonthName(calendar.month) + "\n" + calendar.year
            horizontalAlignment: Text.AlignHCenter
        }
        Label {
            width: 30
        }
        Button {
            id:forward
            icon.source: "qrc:/images/forward.png"
        }
        Label {
            Layout.fillWidth: true
        }
    }

    HorizontalHeaderView {
        id: horizontalHeader
        syncView: table
        anchors.left: table.left
        anchors.top: navigationButtons.bottom
        //anchors.leftMargin: verticalHeader.width

        delegate: Text {
            horizontalAlignment: Text.AlignHCenter
            text:  model.display//modelData//model.headerData()
        }
    }

    VerticalHeaderView {
        id: verticalHeader
        syncView: table
        anchors.left: parent.left
        anchors.top: table.top
        anchors.right: table.left

        delegate: Text {
            horizontalAlignment: Text.AlignHCenter
            text:  model.display//modelData//model.headerData()
        }
    }

    TableView {
        id: table
        anchors.fill: parent
        anchors.topMargin: horizontalHeader.height + navigationButtons.height
        anchors.leftMargin: verticalHeader.width
        //anchors.left: verticalHeader.right
        columnSpacing: 1
        rowSpacing: 1
        clip: true

        onWidthChanged: table.forceLayout()

        model: calendar

        delegate: Rectangle {
            implicitWidth: 40
            implicitHeight: 40
            border.width: 1

            Rectangle {
                anchors.fill: parent
                anchors.margins: 2
                color: display ? Material.color(Material.Purple) : "#FFFFFF"
                border.width: display ? 1 : 0
            }

            MouseArea {
                anchors.fill: parent

                onClicked: {
                    console.log(column);
                    console.log(row);
                    calendar.setHoliday(column, row);
                }
            }

        }

        Component.onCompleted: {
            app.loadCalendarRequest(calendar.month, calendar.year);
        }
    }
}
}
