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

#include "PlayableItemModel.h"

PlayableItemModel::PlayableItemModel(QObject *parent) : Models::ListItem(parent)
{
}

PlayableItemModel::~PlayableItemModel()
{
}

QVariant PlayableItemModel::data(int role) const
{
    switch (role)
    {
    case title:
        return this->getTitle();
    case rating:
        return this->getRating();
    case file:
        return this->getFile();
    case thumbnail:
        return this->getThumbnail();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> PlayableItemModel::roleNames() const
{
    QHash<int, QByteArray> roleNames;

    roleNames[title] = "title";
    roleNames[file] = "file";
    roleNames[thumbnail] = "thumbnail";
    roleNames[rating] = "rating";

    return roleNames;
}

QString PlayableItemModel::getFile() const
{
    return this->m_file;
}

QString PlayableItemModel::getTitle() const
{
    return this->m_title;
}

QString PlayableItemModel::getThumbnail() const
{
    return this->m_thumbnail;
}

int PlayableItemModel::getRating() const
{
    return this->m_rating;
}

void PlayableItemModel::setTitle(const QString &title)
{
    this->m_title = title;
}

void PlayableItemModel::setFile(const QString &file)
{
    this->m_file = file;
}

void PlayableItemModel::setThumbnail(const QString &thumbnail)
{
    this->m_thumbnail =  QUrl::toPercentEncoding(thumbnail);
}

void PlayableItemModel::setRating(int rating)
{
    this->m_rating = rating;
}


