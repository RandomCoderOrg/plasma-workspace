/*
 *   SPDX-FileCopyrightText: 2008 Sebastian Kügler <sebas@kde.org>
 *
 *   SPDX-License-Identifier: LGPL-2.0-or-later
 */

#ifndef RECENTDOCUMENTS_H
#define RECENTDOCUMENTS_H

#include <krunner/abstractrunner.h>

#include <QIcon>

class RecentDocuments : public Plasma::AbstractRunner
{
    Q_OBJECT

public:
    RecentDocuments(QObject *parent, const KPluginMetaData &metaData, const QVariantList &args);
    ~RecentDocuments() override;

    void match(Plasma::RunnerContext &context) override;
    void run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match) override;

private Q_SLOTS:
    QMimeData *mimeDataForMatch(const Plasma::QueryMatch &match) override;
};

#endif
