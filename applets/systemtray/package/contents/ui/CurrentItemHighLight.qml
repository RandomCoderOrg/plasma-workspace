/*
 *   Copyright 2011 Marco Martin <mart@kde.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 2, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Library General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

import QtQuick 2.12
import org.kde.plasma.plasmoid 2.0
import org.kde.plasma.core 2.0 as PlasmaCore

PlasmaCore.FrameSvgItem {
    id: currentItemHighLight

    property int location

    property bool animationEnabled: true
    property var highlightedItem: null

    property var containerMargins: {
        var item = currentItemHighLight;
        while (item.parent) {
            item = item.parent;
            if (item.isAppletContainer) {
                return item.getMargins;
            }
        }
        return undefined;
    }

    z: -1 // always draw behind icons
    opacity: systemTrayState.expanded ? 1 : 0

    imagePath: "widgets/tabbar"
    prefix: {
        var prefix = ""
        switch (location) {
            case PlasmaCore.Types.LeftEdge:
                prefix = "west-active-tab";
                break;
            case PlasmaCore.Types.TopEdge:
                prefix = "north-active-tab";
                break;
            case PlasmaCore.Types.RightEdge:
                prefix = "east-active-tab";
                break;
            default:
                prefix = "south-active-tab";
            }
            if (!hasElementPrefix(prefix)) {
                prefix = "active-tab";
            }
            return prefix;
    }

    // update when System Tray is expanded - applet activated or hidden icons shown
    Connections {
        target: systemTrayState

        function onActiveAppletChanged() {
            Qt.callLater(updateHighlightedItem);
        }

        function onExpandedChanged() {
            Qt.callLater(updateHighlightedItem);
        }
    }

    // update when applet changes parent (e.g. moves from active to hidden icons)
    Connections {
        target: systemTrayState.activeApplet

        function onParentChanged() {
            Qt.callLater(updateHighlightedItem);
        }
    }

    // update when System Tray size changes
    Connections {
        target: parent

        function onWidthChanged() {
            Qt.callLater(updateHighlightedItem);
        }

        function onHeightChanged() {
            Qt.callLater(updateHighlightedItem);
        }
    }

    // update when scale of newly added tray item changes (check 'add' animation in GridView in main.qml)
    Connections {
        target: !!highlightedItem && highlightedItem.parent ? highlightedItem.parent : null

        function onScaleChanged() {
            Qt.callLater(updateHighlightedItem);
        }
    }

    function updateHighlightedItem() {
        if (systemTrayState.expanded) {
            if (systemTrayState.activeApplet && systemTrayState.activeApplet.parent && systemTrayState.activeApplet.parent.inVisibleLayout) {
                changeHighlightedItem(systemTrayState.activeApplet.parent.container, false);
            } else { // 'Show hiden items' popup
                changeHighlightedItem(parent, true);
            }
        } else {
            highlightedItem = null;
        }
    }

    function changeHighlightedItem(nextItem, forceEdgeHighlight) {
        // do not animate the first appearance
        // or when the property value of a highlighted item changes
        if (!highlightedItem || (highlightedItem === nextItem)) {
            animationEnabled = false;
        }

        const p = parent.mapFromItem(nextItem, 0, 0);
        if (containerMargins && (parent.oneRowOrColumn || forceEdgeHighlight)) {
            x = p.x - containerMargins('left', true);
            y = p.y - containerMargins('top', true);
            width = nextItem.width + containerMargins('left', true) + containerMargins('right', true);
            height = nextItem.height + containerMargins('bottom', true) + containerMargins('top', true);
        } else {
            x = p.x;
            y = p.y;
            width = nextItem.width
            height = nextItem.height
        }

        highlightedItem = nextItem;
        animationEnabled = true;
    }

    Behavior on opacity {
        NumberAnimation {
            duration: PlasmaCore.Units.longDuration
            easing.type: systemTrayState.expanded ? Easing.OutCubic : Easing.InCubic
        }
    }
    Behavior on x {
        id: xAnim
        enabled: animationEnabled
        NumberAnimation {
            duration: PlasmaCore.Units.longDuration
            easing.type: Easing.InOutCubic
        }
    }
    Behavior on y {
        id: yAnim
        enabled: animationEnabled
        NumberAnimation {
            duration: PlasmaCore.Units.longDuration
            easing.type: Easing.InOutCubic
        }
    }
    Behavior on width {
        id: widthAnim
        enabled: animationEnabled
        NumberAnimation {
            duration: PlasmaCore.Units.longDuration
            easing.type: Easing.InOutCubic
        }
    }
    Behavior on height {
        id: heightAnim
        enabled: animationEnabled
        NumberAnimation {
            duration: PlasmaCore.Units.longDuration
            easing.type: Easing.InOutCubic
        }
    }
}
