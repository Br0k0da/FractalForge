import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Window
import Prototype

Window {
  id: root
  title: qsTr("FractalForge")

  width: 1024
  minimumWidth: 512
  height: 768
  minimumHeight: 384

  visible: true
  // color: "#424242"

    Item {
        anchors.fill: parent
        FractalWindow {
        }
    }



  // GridLayout {
  //   anchors.fill: parent
  //   columns: 2

  //   Item {
  //     Layout.fillWidth: true
  //     Layout.fillHeight: true

  //     Rectangle {
  //       id: toolsBar
  //       anchors {
  //         top: parent.top
  //         bottom: parent.bottom
  //         left: parent.left
  //         margins: 5
  //       }
  //       radius: 5
  //       width: parent.width * 0.6
  //       color: "#EDECDF"

  //       Rectangle {
  //         id: toolsBarMenu
  //         anchors {
  //           left: toolsBar.left
  //           right: toolsBar.right
  //           top: toolsBar.top
  //           margins: 5
  //         }
  //         height: toolsBar.height * 0.8
  //         radius: 5
  //         color: "#A0A299"

  //         Rectangle {
  //           id: preview
  //           anchors {
  //             left: toolsBarMenu.left
  //             right: toolsBarMenu.right
  //             top: toolsBarMenu.top
  //             margins: 5
  //           }
  //           height: toolsBarMenu.height * 0.55
  //           radius: 5
  //           color: "black"
  //         }

  //         CustomScrollBar {
  //           anchors {
  //             bottom: toolsBarMenu.bottom
  //             left: toolsBarMenu.left
  //             right: toolsBarMenu.right
  //             leftMargin: 5
  //             rightMargin: 5
  //             bottomMargin: 10
  //           }
  //           height: toolsBarMenu.height * 0.35
  //         }
  //       }

  //       Rectangle {
  //         id: button1
  //         anchors {
  //           right: toolsBar.right
  //           bottom: toolsBar.bottom
  //           rightMargin: button2.width + 15
  //           bottomMargin: button3.height + 10
  //         }
  //         radius: 20
  //         width: button3.width / 2 - 5
  //         height: toolsBar.height * 0.05
  //         color: if (mouseArea1.containsPress) {
  //                  return "#B2B4AB"
  //                } else if (mouseArea1.containsMouse) {
  //                  return "#92938C"
  //                } else {
  //                  return "#A0A299"
  //                }

  //         Label {
  //           color: "#EDECDF"
  //           text: "empty"
  //           anchors.centerIn: button1
  //           font {
  //             pixelSize: (parent.height + parent.width) * 0.2
  //           }
  //         }

  //         MouseArea {
  //           id: mouseArea1
  //           anchors.fill: parent
  //           hoverEnabled: true
  //         }
  //       }

  //       Rectangle {
  //         id: button2
  //         anchors {
  //           right: toolsBar.right
  //           bottom: toolsBar.bottom
  //           rightMargin: 5
  //           bottomMargin: button3.height + 10
  //         }
  //         radius: 20
  //         width: button3.width / 2 - 5
  //         height: toolsBar.height * 0.05
  //         color: if (mouseArea2.containsPress) {
  //                  return "#DCB59F"
  //                } else if (mouseArea2.containsMouse) {
  //                  return "#B59685"
  //                } else {
  //                  return "#C8A591"
  //                }

  //         Label {
  //           color: "#EDECDF"
  //           text: "empty"
  //           anchors.centerIn: button2
  //           font {
  //             pixelSize: (parent.height + parent.width) * 0.2
  //           }
  //         }

  //         MouseArea {
  //           id: mouseArea2
  //           anchors.fill: parent
  //           hoverEnabled: true
  //         }
  //       }

  //       Rectangle {
  //         id: button3
  //         anchors {
  //           left: toolsBar.left
  //           bottom: toolsBar.bottom
  //           margins: 5
  //         }
  //         radius: 20
  //         width: toolsBar.width * 0.4
  //         height: toolsBar.height * 0.05
  //         color: if (mouseArea3.containsPress) {
  //                  return "#BFBFBF"
  //                } else if (mouseArea3.containsMouse) {
  //                  return "#858585"
  //                } else {
  //                  return "#9C9C9C"
  //                }

  //         Label {
  //           color: "#EDECDF"
  //           text: "Формульный"
  //           anchors.centerIn: button3
  //           font {
  //             pixelSize: (parent.height + parent.width) * 0.12
  //           }
  //         }

  //         MouseArea {
  //           id: mouseArea3
  //           anchors.fill: parent
  //           hoverEnabled: true
  //         }
  //       }

  //       Rectangle {
  //         id: button4
  //         anchors {
  //           right: toolsBar.right
  //           bottom: toolsBar.bottom
  //           margins: 5
  //         }
  //         radius: 20
  //         color: if (mouseArea4.containsPress) {
  //                  return "#BFBFBF"
  //                } else if (mouseArea4.containsMouse) {
  //                  return "#858585"
  //                } else {
  //                  return "#9C9C9C"
  //                }
  //         width: toolsBar.width * 0.4
  //         height: toolsBar.height * 0.05

  //         Label {
  //           color: "#EDECDF"
  //           text: "Хаотичный"
  //           anchors.centerIn: button4
  //           font {
  //             pixelSize: (parent.height + parent.width) * 0.12
  //           }
  //         }

  //         MouseArea {
  //           id: mouseArea4
  //           anchors.fill: parent
  //           hoverEnabled: true
  //         }
  //       }
  //     }
  //   }

  //   Item {
  //     Layout.fillWidth: true
  //     Layout.fillHeight: true

  //     Rectangle {
  //       id: displayBlock
  //       anchors {
  //         top: parent.top
  //         bottom: parent.bottom
  //         right: parent.right
  //         margins: 5
  //       }
  //       radius: 5
  //       width: parent.width * 1.35 - 10
  //       color: "#EDECDF"

  //       Rectangle {
  //         id: display
  //         anchors {
  //           fill: displayBlock
  //           margins: 5
  //         }
  //         radius: 5
  //         color: "black"


  //       }
  //     }
  //   }
  // }
}
