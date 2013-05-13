#ifndef NETWORKREPLYREPEATER_H
#define NETWORKREPLYREPEATER_H

#include <QNetworkReply>
#include <QObject>

class NetworkReplyRepeater : public QObject
{
    Q_OBJECT
public:
    NetworkReplyRepeater(QObject *receiver, int requestId, void *data, QHttpMultiPart *multiPart = NULL);
    ~NetworkReplyRepeater();

private:
    QObject *receiver;
    void    *data;
    int     requestId;
    QHttpMultiPart *multiPart;

public slots:
    void    receiveNetworkReply();

};

#endif // NETWORKREPLYREPEATER_H
