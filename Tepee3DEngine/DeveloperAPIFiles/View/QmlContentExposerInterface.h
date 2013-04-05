#ifndef QMLCONTENTEXPOSERINTERFACE_H
#define QMLCONTENTEXPOSERINTERFACE_H

#include <QQmlContext>

namespace View
{
class   QmlContentExposerInterface
{
public :
    virtual void    exposeContentToQml(QQmlContext *context) = 0;
};
}
Q_DECLARE_INTERFACE(View::QmlContentExposerInterface, "com.tepee3d.View.QmlContentExposerInterface/1.0")



#endif // QMLCONTENTEXPOSERINTERFACE_H
