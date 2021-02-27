/********************************************************************
This file is part of the KDE project.

SPDX-FileCopyrightText: 2014 Martin Gräßlin <mgraesslin@kde.org>
SPDX-FileCopyrightText: 2014 Kai Uwe Broulik <kde@privat.broulik.de>

SPDX-License-Identifier: GPL-2.0-or-later
*********************************************************************/
import QtQuick 2.4
import QtQuick.Layouts 1.1

import org.kde.plasma.plasmoid 2.0
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.components 3.0 as PlasmaComponents3
import org.kde.plasma.extras 2.0 as PlasmaExtras

ColumnLayout {
    Keys.onPressed: {
        switch(event.key) {
            case Qt.Key_Up: {
                clipboardMenu.view.decrementCurrentIndex();
                event.accepted = true;
                break;
            }
            case Qt.Key_Down: {
                clipboardMenu.view.incrementCurrentIndex();
                event.accepted = true;
                break;
            }
            case Qt.Key_Enter:
            case Qt.Key_Return: {
                if (clipboardMenu.view.currentIndex >= 0) {
                    var uuid = clipboardMenu.model.get(clipboardMenu.view.currentIndex).UuidRole
                    if (uuid) {
                        clipboardSource.service(uuid, "select")
                        clipboardMenu.view.currentIndex = 0
                        if (plasmoid.hideOnWindowDeactivate) {
                            plasmoid.expanded = false;
                        }
                    }
                }
                break;
            }
            case Qt.Key_Escape: {
                if (filter.text != "") {
                    filter.text = "";
                    event.accepted = true;
                }
                break;
            }
            default: { // forward key to filter
                // filter.text += event.text wil break if the key is backspace
                if (event.key === Qt.Key_Backspace && filter.text == "") {
                    return;
                }
                if (event.text !== "" && !filter.activeFocus) {
                    clipboardMenu.view.currentIndex = -1
                    if (event.matches(StandardKey.Paste)) {
                        filter.paste();
                    } else {
                        filter.text = "";
                        filter.text += event.text;
                    }
                    filter.forceActiveFocus();
                    event.accepted = true;
                }
            }
        }
    }

    property var header: PlasmaExtras.PlasmoidHeading {
        RowLayout {
            anchors.fill: parent
            enabled: clipboardMenu.model.count > 0 || filter.text.length > 0

            PlasmaComponents3.TextField {
                id: filter
                placeholderText: i18n("Search...")
                clearButtonShown: true
                Layout.fillWidth: true

                Connections {
                    target: main
                    function onClearSearchField() {
                        filter.clear()
                    }
                }
            }
            PlasmaComponents3.ToolButton {
                visible: !(plasmoid.containmentDisplayHints & PlasmaCore.Types.ContainmentDrawsPlasmoidHeading)

                icon.name: "edit-clear-history"
                onClicked: {
                    clipboardSource.service("", "clearHistory")
                    filter.clear()
                }

                PlasmaComponents3.ToolTip {
                    text: i18n("Clear history")
                }
            }
        }
    }

    Menu {
        id: clipboardMenu
        model: PlasmaCore.SortFilterModel {
            sourceModel: clipboardSource.models.clipboard
            filterRole: "DisplayRole"
            filterRegExp: filter.text
        }
        supportsBarcodes: {
            try {
                let prisonTest = Qt.createQmlObject("import QtQml 2.0; import org.kde.prison 1.0; QtObject {}", this);
                prisonTest.destroy();
            } catch (e) {
                console.log("Barcodes not supported:", e);
                return false;
            }
            return true;
        }
        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.topMargin: units.smallSpacing
        onItemSelected: clipboardSource.service(uuid, "select")
        onRemove: clipboardSource.service(uuid, "remove")
        onEdit: clipboardSource.edit(uuid)
        onBarcode: {
            stack.push(barcodePage, {
                text: text
            });
        }
        onAction: {
            clipboardSource.service(uuid, "action")
            clipboardMenu.view.currentIndex = 0
        }
    }
}
