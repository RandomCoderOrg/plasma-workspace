/*
 *   SPDX-FileCopyrightText: 2010 Ivan Cukic <ivan.cukic(at)kde.org>
 *   SPDX-FileCopyrightText: 2013 Martin Klapetek <mklapetek(at)kde.org>
 *
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef SPLASH_APP_H_
#define SPLASH_APP_H_

#include <QBasicTimer>
#include <QGuiApplication>
#include <QObject>

class SplashWindow;

namespace KWayland
{
namespace Client
{
class PlasmaShell;
}
}

class SplashApp : public QGuiApplication
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.kde.KSplash")

public:
    explicit SplashApp(int &argc, char **argv);
    ~SplashApp() override;

    KWayland::Client::PlasmaShell *waylandPlasmaShellInterface() const
    {
        return m_waylandPlasmaShell;
    }

public Q_SLOTS:
    Q_SCRIPTABLE void setStage(const QString &messgae);

protected:
    void timerEvent(QTimerEvent *event) override;
    void setStage(int stage);

private:
    void setupWaylandIntegration();
    int m_stage;
    QList<SplashWindow *> m_windows;
    bool m_testing;
    bool m_window;
    QStringList m_stages;
    QBasicTimer m_timer;
    QString m_theme;

    KWayland::Client::PlasmaShell *m_waylandPlasmaShell = nullptr;

private Q_SLOTS:
    void adoptScreen(QScreen *);
};

#endif // SPLASH_APP_H_
