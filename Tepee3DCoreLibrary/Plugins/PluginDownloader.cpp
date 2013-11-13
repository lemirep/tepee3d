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

#include "PluginDownloader.h"

/*!
 * \class Plugins::PluginDownloader
 * \brief Utility class handling the download of plugin libraries from the Tepee3D remote server.
 */

Plugins::PluginDownloader* Plugins::PluginDownloader::instance = NULL;

/*!
 * Destroys a PluginDownloader instance.
 */
Plugins::PluginDownloader::~PluginDownloader()
{
    Plugins::PluginDownloader::instance = NULL;
}

/*!
 * Returns a singleton instance of PluginDownloader.
 */
Plugins::PluginDownloader *Plugins::PluginDownloader::getInstance(QObject *parent)
{
    if (Plugins::PluginDownloader::instance == NULL)
        Plugins::PluginDownloader::instance = new Plugins::PluginDownloader(parent);
    return Plugins::PluginDownloader::instance;
}

/*!
 * Constructs an instance of a PluginDownloader class.
 */
Plugins::PluginDownloader::PluginDownloader(QObject *parent) : QObject(parent),
    FileDownloaderServiceUserInterface()
{
    this->callBacks[DOWNLOAD_PLUGIN_INDEX] = &Plugins::PluginDownloader::downloadPluginIndexCallBack;
    this->callBacks[DOWNLOAD_PLUGIN_FILE] = &Plugins::PluginDownloader::downloadPluginFileCallBack;
}

/*!
 * CallBack called when the index file of a plugin was downloaded or encountered an error. The \a file where the download was saved as well as an optional \a data
 * pointer passed when issuing the request are passed. In addition, the \a error variable is true when the download encountered an error.
 */
void Plugins::PluginDownloader::downloadPluginIndexCallBack(QPointer<QFile> file, QPointer<QObject> data, bool error)
{
    if (!file.isNull() && !data.isNull())
    {
        Models::PluginOnlineModelItem *pluginOnlineItem = reinterpret_cast<Models::PluginOnlineModelItem *>(data.data());
        if (error)
        {
            pluginOnlineItem->setPluginDownloadError(error);
            return ;
        }
        if (pluginOnlineItem->getPluginDownloadError())
        {
            file->close();
            qWarning() << "Error while trying to dowload plugin File file";
            qWarning() << "Removing Plugin Directory";
            QDir pluginDir = QDir(PlatformFactory::getPlatformInitializer()->
                                  getWidgetsResourceDirectory().absoluteFilePath(
                                      pluginOnlineItem->getPluginRepoName()));
            pluginDir.removeRecursively();
            return ;
        }
        qDebug() << "File Index downloaded";
        file->reset();
        pluginOnlineItem->setPluginDownloading(true);
        while (!file->atEnd())
        {
            QString fileName = file->readLine();
            fileName.chop(1);
            QFile *itemFile;
            QDir pluginDir = QDir(PlatformFactory::getPlatformInitializer()->
                                  getWidgetsResourceDirectory().absoluteFilePath(
                                      pluginOnlineItem->getPluginRepoName()));
            qDebug() << pluginDir.absolutePath();
            if (fileName.compare(pluginOnlineItem->getPluginRepoName() + ".sql") == 0) // WE HAVE A DATABASE FILE
                itemFile = new QFile(PlatformFactory::getPlatformInitializer()->
                                     getDatabaseDirectory().absoluteFilePath(fileName));
            else if (fileName.endsWith(".so") || fileName.endsWith(".ddl")) // WE HAVE THE PLUGIN LIBRARY
                itemFile = new QFile(PlatformFactory::getPlatformInitializer()->
                                     getWidgetSharedLibrariesDirectory().absoluteFilePath(fileName));
            else
                itemFile = new QFile(pluginDir.absoluteFilePath(fileName));
            if (itemFile->open(QIODevice::WriteOnly))
            {
                qDebug() << itemFile->fileName();
                pluginOnlineItem->setPluginFileToDownloadCount(pluginOnlineItem->getPluginFileToDownload() + 1);
                emit executeFileDownloader(QNetworkRequest(QUrl(QString(TEPEE3D_WIDGETS_STORE)
                                                                + PlatformFactory::getPlatformInitializer()->getPlatformName()
                                                                + "/"
                                                                + pluginOnlineItem->getPluginRepoName()
                                                                + "/"
                                                                + fileName)),
                                           Services::FileDownloaderServiceUserInterface::Get,
                                           DOWNLOAD_PLUGIN_FILE,
                                           QPointer<QFile>(itemFile),
                                           QPointer<QObject>(this),
                                           NULL,
                                           QPointer<QObject>(pluginOnlineItem));
            }
        }
        qDebug() << "Reading done";
    }
}

/*!
 * CallBack called when a plugin file was downloaded or encountered an error. The \a file where the download was saved as well as an optional \a data
 * pointer passed when issuing the request are passed. In addition, the \a error variable is true when the download encountered an error.
 */
