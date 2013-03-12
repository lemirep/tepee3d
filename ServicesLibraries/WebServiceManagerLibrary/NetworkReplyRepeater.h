#ifndef NETWORKREPLYREPEATER_H
#define NETWORKREPLYREPEATER_H

#include <QNetworkReply>
#include <QObject>

class NetworkReplyRepeater : public QObject
{
    Q_OBJECT
public:
    NetworkReplyRepeater(QObject *receiver, int requestId);

private:
    QObject *receiver;
    int     requestId;

public slots:
    void    receiveNetworkReply();

};

#endif // NETWORKREPLYREPEATER_H
