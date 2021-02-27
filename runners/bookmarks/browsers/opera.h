/*
 *   SPDX-FileCopyrightText: 2007 Glenn Ergeerts <glenn.ergeerts@telenet.be>
 *   SPDX-FileCopyrightText: 2012 Glenn Ergeerts <marco.gulino@gmail.com>
 *
 *   SPDX-License-Identifier: LGPL-2.0-or-later
 */

#ifndef OPERA_H
#define OPERA_H

#include "browser.h"
#include <QStringList>

class Favicon;

class Opera : public QObject, public Browser
{
    Q_OBJECT
public:
    explicit Opera(QObject *parent = nullptr);
    QList<BookmarkMatch> match(const QString &term, bool addEverything) override;
public Q_SLOTS:
    void prepare() override;
    void teardown() override;

private:
    QStringList m_operaBookmarkEntries;
    Favicon *const m_favicon;
};

#endif // OPERA_H
