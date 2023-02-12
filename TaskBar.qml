import QtQuick 2.15
import Dock 1.0
DockWindow{
    width: itemRow0.width+10
    height:50
    Rectangle{
        color:bgColor
        radius: 5
        anchors.fill: parent
    }
    Behavior on width {
        PropertyAnimation{
            target: taskBar
            property: "width"
            duration: 200
            easing.type: Easing.InCubic
        }
    }
    Row{
        id:itemRow0
        spacing: 10
        height:parent.height-10
        x:5
        y:5
        Repeater{
            id: repeater
            model:appModel
            DockItem{
                icon.name:model.iconName
                icon.width: 60
                icon.height: 60
                width: 50
                height:50
                icon.color:"transparent"
                onClicked: appModel.clicked(model.appId)
                Rectangle{
                    color:model.isActive ? "#44ff44" : "white"
                    anchors.bottom:parent.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    width:10
                    height:3
                    anchors.bottomMargin: 3
                    radius:height
                }
            }
        }
    }
}
