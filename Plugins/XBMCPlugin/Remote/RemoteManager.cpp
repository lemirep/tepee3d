#include "RemoteManager.h"

RemoteManager::RemoteManager(QObject *parent) : QObject(parent)
{
}

RemoteManager::~RemoteManager()
{
}

void RemoteManager::receiveResultFromHttpRequest(QNetworkReply *reply, int id, void *data)
{
}

int RemoteManager::getMajorIDRequestHandled() const
{
    return MAJOR_ID_REQUEST;
}
