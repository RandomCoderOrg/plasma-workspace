/*  This file is part of the KDE project
    SPDX-FileCopyrightText: 2006 Matthias Kretz <kretz@kde.org>
    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef KFONTINST_EXPORT_H
#define KFONTINST_EXPORT_H

#include <QtGlobal>

#if defined _WIN32 || defined _WIN64

#ifndef KFONTINST_EXPORT
#if defined(MAKE_KFONTINST_LIB)
#define KFONTINST_EXPORT Q_DECL_EXPORT
#else
#define KFONTINST_EXPORT Q_DECL_IMPORT
#endif
#endif

#else /* UNIX */

#define KFONTINST_EXPORT Q_DECL_EXPORT

#endif

#endif // KFONTINST_EXPORT_H
