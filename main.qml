import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.15
ApplicationWindow {
    width: 1280
    Material.theme: Material.Dark
    Material.accent: Material.Cyan
    height: 720
    visible: true
    title: qsTr("Configuration")
    TabBar{
        id: tabBar
        width: parent.width
        height: 50
        currentIndex: stack.currentIndex
        TabButton{
            text:"Layouts"
            height: parent.height
            onClicked: stack.currentIndex = 0
        }
        TabButton{
            text:"Colors"
            height: parent.height
            onClicked: stack.currentIndex = 1
        }
        TabButton{
            text:"Behaviour"
            height: parent.height
            onClicked: stack.currentIndex = 2
        }
        TabButton{
            text:"Animations"
            height: parent.height
            onClicked: stack.currentIndex = 3
        }
        TabButton{
            text:"Tasks"
            height: parent.height
            onClicked: stack.currentIndex = 4
        }
    }
    SwipeView{
        id: stack
        anchors.top: tabBar.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        Item{
            id:layoutsTab
            Label{
                text:"Layouts"
                anchors.centerIn: parent
            }
        }
        Item{
            id:colorsTab
            Label{
                text:"Colors"
                anchors.centerIn: parent
            }
        }
        Item{
            id:behaviourTab
            Label{
                text:"Behaviour"
                anchors.centerIn: parent
            }
        }
        Item{
            id:animationsTab
            Label{
                text:"Animations"
                anchors.centerIn: parent
            }
        }
        Item{
            id:tasksTab
            Label{
                text:"Tasks"
                anchors.centerIn: parent
            }
        }
    }
}
