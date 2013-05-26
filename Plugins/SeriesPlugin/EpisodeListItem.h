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

#ifndef EPISODELISTITEM_H
#define EPISODELISTITEM_H

#include <ListItem.h>
#include <QDateTime>

class EpisodeListItem : public Models::ListItem
{
public:
    enum    EpisodeListItemRoles
    {
        episodeId = Qt::UserRole + 1,
        episodeNumber,
        episodeSeason,
        episodeTitle,
        episodeSummary,
        episodeAiring,
        imageUrl,
        episodeSeen,
        episodeSickbeardStatus
    };

    explicit EpisodeListItem(QObject *parent = 0);
    explicit EpisodeListItem(int episodeId, int episodeNumber, int episodeSeason,
                             const QString& episodeTitle, const QString& episodeSummary, const QString& imageUrl,
                             QDateTime episodeAiring, bool episodeSeen = false,
                             const QString& episodeSickbeardStatus = "", QObject *parent = 0);
    ~EpisodeListItem();
    int             id() const;
    QVariant        data(int role) const;
    QHash<int, QByteArray>  roleNames() const;

    void    setSickbeardStatus(const QString& status);
    void    setEpisodeSeen(bool value);

private :
    int m_episodeId;
    int m_episodeNumber;
    int m_episodeSeason;
    bool m_episodeSeen;

    QString m_episodeTitle;
    QString m_episodeSummary;
    QString m_imageUrl;
    QString m_episodeSickbeardStatus;

    QDateTime m_episodeAiring;
};

#endif // EPISODELISTITEM_H
