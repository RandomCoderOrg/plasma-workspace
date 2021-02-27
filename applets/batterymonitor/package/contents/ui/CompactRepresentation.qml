/*
*   SPDX-FileCopyrightText: 2011 Sebastian Kügler <sebas@kde.org>
*   SPDX-FileCopyrightText: 2011 Viranch Mehta <viranch.mehta@gmail.com>
*   SPDX-FileCopyrightText: 2013 Kai Uwe Broulik <kde@privat.broulik.de>
*
*   SPDX-License-Identifier: LGPL-2.0-or-later
*/

import QtQuick 2.0
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.workspace.components 2.0 as WorkspaceComponents

MouseArea {
    id: root

    property real itemSize: Math.min(root.height, root.width/view.count)
    readonly property bool isConstrained: plasmoid.formFactor === PlasmaCore.Types.Vertical || plasmoid.formFactor === PlasmaCore.Types.Horizontal
    property int wheelDelta: 0


    onClicked: plasmoid.expanded = !plasmoid.expanded
    onEntered: wheelDelta = 0
    onExited: wheelDelta = 0
    onWheel: {
        var delta = wheel.angleDelta.y || wheel.angleDelta.x

        var maximumBrightness = batterymonitor.maximumScreenBrightness
        // Don't allow the UI to turn off the screen
        // Please see https://git.reviewboard.kde.org/r/122505/ for more information
        var minimumBrightness = (maximumBrightness > 100 ? 1 : 0)
        var steps = Math.max(1, Math.round(maximumBrightness / 20))
        var deltaSteps = delta / 120;
        batterymonitor.screenBrightness = Math.max(minimumBrightness, Math.min(maximumBrightness, batterymonitor.screenBrightness + deltaSteps * steps));
    }


    //Should we consider turning this into a Flow item?
    Row {
        anchors.centerIn: parent
        Repeater {
            id: view

            property bool hasBattery: batterymonitor.pmSource.data["Battery"]["Has Cumulative"]
            property bool singleBattery: root.isConstrained || !view.hasBattery

            model: singleBattery ? 1 : batterymonitor.batteries

            Item {
                id: batteryContainer

                property bool hasBattery: view.singleBattery ? view.hasBattery : model["Plugged in"]
                property int percent: view.singleBattery ? pmSource.data["Battery"]["Percent"] : model["Percent"]
                property bool pluggedIn: pmSource.data["AC Adapter"] && pmSource.data["AC Adapter"]["Plugged in"] && (view.singleBattery || model["Is Power Supply"])

                height: root.itemSize
                width: root.width/view.count

                property real iconSize: Math.min(width, height)

                WorkspaceComponents.BatteryIcon {
                    id: batteryIcon

                    anchors.centerIn: parent
                    height: root.isConstrained ? batteryContainer.iconSize : batteryContainer.iconSize - batteryLabel.height
                    width: height

                    hasBattery: batteryContainer.hasBattery
                    percent: batteryContainer.percent
                    pluggedIn: batteryContainer.pluggedIn
                }

                BadgeOverlay {
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right

                    visible: plasmoid.configuration.showPercentage

                    text: batteryContainer.hasBattery ? i18nc("battery percentage below battery icon", "%1%", percent) : i18nc("short symbol to signal there is no battery currently available", "-")
                    icon: batteryIcon
                }
            }
        }
    }
}
