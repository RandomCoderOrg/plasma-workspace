/* This file is part of the KDE Project
   SPDX-FileCopyrightText: 2009 Kevin Ottens <ervin@kde.org>

   SPDX-License-Identifier: LGPL-2.0-only
*/

#ifndef SOLIDAUTOEJECT_H
#define SOLIDAUTOEJECT_H

#include <kdedmodule.h>

namespace Solid
{
class Device;
}

class SolidAutoEject : public KDEDModule
{
    Q_OBJECT

public:
    SolidAutoEject(QObject *parent, const QList<QVariant> &);
    ~SolidAutoEject() override;

private slots:
    void onDeviceAdded(const QString &udi);
    void onEjectPressed(const QString &udi);

private:
    void connectDevice(const Solid::Device &device);
};

#endif
