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


#ifndef PLAYABLEITEMMODEL_H
#define PLAYABLEITEMMODEL_H

#include <ListItem.h>
#include <QUrl>

class PlayableItemModel : public Models::ListItem
{
    // Q_OBJECT NEEDS TO BE OMITTED HERE
public:
    enum PlayableItemModelRoles
    {
        title = Qt::UserRole + 1,
        rating,
        file,
        thumbnail
    };

    PlayableItemModel(QObject *parent = 0);
    virtual ~PlayableItemModel();
    virtual int id() const = 0;

    virtual QVariant data(int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

    virtual QString getFile() const;
    virtual QString getTitle() const;
    virtual QString getThumbnail() const;
    virtual int getRating() const;

    virtual void setTitle(const QString &title);
    virtual void setFile(const QString &file);
    virtual void setThumbnail(const QString &thumbnail);
    virtual void setRating(int rating);

protected :
    int m_rating;
    QString m_title;
    QString m_file;
    QString m_thumbnail;
};

#endif // PLAYABLEITEMMODEL_H
