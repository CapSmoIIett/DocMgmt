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
        }
        Button {
            id: back
            icon.source: "qrc:/images/back.png"
            onClicked: {
                calendar.datePrev();
                app.loadCalendarRequest(calendar.month, calendar.year);
                date.text = calendar.getMonthName(calendar.month) + "\n" + calendar.year
            }
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
            onClicked: {
                calendar.dateNext();
                app.loadCalendarRequest(calendar.month, calendar.year);
                date.text = calendar.getMonthName(calendar.month) + "\n" + calendar.year
            }
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

        delegate: Rectangle {
            width: 40
            height: 40

            color: "#CE93D8"

            Text {
                horizontalAlignment: Text.AlignHCenter
                text:  model.display//modelData//model.headerData()
            }
        }
    }

    VerticalHeaderView {
        id: verticalHeader
        syncView: table
        anchors.left: parent.left
        anchors.top: table.top
        //anchors.right: table.left

        delegate: Rectangle {
            width: 550
            border.width: 1

            color: "#CE93D8"

            Text {
                width: parent.width
                elide: Text.ElideRight
                horizontalAlignment: Text.AlignHCenter
                text:  model.display//modelData//model.headerData()
            }
        }
    }

    TableView {
        id: table
        anchors.fill: parent
        anchors.topMargin: horizontalHeader.height + navigationButtons.height
        anchors.leftMargin: verticalHeader.width
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
