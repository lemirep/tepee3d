#include <iostream>
#include "agendaplugin.h"

AgendaPlugin::AgendaPlugin()
{
}


// ALL the function should be implemented

int AgendaPlugin::getPluginId()
{
    return PLUGIN_ID;
}

void AgendaPlugin::initPlugin()
{
    this->m_synchingWithSB = false;
    this->setPluginState("shows_view");
    this->currentWebQueriesCount = 0;
    QObject::connect(this, SIGNAL(executeHttpRequest(QNetworkRequest,int,QHttpMultiPart*,QObject*,int,void*)),
                     this, SLOT(webQueryEmitted()));
    this->currentDate = QDate::currentDate();
    this->currentDate.setDate(this->currentDate.year(), this->currentDate.month(), 1);
}

void AgendaPlugin::clearPluginBeforeRemoval()
{
}

QString AgendaPlugin::getPluginName()
{
    return QString("AgendaPlugin");
}

QString AgendaPlugin::getPluginDescription()
{
    return QString("AgendaPlugin.qml");
}

Plugins::PluginBase* AgendaPlugin::getPluginBase()
{
    return this;
}

QString AgendaPlugin::getRoomPluginQmlFile() const
{
    return QString("AgendaPlugin.qml");
}

QString AgendaPlugin::getMenuPluginQmlFile() const
{
    return QString("Menu.qml");
}

void AgendaPlugin::onIdleFocusState()
{
    qDebug() << "AgendaPlugin idling";
}

void AgendaPlugin::onSelectedFocusState()
{
    qDebug() << "AgendaPlugin Selected";
}

void AgendaPlugin::onFocusedFocusState()
{
    qDebug() << "AgendaPlugin Focused";

}

Plugins::PluginBase* AgendaPlugin::createNewInstance()
{
    return new AgendaPlugin();
}

void    AgendaPlugin::receiveResultFromSQLQuery(QList<QSqlRecord> result, int id, void *data)
{
    (this->*this->databaseCallBacks[id])(result, data);
}


void    AgendaPlugin::receiveResultFromHttpRequest(QNetworkReply *reply, int id, void *data)
{
   this->currentWebQueriesCount--;
   (this->*this->webServicesCallBacks[id])(reply, data);
   emit synchingChanged();
}


// SERIESPLUGIN PROPERTIES

QString AgendaPlugin::pluginState() const
{
    return this->m_pluginState;
}

void AgendaPlugin::setPluginState(const QString& value)
{
    this->m_pluginState = value;
    emit pluginStateChanged();
}

QString AgendaPlugin::sickBeardApi() const
{
    return this->m_sickBeardApiKey;
}

QString AgendaPlugin::sickBeardUrl() const
{
    return this->m_sickBeardUrl;
}

bool AgendaPlugin::addToSickBeard() const
{
    return this->m_addToSickBeard;
}

void AgendaPlugin::setSickBeardUrl(const QString &sickBeardUrl)
{
    this->m_sickBeardUrl = sickBeardUrl;
    if (this->m_sickBeardUrl.endsWith("/"))
        this->m_sickBeardUrl.chop(1);
    emit sickBeardUrlChanged();
}

void AgendaPlugin::setSickBeardApi(const QString &sickBeardApi)
{
    this->m_sickBeardApiKey = sickBeardApi;
    emit sickBeardApiChanged();
}

void AgendaPlugin::setAddToSickBeard(bool value)
{
    this->m_addToSickBeard = value;
    emit addToSickBeardChanged();
}

bool AgendaPlugin::getSynching() const
{
    return (this->currentWebQueriesCount != 0);
}

QString AgendaPlugin::getMonth() const
{
    return QDate::longMonthName(this->currentDate.month());
}

int     AgendaPlugin::getBeginDayOfTheMonth() const
{
    return (this->currentDate.dayOfWeek());
}

int     AgendaPlugin::getMonthLength() const
{
    qDebug() << "Length " << this->currentDate.daysInMonth();
    return (this->currentDate.daysInMonth());
}