void Plugins::PluginDownloader::downloadPluginFileCallBack(QPointer<QFile> file, QPointer<QObject> data, bool error)
{
    if (!file.isNull() && !data.isNull())
    {
        Models::PluginOnlineModelItem* pluginOnlineItem = reinterpret_cast<Models::PluginOnlineModelItem *>(data.data());
        if (error)
        {
            pluginOnlineItem->setPluginDownloadError(error);
            return ;
        }
        pluginOnlineItem->setPluginFileToDownloadCount(pluginOnlineItem->getPluginFileToDownload() - 1);
        qDebug() << pluginOnlineItem->getPluginFileToDownload() << " Files Remaining";
        if (pluginOnlineItem->getPluginFileToDownload() == 0)
        {
            if (pluginOnlineItem->getPluginDownloadError())
            {
                file->close();
                qWarning() << "Error while trying to dowload plugin File file";
                qWarning() << "Removing Plugin Directory";
                QDir pluginDir = QDir(PlatformFactory::getPlatformInitializer()->
                                      getWidgetsResourceDirectory().absoluteFilePath(
                                          pluginOnlineItem->getPluginRepoName()));
                pluginDir.removeRecursively();
                pluginOnlineItem->setPluginDownloaded(false);
                pluginOnlineItem->setPluginDownloading(false);
                return ;
            }
            qDebug() << "Plugin Downloaded, reloading models";
            pluginOnlineItem->setPluginDownloading(false);
            pluginOnlineItem->setPluginDownloaded(true);
            emit newPluginDownloaded();
        }
    }
}

/*!
 * Callback triggered when a download has completed with the \a file where the download was saved, the \a requestId passed when
 * calling the download as well as an optional \a data pointer.
 */
void Plugins::PluginDownloader::onDownloadFinished(QPointer<QFile> file, int requestId, QPointer<QObject> data)
{
    (this->*this->callBacks[requestId])(file, data, false);
    if (!file.isNull())
        file->close();
}

/*!
 * Callback triggered when a download's \a progress has changed with the \a file where the download was saved, the \a requestId passed when
 * calling the download as well as an optional \a data pointer.
 */
void Plugins::PluginDownloader::onDownloadProgress(QPointer<QFile> , int , int , QPointer<QObject>)
{
}

/*!
 * Callback triggered when a download has started with the \a file where the download was saved, the \a requestId passed when
 * calling the download as well as an optional \a data pointer.
 */
void Plugins::PluginDownloader::onDownloadStarted(QPointer<QFile>, int , QPointer<QObject>)
{
}

/*!
 * Callback triggered when a download has encountered an error with the \a file where the download was saved, the \a requestId passed when
 * calling the download as well as an optional \a data pointer.
 */
void Plugins::PluginDownloader::onDownloadError(QPointer<QFile> file, int requestId, QPointer<QObject> data)
{
    (this->*this->callBacks[requestId])(file, data, true);
}

/*!
 * Performs a request to download a plugin, the \a plugin model is passed along in order to be updated during the process.
 */
void Plugins::PluginDownloader::downloadPluginFromServer(QPointer<QObject> plugin)
{
    if (plugin.isNull())
        return ;
    Models::PluginOnlineModelItem *pluginOnlineItem = reinterpret_cast<Models::PluginOnlineModelItem *>(plugin.data());
    pluginOnlineItem->setPluginDownloadError(false);
    QDir pluginDir = QDir(PlatformFactory::getPlatformInitializer()->getWidgetsResourceDirectory().absoluteFilePath(pluginOnlineItem->getPluginRepoName()));
    qDebug() << pluginDir.absolutePath();
    qDebug() << pluginDir.dirName();
    qDebug() << "Repo Name " << pluginOnlineItem->getPluginRepoName();
    if (pluginDir.exists() ||
            (!pluginDir.exists() && PlatformFactory::getPlatformInitializer()->getWidgetsResourceDirectory().mkdir(pluginDir.dirName())))
    {
        qDebug() << "Plugin Dir exists";
        QFile *indexFile = new QFile(pluginDir.absoluteFilePath("index"));
        if (indexFile->open(QIODevice::ReadWrite))
        {
            emit executeFileDownloader(QNetworkRequest(QUrl(QString(TEPEE3D_WIDGETS_STORE)
                                                            + PlatformFactory::getPlatformInitializer()->getPlatformName()
                                                            + "/"
                                                            + pluginOnlineItem->getPluginRepoName()
                                                            + "/index")),
                                       Services::FileDownloaderServiceUserInterface::Get,
                                       DOWNLOAD_PLUGIN_INDEX,
                                       QPointer<QFile>(indexFile),
                                       QPointer<QObject>(this),
                                       NULL,
                                       QPointer<QObject>(pluginOnlineItem));
        }
    }
}

