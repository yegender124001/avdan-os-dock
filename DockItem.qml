import QtQuick.Controls 2.15
import QtQuick 2.15
Button{
    width: 40
    height: 40
    icon.width: 48
    icon.height: 48
    icon.color: "white"
    id: button
    states: [
        State {
            name: "normal"
            when: button.hovered == false
            PropertyChanges {
                target:background
                color:"transparent"
            }
        },
        State {
            name: "pressed"
            when:button.pressed == true
            PropertyChanges {
                target: background
                width: button.width-5
                height: button.height-5
            }
        }
    ]
    transitions: Transition {
        reversible: true
        ParallelAnimation{
            PropertyAnimation{duration:50; target: background; properties: "width,height"; easing.type: Easing.InCubic}
            ColorAnimation {
                duration: 50
                easing.type: Easing.InCubic
                target: background
            }
        }
    }
    background: Rectangle{
        id: background
        color: hoverColor
        radius: 5
        anchors.centerIn: parent
    }
}
