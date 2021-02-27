/*
 *   SPDX-FileCopyrightText: 2007 Glenn Ergeerts <glenn.ergeerts@telenet.be>
 *   SPDX-FileCopyrightText: 2012 Glenn Ergeerts <marco.gulino@gmail.com>
 *
 *   SPDX-License-Identifier: LGPL-2.0-or-later
 */

#ifndef FAVICON_H
#define FAVICON_H

#include <QIcon>
#include <QObject>

class Favicon : public QObject
{
    Q_OBJECT
public:
    explicit Favicon(QObject *parent = nullptr);
    virtual QIcon iconFor(const QString &url) = 0;

protected:
    inline QIcon defaultIcon() const
    {
        return m_default_icon;
    }

private:
    QIcon const m_default_icon;

public Q_SLOTS:
    virtual void prepare()
    {
    }
    virtual void teardown()
    {
    }
};

class FallbackFavicon : public Favicon
{
    Q_OBJECT
public:
    FallbackFavicon(QObject *parent = nullptr)
        : Favicon(parent)
    {
    }
    QIcon iconFor(const QString &) override
    {
        return defaultIcon();
    }
};

#endif // FAVICON_H
