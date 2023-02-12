import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import Dock 1.0
Item{
    property color bgColor:"#88000000"
    property color hoverColor:"#88000000"
    TaskBar{
        id: taskBar
        height:60
        x:(Screen.width/2)-((width+mainBar.width+notificationBar.width+systemBar.width)/2)
        y:Screen.height-height-5
        Component.onCompleted: enableStruts()
        visible: true
    }
    MainDock{
        id: mainBar
        height:60
        x:taskBar.x+taskBar.width+10
        y:taskBar.y
        visible: true
    }
    NotificationDock{
        id: notificationBar
        height:60
        x:mainBar.x+mainBar.width+10
        y:taskBar.y
        visible: true
    }
    SystemDock{
        id: systemBar
        height:60
        x:notificationBar.x+notificationBar.width+10
        y:taskBar.y
        visible: true
    }
}
