/*
 *   SPDX-FileCopyrightText: 2007 Glenn Ergeerts <glenn.ergeerts@telenet.be>
 *   SPDX-FileCopyrightText: 2012 Glenn Ergeerts <marco.gulino@gmail.com>
 *
 *   SPDX-License-Identifier: LGPL-2.0-or-later
 */

#ifndef BOOKMARKMATCH_H
#define BOOKMARKMATCH_H

#include <KRunner/QueryMatch>
#include <QIcon>
#include <QList>
#include <QString>

class BookmarkMatch
{
public:
    BookmarkMatch(const QIcon &icon,
                  const QString &searchTerm,
                  const QString &bookmarkTitle,
                  const QString &bookmarkURL,
                  const QString &description = QString());
    void addTo(QList<BookmarkMatch> &listOfResults, bool addEvenOnNoMatch);
    Plasma::QueryMatch asQueryMatch(Plasma::AbstractRunner *runner);

private:
    bool matches(const QString &search, const QString &matchingField);

private:
    QIcon m_icon;
    QString m_searchTerm;
    QString m_bookmarkTitle;
    QString m_bookmarkURL;
    QString m_description;
};

#endif // BOOKMARKMATCH_H
