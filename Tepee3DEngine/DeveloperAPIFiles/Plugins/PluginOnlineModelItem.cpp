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

#include "PluginOnlineModelItem.h"

Models::PluginOnlineModelItem::PluginOnlineModelItem(int pluginId, QObject *parent) :
    Models::ListItem(parent),
    m_pluginId(pluginId)
{
    this->m_pluginName = "";
    this->m_pluginDescription = "";
    this->m_pluginRepoName = "";
    this->m_pluginDownloaded = false;
    this->m_pluginDownloading = false;
}

Models::PluginOnlineModelItem::~PluginOnlineModelItem()
{
}

int Models::PluginOnlineModelItem::id() const
{
    return this->m_pluginId;
}

QVariant Models::PluginOnlineModelItem::data(int role) const
{
    switch (role)
    {
    case pluginId:
        return this->id();
    case pluginName:
        return this->getPluginName();
    case pluginDescription:
        return this->getPluginDescription();
    case pluginDownloaded:
        return this->m_pluginDownloaded;
    case pluginDownloading:
        return this->m_pluginDownloading;
    case pluginRepoName:
        return this->getPluginRepoName();
    default :
        return QVariant();
    }
}

QHash<int, QByteArray> Models::PluginOnlineModelItem::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[pluginId] = "pluginId";
    roles[pluginName] = "pluginName";
    roles[pluginDescription] = "pluginDescription";
    roles[pluginRepoName] = "pluginRepoName";

    return roles;
}

QString Models::PluginOnlineModelItem::getPluginName() const
{
    return this->m_pluginName;
}

QString Models::PluginOnlineModelItem::getPluginRepoName() const
{
    return this->m_pluginRepoName;
}

QString Models::PluginOnlineModelItem::getPluginDescription() const
{
    return this->m_pluginDescription;
}

int Models::PluginOnlineModelItem::getPluginFileToDownload() const
{
    return this->m_filetoDownloadCount;
}

void Models::PluginOnlineModelItem::setPluginName(const QString &pluginName)
{
    this->m_pluginName = pluginName;
}

void Models::PluginOnlineModelItem::setPluginDescription(const QString &pluginDescription)
{
    this->m_pluginDescription = pluginDescription;
}

void Models::PluginOnlineModelItem::setPluginDownloaded(bool downloaded)
{
    this->m_pluginDownloaded = downloaded;
}

void Models::PluginOnlineModelItem::setPluginDownloading(bool downloading)
{
    this->m_pluginDownloading = downloading;
}

void Models::PluginOnlineModelItem::setPluginRepoName(const QString &pluginRepoName)
{
    this->m_pluginRepoName = pluginRepoName;
}

void Models::PluginOnlineModelItem::setPluginFileToDownloadCount(int fileToDownloadCount)
{
    this->m_filetoDownloadCount = fileToDownloadCount;
}
