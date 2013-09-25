#include "Tepee3DTouchAreaQmlExtensionPlugin.h"

void Tepee3DTouchAreaQmlExtensionPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("Tepee3DTouchArea"));
    qmlRegisterType<Tepee3DQmlExtensions::QQuickMultiPointTouchArea>(uri, 1, 0, "Tepee3DTouchArea");
    qmlRegisterType<Tepee3DQmlExtensions::QQuickTouchPoint>(uri, 1, 0, "Tepee3DTouchPoint");
    qmlRegisterType<Tepee3DQmlExtensions::QQuickGrabGestureEvent>(uri, 1, 0, "Tepee3DGrabGestureEvent");
}
