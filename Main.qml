import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Window
import Prototype
import fractalforge.ButtonController

Window {
    id: root
    title: qsTr("FractalForge")

    width: 1400
    minimumWidth: 1400
    height: 710
    minimumHeight: 710

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

                        onClicked: {

                        }
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

                        onClicked: {

                        }
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

                        onClicked: {
                            ButtonController.fractalType = 0
                            console.log(ButtonController.fractalType)
                        }
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

                        onClicked: {
                            ButtonController.fractalType = 1
                            console.log(ButtonController.fractalType)
                        }
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

                    MouseArea {
                        id: fractalWindowMouseArea
                        anchors.fill: display

                        property var prevXOffset
                        property var prevYOffset
                        property var time;

                        onPressed: (mouse) => {
                            prevXOffset = mouse.x
                            prevYOffset = mouse.y
                            time = Date.now()
                            console.log("prevYOffset: " + prevYOffset)
                            console.log("mouse.y: " + mouse.y)
                        }

                        onPositionChanged: (mouse) => {

                            if(pressedButtons == Qt.LeftButton)
                            {
                                var xDistinction = mouse.x - prevXOffset
                                var yDistinction = mouse.y - prevYOffset
                                var velocity = Math.sqrt(xDistinction*xDistinction+yDistinction*yDistinction)/(Date.now() - time)

                                // console.log("xDist: " + xDistinction)

                                if(velocity > 5)
                                {
                                    velocity = 5.0
                                }

                                if(velocity < 1)
                                {
                                    velocity = 1.0
                                }

                                if(fractalWindow.fScale < 1)
                                {
                                    velocity -= fractalWindow.fScale
                                }

                                fractalWindow.xOffset += xDistinction / fractalWindow.width * velocity
                                fractalWindow.yOffset += yDistinction / fractalWindow.height * velocity

                                display.update()
                            }

                            prevXOffset = mouse.x
                            prevYOffset = mouse.y
                            time = Date.now()
                        }

                        onWheel: (wheel) =>
                                 {
                                     if(wheel.angleDelta.y < 0)
                                     {
                                         fractalWindow.fScale *= 1.05
                                         display.update()
                                     } else {
                                         fractalWindow.fScale *= 0.95
                                         display.update()
                                     }
                                 }

                        FractalWindow {
                            id: fractalWindow
                            anchors.fill: fractalWindowMouseArea
                        }
                    }
                }
            }
        }
    }
}
