#ifndef STREAMSERVICEUSERINTERFACE_H
#define STREAMSERVICEUSERINTERFACE_H

#include <QDataStream>

namespace Services
{
class   StreamServiceUserInterface
{
public :
    virtual void receiveStreamFromRequest(QDataStream *stream, int requestId, void *data) = 0;
    // SIGNAL
    //void executeStreamRequest(const QNetworkRequest&, int, QDataStream*, QObject* sender, int, void *);
};
}
Q_DECLARE_INTERFACE(Services::StreamServiceUserInterface, "com.tepee3d.Services.WebServiceUserInterface/1.0")



#endif // STREAMSERVICEUSERINTERFACE_H
