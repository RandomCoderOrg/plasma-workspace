/*
 *   SPDX-FileCopyrightText: 2007 Aaron Seigo <aseigo@kde.org>
 *
 *   SPDX-License-Identifier: LGPL-2.0-only
 */

#ifndef LOCATIONRUNNER_H
#define LOCATIONRUNNER_H

#include <krunner/abstractrunner.h>

class LocationsRunner : public Plasma::AbstractRunner
{
    Q_OBJECT

public:
    LocationsRunner(QObject *parent, const KPluginMetaData &metaData, const QVariantList &args);
    ~LocationsRunner() override;

    void match(Plasma::RunnerContext &context) override;
    void run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &action) override;

protected Q_SLOTS:
    QMimeData *mimeDataForMatch(const Plasma::QueryMatch &match) override;
};

#endif
