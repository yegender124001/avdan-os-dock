import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
//TaskBar{
//    property color bgColor:"#88000000"
//    property color hoverColor:"#88000000"
//    id: taskBar
//    height:50
//    x:(Screen.width/2)-(width/2)
//    y:Screen.height-height-5
//    Component.onCompleted: enableStruts()
//    visible: true
//}
Window{
    width: 1280
    height: 720
    visible: true
    ListView{
        id: view
        anchors.fill: parent
        model: appModel
        delegate: Rectangle {
            color:"#222"
            implicitWidth: parent.width
            implicitHeight: 50
            Button{
                id: icon
                width: 50
                height: 50
                icon.name:model.iconName
                icon.color:"transparent"
                background:Item{}
            }
            Label{
                id: name
                anchors.left: icon.right
                anchors.verticalCenter: icon.verticalCenter
                color:model.isActive ? "green" : "white"
                text:model.visibleName + "(" + model.windowCount + ")"
            }
        }
    }
    Timer{
        interval: 100
        repeat: true
        running: true
        onTriggered:  {
            console.log(appModel.rowCount())
        }
    }
}
