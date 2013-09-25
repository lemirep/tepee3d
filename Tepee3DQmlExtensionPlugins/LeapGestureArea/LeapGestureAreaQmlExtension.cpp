
#include "LeapGestureAreaQmlExtension.h"

void LeapGestureAreaQmlExtension::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("LeapGestureArea"));
    qmlRegisterType<Tepee3DQmlExtensions::LeapGestureArea>(uri, 1, 0, "LeapGestureArea");
}
