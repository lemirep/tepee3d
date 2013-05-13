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

#include "Utils.h"

Utils::Utils()
{
}

QJsonDocument Utils::QJsonDocumentFromReply(QNetworkReply *reply)
{
    if (reply != NULL)
        return QJsonDocument::fromJson(reply->readAll());
    return QJsonDocument::fromJson("{}");
}

QString & Utils::escapeSqlQuery(QString query)
{
    return query.replace("'", "''");
}

QString Utils::returnPlatformName()
{
#if defined Q_OS_LINUX
    return "linux";
#elif defined Q_OS_UNIX
    return "unix";
#elif defined Q_OS_WIN32
    return "windows32";
#elif defined Q_OS_WIN64
    return "windows64";
#elif defined Q_OS_QNX
    return "qnx";
#elif defined Q_OS_MACX
    return "mac";
#elif defined Q_OS_IOS
    return "ios";
#elif defined Q_OS_ANDROID
    return "android";
#endif
}

