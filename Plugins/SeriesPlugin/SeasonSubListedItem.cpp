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

#include "SeasonSubListedItem.h"

SeasonSubListedItem::SeasonSubListedItem(int seasonId, int episodeCount, QString imageUrl, QObject *parent) : Models::SubListedListItem(parent)
{
    this->m_seasonId = seasonId;
    this->m_episodeCount = episodeCount;
    this->m_imageUrl = imageUrl;
    this->episodesModel = new Models::ListModel(new EpisodeListItem());
}

SeasonSubListedItem::~SeasonSubListedItem()
{
    delete this->episodesModel;
}

int SeasonSubListedItem::id() const
{
    return this->m_seasonId;
}

QVariant SeasonSubListedItem::data(int role) const
{
    switch (role)
    {
    case seasonId:
        return this->m_seasonId;
    case episodeCount:
        return this->m_episodeCount;
    case imageUrl:
        return this->m_imageUrl;
    default :
        return QVariant();
    }
}

QHash<int, QByteArray> SeasonSubListedItem::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[seasonId] = "seasonId";
    roles[episodeCount] = "episodeCount";
    roles[imageUrl] = "imageUrl";

    return roles;
}

Models::ListModel *SeasonSubListedItem::submodel() const
{
    return (Models::ListModel*)this->episodesModel;
}

