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

#include <QObject>
#include <QPointer>
#include <QHash>
#include <FileDownloaderServiceUserInterface.h>
#include <PluginOnlineModelItem.h>
#include <PlatformFactory.h>
#include <QDebug>

#ifndef PLUGINDOWNLOADER_H
#define PLUGINDOWNLOADER_H

#define TEPEE3D_WIDGETS_STORE "http://tepee3d.dyndns.org/builds/"
#define DOWNLOAD_PLUGIN_INDEX 1
#define DOWNLOAD_PLUGIN_FILE 2

namespace Plugins
{
class PluginDownloader : public QObject,
                         public Services::FileDownloaderServiceUserInterface
{
    Q_OBJECT
    Q_INTERFACES(Services::FileDownloaderServiceUserInterface)
public:
    ~PluginDownloader();
    static PluginDownloader *getInstance(QObject *parent = 0);

private:
    explicit PluginDownloader(QObject *parent = 0);

    static PluginDownloader* instance;
    QHash<int, void (PluginDownloader::*)(QPointer<QFile>, QPointer<QObject>, bool)> callBacks;

    void downloadPluginIndexCallBack(QPointer<QFile> file, QPointer<QObject> data, bool error = false);
    void downloadPluginFileCallBack(QPointer<QFile> file, QPointer<QObject> data, bool error = false);

    // FileDownloaderServiceUserInterface interface
public:
    void onDownloadFinished(QPointer<QFile> file, int requestId, QPointer<QObject> data);
    void onDownloadProgress(QPointer<QFile> file, int progress, int requestId, QPointer<QObject> data);
    void onDownloadStarted(QPointer<QFile> file, int requestId, QPointer<QObject> data);
    void onDownloadError(QPointer<QFile> file, int requestId, QPointer<QObject> data);

    void downloadPluginFromServer(QPointer<QObject> plugin);

signals:
    void executeFileDownloader(const QNetworkRequest&,
                               Services::FileDownloaderServiceUserInterface::FileDownloadRequestType,
                               QHttpMultiPart *,
                               QPointer<QFile>,
                               QPointer<QObject>,
                               int,
                               QPointer<QObject> = QPointer<QObject>());
    void newPluginDownloaded();
};
}
#endif // PLUGINDOWNLOADER_H
