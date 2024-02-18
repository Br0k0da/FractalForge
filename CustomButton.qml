import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Item {
  id: root
  required property string buttonText
  required property string colorDefualt
  required property string colorPress
  required property string colorMouse
  required property string colorFont
  Rectangle {
    radius: 20
    anchors.fill: parent
    color: if (mouseArea.containsPress) {
             return colorPress
           } else if (mouseArea.containsMouse) {
             return colorMouse
           } else {
             return colorDefualt
           }

    Label {
      color: colorFont
      text: buttonText
      anchors.centerIn: parent
      font {
        pixelSize: (root.parent.height + root.parent.width) * 0.05
      }
    }

    MouseArea {
      id: mouseArea
      anchors.fill: parent
      hoverEnabled: true
    }
  }
}
