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

#include "EpisodeListItem.h"

EpisodeListItem::EpisodeListItem(QObject *parent) : Models::ListItem(parent)
{
}

EpisodeListItem::EpisodeListItem(int episodeId, int episodeNumber, int episodeSeason,
                                 const QString &episodeTitle, const QString &episodeSummary, const QString &imageUrl,
                                 QDateTime episodeAiring, bool episodeSeen,
                                 const QString &episodeSickbeardStatus, QObject *parent) : Models::ListItem(parent)
{
    this->m_episodeId = episodeId;
    this->m_episodeNumber = episodeNumber;
    this->m_episodeSeason = episodeSeason;
    this->m_episodeTitle = episodeTitle;
    this->m_episodeSummary = episodeSummary;
    this->m_imageUrl = imageUrl;
    this->m_episodeAiring = episodeAiring;
    this->m_episodeSeen = episodeSeen;
    this->m_episodeSickbeardStatus = episodeSickbeardStatus;
}

EpisodeListItem::~EpisodeListItem()
{
}

int EpisodeListItem::id() const
{
    return this->m_episodeId;
}

QVariant EpisodeListItem::data(int role) const
{
    switch (role)
    {
    case episodeId:
        return this->m_episodeId;
    case episodeNumber:
        return this->m_episodeNumber;
    case episodeSeason:
        return this->m_episodeSeason;
    case episodeTitle:
        return this->m_episodeTitle;
    case episodeSummary:
        return this->m_episodeSummary;
    case episodeAiring:
        return this->m_episodeAiring;
    case imageUrl:
        return this->m_imageUrl;
    case episodeSeen:
        return this->m_episodeSeen;
    case episodeSickbeardStatus:
        return this->m_episodeSickbeardStatus;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> EpisodeListItem::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[episodeId] = "episodeId";
    roles[episodeNumber] = "episodeNumber";
    roles[episodeSeason] = "episodeSeason";
    roles[episodeTitle] = "episodeTitle";
    roles[episodeSummary] = "episodeSummary";
    roles[episodeAiring] = "episodeAiring";
    roles[imageUrl] = "imageUrl";
    roles[episodeSeen] = "episodeSeen";
    roles[episodeSickbeardStatus] = "episodeSickbeardStatus";

    return roles;
}

void EpisodeListItem::setSickbeardStatus(const QString &status)
{
    this->m_episodeSickbeardStatus = status;
    this->triggerItemUpdate();
}

void EpisodeListItem::setEpisodeSeen(bool value)
{
    this->m_episodeSeen = value;
    this->triggerItemUpdate();
}
