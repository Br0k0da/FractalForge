import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Window
import Prototype

Window {
  id: root
  title: qsTr("FractalForge")

  width: 1400
  minimumWidth: 1000
  height: 710
  minimumHeight: 500

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
        color: "#EDECDF"

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
            Image {
              id: previewImage
              anchors.fill: parent
            }
          }

          CustomScrollBar {
            id: scrollBar
            anchors {
              bottom: toolsBarMenu.bottom
              left: toolsBarMenu.left
              right: toolsBarMenu.right
              leftMargin: 5
              rightMargin: 5
              bottomMargin: 10
            }
            height: toolsBarMenu.height * 0.35
            onEntered: previewImage.source = someImage
          }
        }
        Rectangle {
          id: buttonsArea
          anchors {
            right: toolsBar.right
            left: toolsBar.left
            bottom: toolsBar.bottom
            bottomMargin: 5
            leftMargin: 5
            rightMargin: 5
          }

          height: toolsBar.height * 0.12
          color: "#00000000"

          CustomButton {
            id: button1
            anchors {
              top: parent.top
              right: parent.right
              rightMargin: width + 5
            }
            width: parent.width * 0.22
            height: parent.height * 0.45

            buttonText: "empty"
            colorDefualt: "#A0A299"
            colorPress: "#B2B4AB"
            colorMouse: "#92938C"
            colorFont: "#EDECDF"

            onClicked: console.log("Кнопка 1 сработала!")
          }

          CustomButton {
            id: button2
            anchors {
              top: parent.top
              right: parent.right
            }
            width: parent.width * 0.22
            height: parent.height * 0.45

            buttonText: "empty"
            colorDefualt: "#C8A591"
            colorPress: "#DCB59F"
            colorMouse: "#B59685"
            colorFont: "#EDECDF"

            onClicked: console.log("Кнопка 2 сработала!")
          }

          CustomButton {
            id: button3
            anchors {
              bottom: parent.bottom
              left: parent.left
            }
            width: parent.width * 0.45
            height: parent.height * 0.45

            buttonText: "Формульный"
            colorDefualt: "#9C9C9C"
            colorPress: "#B2B4AB"
            colorMouse: "#858585"
            colorFont: "#EDECDF"

            onClicked: console.log("Кнопка 3 сработала!")
          }

          CustomButton {
            id: button4
            anchors {
              bottom: parent.bottom
              right: parent.right
            }
            width: parent.width * 0.45
            height: parent.height * 0.45

            buttonText: "Хаотичный"
            colorDefualt: "#9C9C9C"
            colorPress: "#B2B4AB"
            colorMouse: "#858585"
            colorFont: "#EDECDF"

            onClicked: console.log("Кнопка 4 сработала!")
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
        color: "#EDECDF"

        Rectangle {
          id: display
          anchors {
            fill: displayBlock
            margins: 5
          }
          radius: 5
          color: "black"


          FractalWindow {
            Component.onCompleted: {
                xCoord: display.mapToItem(root.parent, 0, 0).x
                yCoord: display.mapToItem(root.parent, 0, 0).y
                zCoord: 0.0
            }

            xCoord: 0
            yCoord: 0
            zCoord: 0
          }
        }
      }
    }
  }

    Component.onCompleted: {
        var globalCoordinares = display.mapToItem(root.parent, 0, 0)
        console.log("X: " + globalCoordinares.x + " y: " + globalCoordinares.y)
    }
}
