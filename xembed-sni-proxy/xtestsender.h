/* Wrap XLIB code in a new file as it defines keywords that conflict with Qt
 *
 * Copyright (C) 2017 <davidedmundson@kde.org> David Edmundson
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 *
 */
#ifndef XTEST_SENDER_H
#define XTEST_SENDER_H

typedef struct _XDisplay Display;

void sendXTestPressed(Display *display, int button);
void sendXTestReleased(Display *display, int button);

#endif
