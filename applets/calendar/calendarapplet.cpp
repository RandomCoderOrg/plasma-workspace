/*
 * Copyright 2016 Kai Uwe Broulik <kde@privat.broulik.de>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License or (at your option) version 3 or any later version
 * accepted by the membership of KDE e.V. (or its successor approved
 * by the membership of KDE e.V.), which shall act as a proxy
 * defined in Section 14 of version 3 of the license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "calendarapplet.h"

#include <QDateTime>

CalendarApplet::CalendarApplet(QObject *parent, const QVariantList &data)
    : Plasma::Applet(parent, data)
{
}

CalendarApplet::~CalendarApplet()
{
}

int CalendarApplet::weekNumber(const QDateTime &dateTime) const
{
    return dateTime.date().weekNumber();
}

K_PLUGIN_CLASS_WITH_JSON(CalendarApplet, "metadata.json")

#include "calendarapplet.moc"
