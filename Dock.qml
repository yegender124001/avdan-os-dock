import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
Item{

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

DockWindow{
    
}
}