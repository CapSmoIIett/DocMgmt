import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Controls.Universal
import QtCharts

import Qt.labs.folderlistmodel

  Pane {
    padding: 10
    anchors.fill: parent
    GridLayout {
      anchors.fill: parent
      flow: GridLayout.TopToBottom
      rows: 2
      CellBox {
        title: 'Buttons'
        ColumnLayout {
          anchors.fill: parent
          Button {
            text: 'Button'
            Layout.fillWidth: true
            onClicked: normalPopup.open()
          }
          Button {
            text: 'Flat'
            Layout.fillWidth: true
            flat: true
            onClicked: modalPopup.open()
          }
          Button {
            text: 'Highlighted'
            Layout.fillWidth: true
            highlighted: true
            onClicked: dialog.open()
          }
          RoundButton {
            text: '+'
            Layout.alignment: Qt.AlignHCenter
          }
        }
      }
      CellBox {
        title: 'Radio Buttons'
        ColumnLayout {
          anchors.fill: parent
          RadioButton { text: 'Radio Button 1'; checked: true }
          RadioButton { text: 'Radio Button 2' }
          RadioButton { text: 'Radio Button 3' }
          RadioButton { text: 'Radio Button 4' }
        }
      }
      CellBox {
        title: 'Check Boxes'
        ColumnLayout {
          anchors.fill: parent
          Switch { Layout.alignment: Qt.AlignHCenter }
          ButtonGroup {
            id: childGroup
            exclusive: false
            checkState: parentBox.checkState
          }
          CheckBox {
            id: parentBox
            text: 'Parent'
            checkState: childGroup.checkState
          }
          CheckBox {
            checked: true
            text: 'Child 1'
            leftPadding: indicator.width
            ButtonGroup.group: childGroup
          }
          CheckBox {
            text: 'Child 2'
            leftPadding: indicator.width
            ButtonGroup.group: childGroup
          }
        }
      }
      CellBox {
        title: 'Progress Indicators'
        ColumnLayout {
          anchors.fill: parent
          BusyIndicator {
            running: true
            Layout.alignment: Qt.AlignHCenter
            ToolTip.visible: hovered
            ToolTip.text: 'Busy Indicator'
          }
          DelayButton {
            text: 'Delay Button'
            delay: 3000
            Layout.fillWidth: true
          }
          ProgressBar { value: 0.6; Layout.fillWidth: true }
          ProgressBar { indeterminate: true; Layout.fillWidth: true }
        }
      }
      CellBox {
          title: 'ComboBoxes'
          ColumnLayout {
              anchors.fill: parent
              ComboBox {
                model: ['Normal', 'Second', 'Third']
                Layout.fillWidth: true
              }
              ComboBox {
                model: ['Flat', 'Second', 'Third']
                Layout.fillWidth: true
                flat: true
              }
              ComboBox {
                model: ['Editable', 'Second', 'Third']
                Layout.fillWidth: true
                editable: true
              }
              ComboBox {
                  model: 10
                  editable: true
                  validator: IntValidator { top: 9; bottom: 0 }
                  Layout.fillWidth: true
              }
          }
      }
      CellBox {
        title: 'Range Controllers'
        ColumnLayout {
          anchors.fill: parent
          Dial {
            id: dial
            scale: 0.8
            Layout.alignment: Qt.AlignHCenter
            ToolTip {
              parent: dial.handle
              visible: dial.pressed
              text: dial.value.toFixed(2)
            }
          }
          RangeSlider {
            first.value: 0.25; second.value: 0.75; Layout.fillWidth: true
            ToolTip.visible: hovered
            ToolTip.text: 'Range Slider'
          }
          Slider {
            id: slider
            Layout.fillWidth: true
            ToolTip {
              parent: slider.handle
              visible: slider.pressed
              text: slider.value.toFixed(2)
            }
          }
        }
      }
      CellBox {
        title: 'Spin Boxes'
        ColumnLayout {
          anchors.fill: parent
          SpinBox { value: 50; editable: true; Layout.fillWidth: true }
          SpinBox {
            from: 0
            to: items.length - 1
            value: 1 // 'Medium'
            property var items: ['Small', 'Medium', 'Large']
            validator: RegularExpressionValidator {
              regularExpression: new RegExp('(Small|Medium|Large)', 'i')
            }
            textFromValue: function(value) {
              return items[value];
            }
            valueFromText: function(text) {
              for (var i = 0; i < items.length; ++i)
                if (items[i].toLowerCase().indexOf(text.toLowerCase()) === 0)
                  return i
              return sb.value
            }
            Layout.fillWidth: true
          }
          SpinBox {
            id: doubleSpinbox
            editable: true
            from: 0
            value: 110
            to: 100 * 100
            stepSize: 100
            property int decimals: 2
            property real realValue: value / 100
            validator: DoubleValidator {
              bottom: Math.min(doubleSpinbox.from, doubleSpinbox.to)
              top:  Math.max(doubleSpinbox.from, doubleSpinbox.to)
            }
            textFromValue: function(value, locale) {
              return Number(value / 100).toLocaleString(locale, 'f', doubleSpinbox.decimals)
            }
            valueFromText: function(text, locale) {
              return Number.fromLocaleString(locale, text) * 100
            }
            Layout.fillWidth: true
          }
        }
      }
      CellBox {
        title: 'Text Inputs'
        Column {
          // ScrollView will not work if we use ColumnLayout as
          // ColumnLayout always measures its size depending on its
          // contents.
          anchors.fill: parent
          spacing: 10
          TextField {
            width: parent.width
            placeholderText: 'Enter something here...'
            selectByMouse: true
          }
          TextField {
            width: parent.width
            text: 'read only'
            readOnly: true
          }
          ScrollView {
            width: parent.width
            height: parent.height - y
            TextArea {
              placeholderText: 'Multi-line text editor...'
              selectByMouse: true
              persistentSelection: true
            }
          }
        }
      }
      Popup {
        id: normalPopup
        ColumnLayout {
          anchors.fill: parent
          Label { text: 'Normal Popup' }
          CheckBox { text: 'E-mail' }
          CheckBox { text: 'Calendar' }
          CheckBox { text: 'Contacts' }
        }
      }
      Popup {
        id: modalPopup
        modal: true
        ColumnLayout {
          anchors.fill: parent
          Label { text: 'Modal Popup' }
          CheckBox { text: 'E-mail' }
          CheckBox { text: 'Calendar' }
          CheckBox { text: 'Contacts' }
        }
      }
      Dialog {
        id: dialog
        title: 'Dialog'
        Label { text: 'The standard dialog.' }
        footer: DialogButtonBox {
          standardButtons: DialogButtonBox.Ok | DialogButtonBox.Cancel
        }
      }
    }
  }
