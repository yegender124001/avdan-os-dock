import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.0
import Dock 1.0
import QtQuick.Window 2.15
DockWindow{
    width: itemRow0.width+10
    height:50
    id: root
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
                id: item
                icon.name:model.iconName
                icon.width: 60
                icon.height: 60
                width: 50
                height:50
                icon.color:"transparent"
                MouseArea{
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    onClicked: {
                        if (mouse.button === Qt.RightButton) {
                            if (model.isPinned){
                                appModel.unPin(model.appId)
                            } else {
                                appModel.pin(model.appId)
                            }
                        }
                        else
                            appModel.clicked(model.appId)
                    }
                }
                Rectangle{
                    color:"#88000000"
                    radius:height
                    border.color: "#444"
                    border.width: 1
                    width: 20
                    anchors.right: parent.right
                    anchors.top: parent.top
                    visible: model.windowCount > 1
                    z:1
                    height:20
                    Label{
                        color:"white"
                        text:model.windowCount
                        anchors.centerIn: parent
                    }
                }

                Rectangle{
                    color:model.isActive ? "#44ff44" : "white"
                    anchors.bottom:parent.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    width:10
                    height:3
                    anchors.bottomMargin: 3
                    radius:height
                    visible: model.windowCount > 0
                }
            }
        }
    }
}
