/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QATOMIC_ARMV7_H
#define QATOMIC_ARMV7_H

QT_BEGIN_HEADER

// use the DMB instruction when compiling for ARMv7, ...
#ifndef Q_CC_RCVT
# define Q_DATA_MEMORY_BARRIER asm volatile("dmb\n":::"memory")
#else
# define Q_DATA_MEMORY_BARRIER do{__asm { dmb } __schedule_barrier();}while(0)
#endif

// ... but the implementation is otherwise identical to that for ARMv6
QT_BEGIN_INCLUDE_HEADER
#include "QtCore/qatomic_armv6.h"
QT_END_INCLUDE_HEADER

QT_END_HEADER

#endif // QATOMIC_ARMV7_H
