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
        spacing: 5
        height:parent.height-10
        x:5
        y:5
        /*Pinned Apps*/
        Repeater{
            //model:ListModel{
            //    ListElement{iconName:"konsole"}
            //    ListElement{iconName:"qtcreator"}
            //    ListElement{iconName:"kate"}
            //    ListElement{iconName:"kcalc"}
            //}
            //model:appModel
            //delegate:DockItem{
            //    icon.name:model.iconName
            //    icon.color:"transparent"
            //    icon.width: 48
            //    icon.height: 48
            //}
            id: repeater
            model:5
            DockItem{
                icon.name:model.iconName ? model.iconName : "application-x-desktop"
                icon.width: 48
                icon.height: 48
                onClicked: repeater.model += 5
            }
        }
        //Rectangle{
        //    anchors.verticalCenter: parent.verticalCenter
        //    width: 1
        //    height:30
        //}
    }
    
}
