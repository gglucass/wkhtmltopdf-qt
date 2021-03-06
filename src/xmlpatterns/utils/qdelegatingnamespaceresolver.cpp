/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtXmlPatterns module of the Qt Toolkit.
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

#include "qnamepool_p.h"

#include "qdelegatingnamespaceresolver_p.h"

QT_BEGIN_NAMESPACE

using namespace QPatternist;

DelegatingNamespaceResolver::DelegatingNamespaceResolver(const NamespaceResolver::Ptr &resolver) : m_nsResolver(resolver)
{
    Q_ASSERT(m_nsResolver);
}

DelegatingNamespaceResolver::DelegatingNamespaceResolver(const NamespaceResolver::Ptr &ns,
                                                         const Bindings &overrides) : m_nsResolver(ns)
                                                                                    , m_bindings(overrides)
{
    Q_ASSERT(m_nsResolver);
}

QXmlName::NamespaceCode DelegatingNamespaceResolver::lookupNamespaceURI(const QXmlName::PrefixCode prefix) const
{
    const QXmlName::NamespaceCode val(m_bindings.value(prefix, NoBinding));

    if(val == NoBinding)
        return m_nsResolver->lookupNamespaceURI(prefix);
    else
        return val;
}

NamespaceResolver::Bindings DelegatingNamespaceResolver::bindings() const
{
    Bindings bs(m_nsResolver->bindings());
    const Bindings::const_iterator end(m_bindings.constEnd());
    Bindings::const_iterator it(m_bindings.constBegin());

    for(; it != end; ++it)
        bs.insert(it.key(), it.value());

    return bs;
}

void DelegatingNamespaceResolver::addBinding(const QXmlName nb)
{
    if(nb.namespaceURI() == StandardNamespaces::UndeclarePrefix)
        m_bindings.remove(nb.prefix());
    else
        m_bindings.insert(nb.prefix(), nb.namespaceURI());
}

QT_END_NAMESPACE
