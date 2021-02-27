/*
 *   SPDX-FileCopyrightText: 2011 Sebastian Kügler <sebas@kde.org>
 *
 *   SPDX-License-Identifier: LGPL-2.0-or-later
 */

#ifndef POWERMANAGEMENTSERVICE_H
#define POWERMANAGEMENTSERVICE_H

#include <Plasma/Service>
#include <Plasma/ServiceJob>

using namespace Plasma;

class PowerManagementService : public Plasma::Service
{
    Q_OBJECT

public:
    explicit PowerManagementService(QObject *parent = nullptr);
    ServiceJob *createJob(const QString &operation, QMap<QString, QVariant> &parameters) override;
};

#endif // POWERMANAGEMENTSERVICE_H
