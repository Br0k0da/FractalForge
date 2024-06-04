import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Item {
 id: root

 property string someImage

 signal entered
 signal clicked

 Rectangle {
  id: scrollBox
  color: "#00000000"
  anchors.fill: parent
  clip: true

<<<<<<< Updated upstream
    ListView {
      id: scrollAria
      currentIndex: -1
      boundsBehavior: Flickable.StopAtBounds
      width: scrollBox.width
      anchors.fill: scrollBox
      spacing: scrollBox.height * 0.028
      model: ListModel {
        id: scrollModel
        ListElement {
          name: "Множество Мальдерброта"
          someImage: "assets/images/1.jpg"
        }
        ListElement {
          name: "Множество Жюлиа"
          someImage: "assets/images/5.jpg"
        }
        ListElement {
          name: "Треугольник Серписнокого"
          someImage: "assets/images/2.jpg"
        }
        ListElement {
          name: "Ковёр Серписнокого"
          someImage: "assets/images/3.jpg"
        }
        ListElement {
          name: "Снежинка Коха"
          someImage: "assets/images/4.jpg"
        }
        ListElement {
          name: "Some else"
          someImage: "assets/images/5.jpg"
        }
        ListElement {
          name: "Some else"
          someImage: "assets/images/6.jpg"
        }
        ListElement {
          name: "Some else"
          someImage: "assets/images/7.jpg"
        }
      }

      delegate: Rectangle {
        id: delegate
        height: scrollBox.height * 0.18
        width: scrollBox.width
        bottomRightRadius: 20
        topRightRadius: 20

        color: if (ListView.isCurrentItem) {
                 return "#E0E9C4"
               } else if (mouseArea.containsPress) {
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
            root.someImage = scrollModel.get(index).someImage
            root.entered()
          }

          onClicked: {
            scrollAria.currentIndex = index
            root.clicked()
          }
        }
      }
=======
  ListView {
   id: scrollAria
   currentIndex: -1
   boundsBehavior: Flickable.StopAtBounds
   width: scrollBox.width
   anchors.fill: scrollBox
   spacing: scrollBox.height * 0.028
   model: ListModel {
    id: scrollModel
    ListElement {
     name: "Множество Мальдерброта"
     someImage: "assets/images/1.png"
>>>>>>> Stashed changes
    }
    ListElement {
     name: "Множество Жюлиа"
     someImage: "assets/images/2.png"
    }
    ListElement {
     name: "Треугольник Серписнокого"
     someImage: "assets/images/3.png"
    }
    ListElement {
     name: "Ковёр Серписнокого"
     someImage: "assets/images/4.png"
    }
    ListElement {
     name: "Снежинка Коха"
     someImage: "assets/images/5.png"
    }
    ListElement {
     name: "Some else"
     someImage: "assets/images/6.png"
    }
    ListElement {
     name: "Some else"
     someImage: "assets/images/6.png"
    }
    ListElement {
     name: "Some else"
     someImage: "assets/images/6.png"
    }
   }

   delegate: Rectangle {
    id: delegate
    height: scrollBox.height * 0.18
    width: scrollBox.width
    bottomRightRadius: 20
    topRightRadius: 20

    color: if (ListView.isCurrentItem) {
            return "#E0E9C4"
           } else if (mouseArea.containsPress) {
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
      root.someImage = scrollModel.get(index).someImage
      root.entered()
     }

     onClicked: {
      scrollAria.currentIndex = index

      fractalWindow.fractalType = index + 1

      root.clicked()
     }
    }
   }
  }
 }
}
