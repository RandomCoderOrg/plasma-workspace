/*
 * SPDX-FileCopyrightText: 2011 Marco Martin <notmart@gmail.com>
 * SPDX-FileCopyrightText: 2014, 2019 Kai Uwe Broulik <kde@privat.broulik.de>
 *
 * SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
 */

import QtQuick 2.8
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1

import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.extras 2.0 as PlasmaExtras
import org.kde.kirigami 2.11 as Kirigami

import org.kde.plasma.private.notifications 2.0 as Notifications

// NOTE This wrapper item is needed for QQC ScrollView to work
// In NotificationItem we just do SelectableLabel {} and then it gets confused
// as to which is the "contentItem"
Item {
    id: bodyTextContainer

    property alias text: bodyText.text
    property alias font: bodyText.font

    property int cursorShape

    property QtObject contextMenu: null

    signal clicked(var mouse)
    signal linkActivated(string link)

    implicitWidth: bodyText.paintedWidth
    implicitHeight: bodyText.paintedHeight


    PlasmaExtras.ScrollArea {
        id: bodyTextScrollArea

        anchors.fill: parent

        flickableItem.boundsBehavior: Flickable.StopAtBounds
        flickableItem.flickableDirection: Flickable.VerticalFlick
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff

        TextEdit {
            id: bodyText
            width: bodyTextScrollArea.width
            // TODO check that this doesn't causes infinite loops when it starts adding and removing the scrollbar
            //width: bodyTextScrollArea.viewport.width
            enabled: !Kirigami.Settings.isMobile

            color: PlasmaCore.ColorScope.textColor
            selectedTextColor: theme.viewBackgroundColor
            selectionColor: theme.viewFocusColor
            font.capitalization: theme.defaultFont.capitalization
            font.family: theme.defaultFont.family
            font.italic: theme.defaultFont.italic
            font.letterSpacing: theme.defaultFont.letterSpacing
            font.pointSize: theme.defaultFont.pointSize
            font.strikeout: theme.defaultFont.strikeout
            font.underline: theme.defaultFont.underline
            font.weight: theme.defaultFont.weight
            font.wordSpacing: theme.defaultFont.wordSpacing
            // Work around Qt bug where NativeRendering breaks for non-integer scale factors
            // https://bugreports.qt.io/browse/QTBUG-67007
            renderType: Screen.devicePixelRatio % 1 !== 0 ? Text.QtRendering : Text.NativeRendering
            // Selectable only when we are in desktop mode
            selectByMouse: !Kirigami.Settings.tabletMode
            
            readOnly: true
            wrapMode: Text.Wrap
            textFormat: TextEdit.RichText

            onLinkActivated: bodyTextContainer.linkActivated(link)

            // ensure selecting text scrolls the view as needed...
            onCursorRectangleChanged: {
                var flick = bodyTextScrollArea.flickableItem
                if (flick.contentY >= cursorRectangle.y) {
                    flick.contentY = cursorRectangle.y
                } else if (flick.contentY + flick.height <= cursorRectangle.y + cursorRectangle.height) {
                    flick.contentY = cursorRectangle.y + cursorRectangle.height - flick.height
                }
            }

            // Handle left-click
            Notifications.TextEditClickHandler {
                target: bodyText
                onClicked: {
                    bodyTextContainer.clicked(null);
                }
            }

            // Handle right-click and cursorShape
            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.RightButton

                cursorShape: {
                    if (bodyText.hoveredLink) {
                        return Qt.PointingHandCursor;
                    } else if (bodyText.selectionStart !== bodyText.selectionEnd) {
                        return Qt.IBeamCursor;
                    } else {
                        return bodyTextContainer.cursorShape || Qt.IBeamCursor;
                    }
                }

                onPressed: {
                    contextMenu = contextMenuComponent.createObject(bodyText);
                    contextMenu.link = bodyText.linkAt(mouse.x, mouse.y);

                    contextMenu.closed.connect(function() {
                        contextMenu.destroy();
                        contextMenu = null;
                    });
                    contextMenu.open(mouse.x, mouse.y);
                }
            }
        }
    }

    Component {
        id: contextMenuComponent

        EditContextMenu {
            target: bodyText
        }
    }
}
