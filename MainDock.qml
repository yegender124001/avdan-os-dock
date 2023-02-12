import QtQuick 2.15
import Dock 1.0
DockWindow{
    width:item1.width+10
    Rectangle{
        color:bgColor
        radius: 5
        anchors.fill: parent
    }
    Item{
        id: item1
        x:5
        y:5
        height:parent.height-10
        width:row1.width
        Row{
            id:row1
            spacing:10
            DockItem{
                icon.name:"search-icon"
                icon.color:"white"
                width: height
                height: 50
            }

            DockItem{
                icon.name:"start-here-symbolic"
                icon.color:"white"
                width: height
                height: 50
            }

            DockItem{
                icon.name:"desktop-symbolic"
                icon.color:"white"
                width: height
                height: 50
            }
        }
    }
}
