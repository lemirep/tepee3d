#ifndef IWEBREQUESTDISPATCHER_H
#define IWEBREQUESTDISPATCHER_H

#include <Utils.h>
#include <QNetworkReply>

#define REQUEST_ID_BUILDER(major, minor) ((major * 10) + minor)

class IWebRequestDispatcher
{
public :
    virtual int     getMajorIDRequestHandled()  const = 0;
    virtual void    receiveResultFromHttpRequest(QNetworkReply * reply,int id, void *data) = 0;

};

#endif // IWEBREQUESTDISPATCHER_H
