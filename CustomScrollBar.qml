import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Item {
  id: root

  signal clicked

  Rectangle {
    id: scrollBox
    color: "#00000000"
    anchors.fill: parent
    clip: true

    ListView {
      id: scrollAria
      boundsBehavior: Flickable.StopAtBounds
      width: scrollBox.width
      anchors.fill: scrollBox
      spacing: scrollBox.height * 0.028
      model: ListModel {
        ListElement {
          name: "Снежинка Коха"
        }
        ListElement {
          name: "Треугольник Серписнокого"
        }
        ListElement {
          name: "Фракталы Пьера Фату"
        }
        ListElement {
          name: "Множество Мальдерброта"
        }
        ListElement {
          name: "Some else"
        }
        ListElement {
          name: "Some else"
        }
        ListElement {
          name: "Some else"
        }
      }

      delegate: Rectangle {
        height: scrollBox.height * 0.18
        width: scrollBox.width
        bottomRightRadius: 20
        topRightRadius: 20

        color: if (mouseArea.containsPress) {
                 return "#FFFEEE"
               } else if (mouseArea.containsMouse) {
                 return "#DBDAD0"
               } else {
                 return "#EDECDF"
               }

        Label {
          anchors {
            left: parent.left
            verticalCenter: parent.verticalCenter
            leftMargin: 5
          }
          text: name
          font {
            pixelSize: (parent.height + parent.width) * 0.055
          }
          color: "black"
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
  }
}
