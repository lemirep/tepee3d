#ifndef NETWORKREPLYREPEATER_H
#define NETWORKREPLYREPEATER_H

#include <QNetworkReply>
#include <QObject>

class NetworkReplyRepeater : public QObject
{
    Q_OBJECT
public:
    NetworkReplyRepeater(QObject *receiver);

private:
    QObject *receiver;

public slots:
    void    receiveNetworkReply();

};

#endif // NETWORKREPLYREPEATER_H
