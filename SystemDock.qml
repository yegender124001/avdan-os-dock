import QtQuick 2.15
import Dock 1.0
import QtQuick.Controls 2.15
DockWindow{
    width:item1.width+10
    Rectangle{
        color:bgColor
        radius: 5
        anchors.fill: parent
    }
    Item{
        id:item1
        x:5
        y:5
        width:row1.width
        height:parent.height-10
        Row{
            id: row1
            spacing:5
            DockItem{
                width: height
                height: 50
                Button{
                    width:height
                    height:35
                    icon.width:width
                    icon.height:height
                    background:Item{}
                    icon.name:"folder-wifi"
                    icon.color:"white"
                    anchors.centerIn:parent
                    onClicked: parent.onPressed
                }
            }
            DockItem{
                width: height
                height: 50
                Button{
                    width:height
                    height:35
                    icon.width:width
                    icon.height:height
                    background:Item{}
                    icon.name:"bluetooth-symbolic"
                    icon.color:"white"
                    anchors.centerIn:parent
                    onClicked: parent.onPressed
                }
            }
            DockItem{
                width: height
                height: 50
                Button{
                    width:height
                    height:35
                    icon.width:width
                    icon.height:height
                    background:Item{}
                    icon.name:"battery-charged-symbolic"
                    icon.color:"white"
                    anchors.centerIn:parent
                    onClicked: parent.onPressed
                }
            }
            DockItem{
                width: height
                height: 50
                Button{
                    width:height
                    height:35
                    icon.width:width
                    icon.height:height
                    background:Item{}
                    icon.name:"audio-volume-high"
                    icon.color:"white"
                    anchors.centerIn:parent
                    onClicked: parent.onPressed
                }
            }
            DockItem{
                width: height
                height: 50
                Button{
                    width:height
                    height:35
                    icon.width:width
                    icon.height:height
                    background:Item{}
                    icon.name:"arrow-up"
                    icon.color:"white"
                    anchors.centerIn:parent
                    onClicked: parent.onPressed
                }
            }
        }
    }
}
