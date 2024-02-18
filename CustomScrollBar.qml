import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Item {
  id: root

  signal entered
  property string someImage: ""

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
        id: scrollModel
        ListElement {
          name: "Снежинка Коха"
          property string sImage: "assets/images/1.jpg"
        }
        ListElement {
          name: "Треугольник Серписнокого"
          property string sImage: "assets/images/2.jpg"
        }
        ListElement {
          name: "Фракталы Пьера Фату"
          property string sImage: "assets/images/3.jpg"
        }
        ListElement {
          name: "Множество Мальдерброта"
          property string sColor: "green"
          property string sImage: "assets/images/4.jpg"
        }
        ListElement {
          name: "Some else"
          property string sImage: "assets/images/5.jpg"
        }
        ListElement {
          name: "Some else"
          property string sImage: "assets/images/6.jpg"
        }
        ListElement {
          name: "Some else"
          property string sImage: "assets/images/7.jpg"
        }
      }

      delegate: Rectangle {
        id: delegate
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

          onEntered: {
            sImage: scrollModel.get(index).sImage
            sfunctons.setSomeColor(sImage)
            root.entered()
          }
        }
        QtObject {
          id: sfunctons

          function setSomeColor(sImage) {
            root.someImage = sImage
          }
        }
      }
    }
  }
}
