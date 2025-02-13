/*
    Copyright (C) 2021 Kai Uwe Broulik <kde@broulik.de>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#pragma once

#include <QObject>
#include <QString>
#include <QUrl>

#include <KService>

class QAction;

namespace KIO
{
class MimeTypeFinderJob;
}

class FileInfo : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)

    Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)
    Q_PROPERTY(int error READ error NOTIFY errorChanged)

    Q_PROPERTY(QString mimeType READ mimeType NOTIFY mimeTypeChanged)
    Q_PROPERTY(QString iconName READ iconName NOTIFY mimeTypeChanged)

    Q_PROPERTY(QAction *openAction READ openAction NOTIFY openActionChanged)
    // QML can't deal with QIcon...
    Q_PROPERTY(QString openActionIconName READ openActionIconName NOTIFY openActionIconNameChanged)

public:
    explicit FileInfo(QObject *parent = nullptr);
    ~FileInfo() override;

    QUrl url() const;
    void setUrl(const QUrl &url);
    Q_SIGNAL void urlChanged(const QUrl &url);

    bool busy() const;
    Q_SIGNAL void busyChanged(bool busy);

    int error() const;
    Q_SIGNAL void errorChanged(bool error);

    QString mimeType() const;
    Q_SIGNAL void mimeTypeChanged();

    QString iconName() const;
    Q_SIGNAL void iconNameChanged(const QString &iconName);

    QAction *openAction() const;
    Q_SIGNAL void openActionChanged();

    QString openActionIconName() const;
    Q_SIGNAL void openActionIconNameChanged();

private:
    void reload();
    void mimeTypeFound(const QString &mimeType);

    void setBusy(bool busy);
    void setError(int error);

    QUrl m_url;

    QPointer<KIO::MimeTypeFinderJob> m_job;
    bool m_busy = false;
    int m_error = 0;

    QString m_mimeType;
    QString m_iconName;

    KService::Ptr m_preferredApplication;
    QAction *m_openAction = nullptr;
};
