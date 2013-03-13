#include <QApplication>
#include "QmlViewManager.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QApplication *app = new QApplication(argc, argv);
    View::QmlViewManager* manager = View::QmlViewManager::getInstance();

    QObject::connect(manager, SIGNAL(quit()), app, SLOT(quit()));
    return app->exec();
}
