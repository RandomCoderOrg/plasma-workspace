/*
 * KCMStyle
 * SPDX-FileCopyrightText: 2002 Karol Szwed <gallium@kde.org>
 * SPDX-FileCopyrightText: 2002 Daniel Molkentin <molkentin@kde.org>
 * SPDX-FileCopyrightText: 2007 Urs Wolfer <uwolfer @ kde.org>
 * SPDX-FileCopyrightText: 2019 Kai Uwe Broulik <kde@broulik.de>
 * SPDX-FileCopyrightText: 2019 Cyril Rossi <cyril.rossi@enioka.com>
 *
 * Portions Copyright (C) TrollTech AS.
 *
 * Based on kcmdisplay
 * SPDX-FileCopyrightText: 1997-2002 kcmdisplay Authors.
 * (see Help -> About Style Settings)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef KCMSTYLE_H
#define KCMSTYLE_H

#include <QPointer>

#include <KQuickAddons/ManagedConfigModule>

#include "gtkpage.h"

class QQuickItem;

class StyleSettings;
class StyleData;
class StylesModel;
class StyleConfigDialog;

class KCMStyle : public KQuickAddons::ManagedConfigModule
{
    Q_OBJECT

    Q_PROPERTY(GtkPage *gtkPage READ gtkPage CONSTANT)
    Q_PROPERTY(StylesModel *model READ model CONSTANT)
    Q_PROPERTY(StyleSettings *styleSettings READ styleSettings CONSTANT)
    Q_PROPERTY(ToolBarStyle mainToolBarStyle READ mainToolBarStyle WRITE setMainToolBarStyle NOTIFY mainToolBarStyleChanged)
    Q_PROPERTY(ToolBarStyle otherToolBarStyle READ otherToolBarStyle WRITE setOtherToolBarStyle NOTIFY otherToolBarStyleChanged)
    Q_PROPERTY(bool gtkConfigKdedModuleLoaded READ gtkConfigKdedModuleLoaded NOTIFY gtkConfigKdedModuleLoadedChanged)

public:
    KCMStyle(QObject *parent, const QVariantList &args);
    ~KCMStyle() override;

    enum ToolBarStyle {
        NoText,
        TextOnly,
        TextBesideIcon,
        TextUnderIcon,
    };
    Q_ENUM(ToolBarStyle)

    GtkPage *gtkPage();

    StylesModel *model() const;

    StyleSettings *styleSettings() const;

    ToolBarStyle mainToolBarStyle() const;
    void setMainToolBarStyle(ToolBarStyle style);
    Q_SIGNAL void mainToolBarStyleChanged();

    ToolBarStyle otherToolBarStyle() const;
    void setOtherToolBarStyle(ToolBarStyle style);
    Q_SIGNAL void otherToolBarStyleChanged();

    bool gtkConfigKdedModuleLoaded() const;
    Q_SIGNAL void gtkConfigKdedModuleLoadedChanged();

    Q_INVOKABLE void configure(const QString &title, const QString &styleName, QQuickItem *ctx = nullptr);

    void load() override;
    void save() override;
    void defaults() override;

Q_SIGNALS:
    void showErrorMessage(const QString &message);
    void styleReconfigured(const QString &styleName);

private:
    void loadSettingsToModel();
    void checkGtkConfigKdedModuleLoaded();

    StyleData *m_data;
    StylesModel *m_model;

    QString m_previousStyle;
    bool m_effectsDirty = false;

    ToolBarStyle m_mainToolBarStyle = NoText;
    ToolBarStyle m_otherToolBarStyle = NoText;

    QPointer<StyleConfigDialog> m_styleConfigDialog;

    bool m_gtkConfigKdedModuleLoaded = false;
    GtkPage *m_gtkPage = nullptr;

};

#endif // __KCMSTYLE_H
