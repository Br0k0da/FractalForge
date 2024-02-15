import QtQuick
import QtQuick.Layouts

Window {
  id: root

  width: 1024
  minimumWidth: 512
  height: 768
  minimumHeight: 384

  visible: true
  color: "#424242"
  title: qsTr("FractalForge")

  GridLayout {
    anchors.fill: parent

    columns: 2

    Item {
      Layout.fillWidth: true
      Layout.fillHeight: true

      Rectangle {
        id: toolsBar
        anchors {
          top: parent.top
          bottom: parent.bottom
          left: parent.left
          margins: 5
        }
        radius: 5
        width: parent.width * 0.6
        color: "white"

        Rectangle {
          id: toolsBarMenu
          anchors {
            left: toolsBar.left
            right: toolsBar.right
            top: toolsBar.top
            margins: 5
          }
          height: toolsBar.height * 0.7
          radius: 5
          color: "gray"

          Rectangle {
            id: preview
            anchors {
              left: toolsBarMenu.left
              right: toolsBarMenu.right
              top: toolsBarMenu.top
              margins: 5
            }
            height: toolsBarMenu.height * 0.5
            radius: 5
            color: "black"
          }
        }
      }
    }

    Item {
      Layout.fillWidth: true
      Layout.fillHeight: true

      Rectangle {
        id: displayBlock
        anchors {
          top: parent.top
          bottom: parent.bottom
          right: parent.right
          margins: 5
        }
        radius: 5
        width: parent.width * 1.35 - 10
        color: "white"

        Rectangle {
          id: display
          anchors {
            fill: displayBlock
            margins: 5
          }
          radius: 5
          color: "black"
        }
      }
    }
  }
}
