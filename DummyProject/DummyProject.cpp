#include "DummyProject.h"

DummyProject::DummyProject() : PluginBase()
{
    this->initPlugin();
}

int DummyProject::getPluginId() const
{
    return ;
}

void DummyProject::initPlugin()
{
}

void DummyProject::clearPluginBeforeRemoval()
{
}

QString DummyProject::getPluginName() const
{
    return QString("DummyProject");
}

QString DummyProject::getPluginVersion() const
{
    return QString("0.0.1");
}

QString DummyProject::getPluginRepoName() const
{
    return QString("DummyProject");
}

QString DummyProject::getPluginDescription() const
{
    return QString("DummyProject description");
}

QString DummyProject::getRoomPluginQmlFile() const
{
    return QString("DummyProject.qml");
}

QString DummyProject::getMenuPluginQmlFile() const
{
    return QString("Menu.qml");
}

Plugins::PluginBase* DummyProject::createNewInstance()
{
    return new DummyProject();
}

void    DummyProject::receiveResultFromSQLQuery( QList<QSqlRecord> , int , void *)
{
}

void    DummyProject::receiveResultFromHttpRequest(QNetworkReply *reply, int , void *)
{
    qDebug() << reply->readAll();
}

void	DummyProject::onIdleFocusState()
{
}

void	DummyProject::onSelectedFocusState()
{
}

void	DummyProject::onFocusedFocusState()
{
}
