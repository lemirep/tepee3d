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

#include "SerieSubListedItem.h"
#include <QDebug>

SerieSubListedItem::SerieSubListedItem(QObject *parent) : Models::SubListedListItem(parent)
{
}

SerieSubListedItem::SerieSubListedItem(int tvDbId, QString slug, QString serieName, QString imageUrl,
                                       QString overview, QString year, QString network,
                                       QDateTime lastUpdate, QString airDay, QString airTime,
                                       QObject *parent) : Models::SubListedListItem(parent)
{
    this->m_tvDbId = tvDbId;
    this->m_serieName = serieName;
    this->m_imageUrl = imageUrl;
    this->m_slug = slug;
    this->m_overview = overview;
    this->m_year = year;
    this->m_network = network;
    this->m_airDay = airDay;
    this->m_airTime = airTime;
    this->m_lastUpdate = lastUpdate;

    // INIT SEASON MODELS HERE
    this->seasonModel = new Models::SubListedListModel(new SeasonSubListedItem(-1, -1, ""));
}

SerieSubListedItem::~SerieSubListedItem()
{
    delete this->seasonModel;
}

int SerieSubListedItem::id() const
{
    return this->m_tvDbId;
}

QVariant SerieSubListedItem::data(int role) const
{
    switch (role)
    {
    case serieTvdbId:
        return this->id();
    case slug:
        return this->m_slug;
    case serieName:
        return this->m_serieName;
    case imageUrl:
        return this->m_imageUrl;
    case serieOverview:
        return this->m_overview;
    case serieYear:
        return this->m_year;
    case serieNetwork:
        return this->m_network;
    case serieLastUpdate:
        return this->m_lastUpdate;
    case serieAirDay:
        return this->m_airDay;
    case serieAirTime:
        return this->m_airTime;
    default :
        return QVariant();
    }
}

QHash<int, QByteArray> SerieSubListedItem::roleNames() const
{
    QHash<int, QByteArray> hashRoles;

    hashRoles[serieTvdbId] = "serieTvdbId";
    hashRoles[serieName] = "serieName";
    hashRoles[imageUrl] = "imageUrl";
    hashRoles[slug] = "slug";
    hashRoles[serieOverview] = "serieOverview";
    hashRoles[serieYear] = "serieYear";
    hashRoles[serieNetwork] = "serieNetwork";
    hashRoles[serieLastUpdate] = "serieLastUpdate";
    hashRoles[serieAirDay] = "serieAirDay";
    hashRoles[serieAirTime] = "serieAirTime";

    return hashRoles;
}

Models::ListModel *SerieSubListedItem::submodel() const
{
    // RETURN SEASONS MODEL FOR SHOW
    return (Models::ListModel*)this->seasonModel;
}



