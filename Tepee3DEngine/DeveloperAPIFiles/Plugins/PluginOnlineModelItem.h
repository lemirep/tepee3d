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

#ifndef PLUGINONLINEMODELITEM_H
#define PLUGINONLINEMODELITEM_H

#include <ListItem.h>

namespace Models
{
class PluginOnlineModelItem : public Models::ListItem
{
    Q_OBJECT
public:

    enum PluginOnlineModelItemRoles
    {
        pluginId = Qt::UserRole + 1,
        pluginName,
        pluginDescription,
        pluginDownloaded,
        pluginDownloading,
        pluginRepoName
    };

    explicit PluginOnlineModelItem(int pluginId, QObject *parent = 0);
    ~PluginOnlineModelItem();

    int                     id() const;
    QVariant                data(int role) const;
    QHash<int, QByteArray>  roleNames() const;

    QString getPluginName() const;
    QString getPluginRepoName() const;
    QString getPluginDescription() const;
    int     getPluginFileToDownload() const;

    void setPluginName(const QString &pluginName);
    void setPluginDescription(const QString &pluginDescription);
    void setPluginDownloaded(bool downloaded);
    void setPluginDownloading(bool downloading);
    void setPluginRepoName(const QString& pluginRepoName);
    void setPluginFileToDownloadCount(int fileToDownloadCount);

private:
    int     m_pluginId;
    QString m_pluginName;
    QString m_pluginDescription;
    QString m_pluginRepoName;
    bool    m_pluginDownloaded;
    bool    m_pluginDownloading;
    int     m_filetoDownloadCount;
};
}

#endif // PLUGINONLINEMODELITEM_H
