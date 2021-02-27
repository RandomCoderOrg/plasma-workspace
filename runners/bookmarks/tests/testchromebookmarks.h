/*
 *   SPDX-FileCopyrightText: 2007 Glenn Ergeerts <glenn.ergeerts@telenet.be>
 *   SPDX-FileCopyrightText: 2012 Glenn Ergeerts <marco.gulino@gmail.com>
 *
 *   SPDX-License-Identifier: LGPL-2.0-or-later
 */

#ifndef TESTCHROMEBOOKMARKS_H
#define TESTCHROMEBOOKMARKS_H

#include "browsers/findprofile.h"
#include <QObject>

class FakeFindProfile : public FindProfile
{
public:
    FakeFindProfile(const QList<Profile> &profiles)
        : m_profiles(profiles)
    {
    }
    QList<Profile> find() override
    {
        return m_profiles;
    }

private:
    QList<Profile> m_profiles;
};

class TestChromeBookmarks : public QObject
{
    Q_OBJECT
public:
    explicit TestChromeBookmarks(QObject *parent = nullptr)
        : QObject(parent)
    {
    }
private Q_SLOTS:
    void initTestCase();
    void bookmarkFinderShouldFindEachProfileDirectory();
    void bookmarkFinderShouldReportNoProfilesOnErrors();
    void itShouldFindNothingWhenPrepareIsNotCalled();
    void itShouldGracefullyExitWhenFileIsNotFound();
    void itShouldFindAllBookmarks();
    void itShouldFindOnlyMatches();
    void itShouldClearResultAfterCallingTeardown();
    void itShouldFindBookmarksFromAllProfiles();

private:
    QScopedPointer<FakeFindProfile> m_findBookmarksInCurrentDirectory;
};

#endif // TESTCHROMEBOOKMARKS_H
