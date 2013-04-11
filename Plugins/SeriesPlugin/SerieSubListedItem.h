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

#ifndef SERIESUBLISTEDITEM_H
#define SERIESUBLISTEDITEM_H

#include <SubListedListModel.h>
#include <SubListedListItem.h>
#include "SeasonSubListedItem.h"

class SerieSubListedItem : public Models::SubListedListItem
{
    Q_OBJECT
public:

    enum    SeriesModelItemRoles
    {
        serieTvdbId = Qt::UserRole + 1,
        slug,
        serieName,
        imageUrl,
        serieOverview,
        serieYear,
        serieNetwork,
        serieLastUpdate,
        serieAirDay,
        serieAirTime,
        serieOnSickbeard
    };

    explicit SerieSubListedItem(QObject *parent = 0);
    explicit SerieSubListedItem( int tvDbId,
                                 QString slug, QString serieName, QString imageUrl,
                                 QString overview, QString year, QString network,
                                 QDateTime lastUpdate, QString airDay, QString airTime,
                                 bool serieOnSickbeard = false, QObject *parent = 0);
    ~SerieSubListedItem();

    int             id() const;
    QVariant        data(int role) const;
    QHash<int, QByteArray>  roleNames() const;

    Models::ListModel*  submodel()   const;
    void                setSerieOnSickBeard(bool value);


private :
    QString m_serieName;
    QString m_imageUrl;
    QString m_slug;
    QString m_overview;
    QString m_year;
    QString m_network;
    QDateTime m_lastUpdate;
    QString m_airDay;
    QString m_airTime;
    int     m_tvDbId;
    bool    m_serieOnSickbeard;

    Models::SubListedListModel*  seasonModel;
};

#endif // SERIESUBLISTEDITEM_H
