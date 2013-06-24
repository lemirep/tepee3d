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

#ifndef ROOMPROPERTIES_H
#define ROOMPROPERTIES_H

#include <QDebug>
#include <QVector3D>
#include <QObject>
#include "ListModel.h"
#include "PluginBase.h"
#include "PluginModelItem.h"

namespace Room
{

class RoomProperties : public QObject
{
    Q_OBJECT

private :

    QString                         roomName;
    QVector3D                       position;
    QVector3D                       scale;

    Models::ListModel*              pluginsModel;

public:
    explicit RoomProperties(QObject *parent = 0);
    ~RoomProperties();

    void                            setScale(const QVector3D& scale);
    void                            setRoomName(const QString& name);
    void                            setPosition(const QVector3D& position);

    QString                         getRoomName()      const;

    QVector3D                       getPosition()      const;
    QVector3D                       getScale()         const;

    Models::ListModel*              getRoomPluginsModel() const;

signals:
    
public slots:
    
};

}

#endif // ROOMPROPERTIES_H
