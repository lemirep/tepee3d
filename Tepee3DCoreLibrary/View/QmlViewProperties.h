/****************************************************************************
**
** Copyright (C) Paul Lemire, Tepee3DTeam and/or its subsidiary(-ies).
** Contact: paul.lemire@epitech.eu
** Contact: tepee3d_2014@labeip.epitech.eu
**
** This file is part of the Tepee3D project
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
****************************************************************************/

#ifndef QMLVIEWPROPERTIES_H
#define QMLVIEWPROPERTIES_H

#include <QObject>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QQmlContext>
#include <QQmlEngine>
#include "QmlContentExposerInterface.h"

namespace View
{
class QmlViewProperties : public QObject
{
    Q_OBJECT

private:
    QQuickView                  *viewer;
    QQmlEngine                  *qmlEngine;
    QQmlContext                 *qmlContext;

    explicit QmlViewProperties(QObject *parent = 0);

    static QmlViewProperties    *instance;

public:
    ~QmlViewProperties();
    static QmlViewProperties*   getInstance(QObject *parent);
    static void                 exposeContentToQml(QObject* exposer);

    void                        setViewerSource(const QUrl& sourceFile);
    void                        showView();

signals:
    void                        quit();
public slots:
    
};
}
#endif // QMLVIEWPROPERTIES_H
