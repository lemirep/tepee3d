#ifndef PLUGINBASE_H
#define PLUGINBASE_H

#include <QObject>
#include "PluginInterface.h"

namespace Plugins
{

class PluginBase : public QObject, Plugins::PluginInterface
{
    Q_OBJECT
    Q_INTERFACES(Plugins::PluginInterface)
public:
    PluginBase();
    virtual int             getPluginId()               = 0;
    virtual void            initPlugin()                = 0;    //PERFORM NECESSARY INITIALIZATION HERE (HelperClasses, QmlModelClasses ...)
    virtual QString         getPluginName()             = 0;
    virtual QString         getPluginDescription()      = 0;
    PluginBase*             getPluginBase();
    virtual PluginBase*     createNewInstance()         = 0;

// Define all signals that a plugin can emit or receive
signals :
    void    execSqlQuery(QString query);
    void    execHttpRequest();

public slots :
    // Define slots as virtual so that developpers can subclass them if necessary
    virtual void    resultFromSQL();
};

}
#endif // PLUGINBASE_H
