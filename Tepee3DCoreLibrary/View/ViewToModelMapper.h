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

#ifndef VIEWTOMODELMAPPER_H
#define VIEWTOMODELMAPPER_H

#include <QObject>
#include "RoomManager.h"

namespace View
{
// ACT AS AN INTERMEDIARY BETWEEN VIEW OBJECT/QML AND MODELS
// ALL INTERACTIONS BETWEEN THE VIEW AND THE MODEL SHOULD GO HERE

class ViewToModelMapper : public QObject
{
    Q_OBJECT
public:
    explicit ViewToModelMapper(QObject *parent = 0);
    
    static Plugins::PluginBase* getPluginFromRoom(int roomId, int pluginId);


signals:
    
public slots:
    
};
}

#endif // VIEWTOMODELMAPPER_H
