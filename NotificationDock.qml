import QtQuick 2.15
import Dock 1.0
import QtQuick.Controls 2.15
DockWindow{
    width:300
    Rectangle{
        color:bgColor
        radius: 5
        anchors.fill: parent
    }
    Item{
        width: parent.width-20
        height: parent.height-10
        x:10
        y:5
        Label{
            color:"white"
            y:(parent.height/2)-height
            font.pixelSize: 15
            Timer{
                interval:100
                repeat:true
                triggeredOnStart: true
                running: true
                onTriggered: parent.text = Qt.formatTime(new Date(), "hh:mm AP")
            }
        }
        Label{
            color:"white"
            font.pixelSize: 15
            y:(parent.height/2)
            Timer{
                interval:100
                repeat:true
                triggeredOnStart: true
                running: true
                onTriggered: parent.text = Qt.formatDate(new Date(), "MMMM d, yyyy")
            }
        }
        DockItem{
            anchors.right:parent.right
            anchors.verticalCenter: parent.verticalCenter
            Rectangle{
                anchors.centerIn: parent
                radius:height
                height:parent.height/1.7
                width: height
                color:"#33ffffff"
                Label{
                    color:"white"
                    anchors.centerIn: parent
                    text:"3"
                }
            }
        }
    }
}
