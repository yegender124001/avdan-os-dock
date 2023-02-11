import QtQuick 2.15
import Dock 1.0
import QtQuick.Window 2.15
TaskBar{
    property color bgColor:"#88000000"
    property color hoverColor:"#88000000"
    id: taskBar
    height:50
    x:(Screen.width/2)-(width/2)
    y:Screen.height-height-5
    Component.onCompleted: enableStruts()
    visible: true
}
