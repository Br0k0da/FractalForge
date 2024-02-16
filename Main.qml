import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Window

Window {
  id: root
  title: qsTr("FractalForge")

  width: 1024
  minimumWidth: 512
  height: 768
  minimumHeight: 384

  visible: true
  color: "#424242"

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
          height: toolsBar.height * 0.8
          radius: 5
          color: "#A0A299"

          Rectangle {
            id: preview
            anchors {
              left: toolsBarMenu.left
              right: toolsBarMenu.right
              top: toolsBarMenu.top
              margins: 5
            }
            height: toolsBarMenu.height * 0.55
            radius: 5
            color: "black"
          }

          ScrollElementsBar {
            anchors {
              bottom: toolsBarMenu.bottom
              left: toolsBarMenu.left
              right: toolsBarMenu.right
              leftMargin: 5
              rightMargin: 5
              bottomMargin: 5
            }
            height: toolsBarMenu.height * 0.4
          }
        }

        Button {
          id: button1
          anchors {
            right: toolsBar.right
            bottom: toolsBar.bottom
            rightMargin: button2.width + 15
            bottomMargin: button3.height + 10
          }
          text: "1"
          width: button3.width / 2 - 5
          height: toolsBar.height * 0.05
        }

        Button {
          id: button2
          anchors {
            right: toolsBar.right
            bottom: toolsBar.bottom
            rightMargin: 5
            bottomMargin: button3.height + 10
          }
          text: "2"
          width: button3.width / 2 - 5
          height: toolsBar.height * 0.05
        }

        Button {
          id: button3
          anchors {
            left: toolsBar.left
            bottom: toolsBar.bottom
            margins: 5
          }
          text: "3"
          width: toolsBar.width * 0.4
          height: toolsBar.height * 0.05
        }

        Button {
          id: button4
          anchors {
            right: toolsBar.right
            bottom: toolsBar.bottom
            margins: 5
          }
          text: "4"
          width: toolsBar.width * 0.4
          height: toolsBar.height * 0.05
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
