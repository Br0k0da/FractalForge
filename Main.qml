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
        anchors {
          top: parent.top
          bottom: parent.bottom
          left: parent.left
          margins: 5
        }
        radius: 5
        width: parent.width * 0.6
        color: "white"

        GridLayout {
          anchors.fill: parent
          Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Rectangle {
              anchors {
                left: parent.left
                right: parent.right
                top: parent.top
                margins: 5
              }
              height: parent.height * 0.7
              radius: 5
              color: "gray"
              GridLayout {
                anchors.fill: parent
                columns: 1
                columnSpacing: 10
                Item {
                  Layout.fillWidth: true
                  Layout.fillHeight: true
                  Rectangle {
                    anchors {
                      left: parent.left
                      right: parent.right
                      top: parent.top
                      margins: 5
                    }
                    height: parent.height * 0.5
                    radius: 5
                    color: "black"
                  }
                }
              }
            }
          }
        }
      }
    }

    Item {
      Layout.fillWidth: true
      Layout.fillHeight: true

      Rectangle {
        anchors {
          top: parent.top
          bottom: parent.bottom
          right: parent.right
          margins: 5
        }
        radius: 5
        width: parent.width * 1.35 - 10
        color: "white"

        GridLayout {
          anchors.fill: parent
          Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Rectangle {
              anchors {
                fill: parent
                margins: 5
              }
              radius: 5
              color: "black"
            }
          }
        }
      }
    }
  }
}
