import QtQuick
import QtQuick.Layouts

Window {
  id: root

  width: 1024
  height: 768
  visible: true
  color: "#424242"
  title: qsTr("FractalForge")

  GridLayout {
    anchors.fill: parent

    columns: 2
    columnSpacing: -10

    Item {
      Layout.fillWidth: true
      Layout.fillHeight: true

      Rectangle {
        anchors {}

        x: 10
        y: 10

        radius: height * 0.01

        width: parent.width * 0.55
        height: parent.height - 20

        color: "white"
      }
    }

    Item {
      Layout.fillWidth: true
      Layout.fillHeight: true

      Rectangle {
        anchors {}

        y: 10
        x: -(parent.width * 0.35)

        radius: height * 0.01

        width: parent.width * 1.35 - 10
        height: parent.height - 20

        color: "white"
      }
    }
  }
}
