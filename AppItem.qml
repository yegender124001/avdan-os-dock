import QtQuick 2.15
import Dock 1.0

DockItem{
    id: appItem
    icon.name:modelData.iconName
    icon.color:"transparent"
    icon.width: 48
    icon.height: 48
}
