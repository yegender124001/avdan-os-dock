import QtQuick 2.15
import Dock 1.0
import QtQuick.Controls 2.15
HamburgerMenu {
    height:clm.height+10
    width: 200
    Rectangle{
        color:"#88000000"
        radius:5
        anchors.fill: parent
        border.color: "#444"
        border.width: 1
    }
    Column{
        anchors.topMargin: 5
        id: clm
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 5
        spacing: 0
        DockItem{
            width: parent.width
            height:30
            Label{
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                text:"Open new instance"
                color:"white"
            }
        }

        DockItem{
            width: parent.width
            height:30
            Label{
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                text:"Pin to dock"
                color:"white"
            }
        }
        Rectangle{
            color:"#888"
            width: parent.width-10
            anchors.horizontalCenter: parent.horizontalCenter
            height:1
        }
        DockItem{
            width: parent.width
            height:30
            Label{
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                text:"Close all"
                color:"white"
            }
        }
    }
}
