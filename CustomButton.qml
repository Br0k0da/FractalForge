import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Item {
  id: root

  property string buttonText
  property string colorDefualt
  property string colorPress
  property string colorMouse
  property string colorFont

  signal clicked

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

      onClicked: {
        root.clicked()
      }
    }
  }
}
