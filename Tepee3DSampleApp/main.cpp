#include <QApplication>
#include "QmlViewManager.h"



Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QApplication *app = new QApplication(argc, argv);
    QmlViewManager* manager = QmlViewManager::getInstance();
    manager->initView();

    return app->exec();
}
