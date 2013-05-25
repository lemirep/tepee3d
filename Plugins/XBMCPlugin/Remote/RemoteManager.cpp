#include "RemoteManager.h"

RemoteManager::RemoteManager(QObject *parent) : QObject(parent)
{
    this->webServiceMethods[Up] = "Input.Up";
    this->webServiceMethods[Left] = "Input.Left";
    this->webServiceMethods[Right] = "Input.Right";
    this->webServiceMethods[Down] = "Input.Down";
    this->webServiceMethods[Back] = "Input.Back";
    this->webServiceMethods[Select] = "Input.Select";
    this->webServiceMethods[Home] = "Input.Home";
}

RemoteManager::~RemoteManager()
{
}

void RemoteManager::receiveResultFromHttpRequest(QNetworkReply *reply, int id, void *data)
{
    Q_UNUSED(id);
    Q_UNUSED(data);
    this->moveKeyCallBack(reply);
}

int RemoteManager::getMajorIDRequestHandled() const
{
    return MAJOR_ID_REQUEST_REMOTE;
}

void RemoteManager::moveKey(int key)
{
     QJsonObject requestJson;
     requestJson.insert("jsonrpc", QJsonValue(QString("2.0")));
     requestJson.insert("method", QJsonValue(this->webServiceMethods[(NavigationKeys)key]));
     emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(MAJOR_ID_REQUEST_REMOTE, KEY_PRESSED));
}

void RemoteManager::moveKeyCallBack(QNetworkReply *reply)
{
    qDebug() << "Move Key CallBack";
    QJsonDocument replyJs = Utils::QJsonDocumentFromReply(reply);
    qDebug() << replyJs.toJson();
}
