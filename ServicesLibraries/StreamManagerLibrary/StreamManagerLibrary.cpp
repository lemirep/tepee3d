#include "StreamManagerLibrary.h"

StreamManagerLibrary::StreamManagerLibrary() : QObject()
{
}

QNetworkAccessManager*  StreamManagerLibrary::getInstance()
{
    if (instance == NULL)
        instance = new QNetworkAccessManager();
    return instance;
}

bool  StreamManagerLibrary::connectServiceToUser(QObject *user)
{
    qDebug() << "Connecting user to StreamServices";
    if (qobject_cast<Services::StreamServiceUserInterface*>(user) != NULL)
        return QObject::connect(user, SIGNAL(executeStreamRequest(const QNetworkRequest&, int, QDataStream*, QObject*, int, void*)),
                         this, SLOT(executeStreamRequest(QNetworkRequest, int, QDataStream*, QObject*, int, void*)));
    qWarning() << "Object does not implement StreamServiceUserInterface";
    return false;
}

/*!
 * Unsubscribes a \a user from the service.
 */
bool  StreamManagerLibrary::disconnectServiceFromUser(QObject *user)
{
    if (qobject_cast<Services::StreamServiceUserInterface*>(user) != NULL)
        return QObject::disconnect(user, SIGNAL(executeStreamRequest(const QNetworkRequest&, int, QDataStream*, QObject*, int, void*)),
                         this, SLOT(executeStreamRequest(QNetworkRequest, int, QDataStream*, QObject*, int, void*)));
    qWarning() << "Object does not implement StreamServiceUserInterface";
    return false;
}


int StreamManagerLibrary::getServiceId() const
{
    return SERVICE_ID;
}

/*!
 * Initializes library signal connection with \a parent.
 */
void            StreamManagerLibrary::initLibraryConnection(QObject *parent)
{
    QObject::connect(this, SIGNAL(initialized()), parent, SLOT(libraryInitialized()));
    emit (initialized());
}

void            StreamManagerLibrary::executeStreamRequest(QNetworkRequest request, int requestType, QDataStream *stream, QObject *sender, int requestId, void *data)
{
    qDebug() << "Executing StreamRequest";

}

/*!
 * Return the QObject instance of the library so that it can easily be connected to signals
 * and slots.
 */
QObject*        StreamManagerLibrary::getLibraryQObject()
{
    return this;
}

QString StreamManagerLibrary::getServiceVersion() const
{
    return SERVICE_VERSION;
}


QNetworkAccessManager* StreamManagerLibrary::instance = NULL;
