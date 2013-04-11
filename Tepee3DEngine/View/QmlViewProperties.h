#ifndef QMLVIEWPROPERTIES_H
#define QMLVIEWPROPERTIES_H

#include <QObject>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QQmlContext>
#include "QmlContentExposerInterface.h"

namespace View
{
class QmlViewProperties : public QObject
{
    Q_OBJECT

private:
    QQuickView                  *viewer;
    QQmlEngine                  *qmlEngine;
    QQmlContext                 *qmlContext;

    explicit QmlViewProperties(QObject *parent = 0);

    static QmlViewProperties    *instance;

public:
    ~QmlViewProperties();
    static QmlViewProperties*   getInstance(QObject *parent = 0);
    static void                 exposeContentToQml(QObject* exposer);

    void                        setViewerSource(const QUrl& sourceFile);
    void                        showView();

signals:
    void                        quit();
public slots:
    
};
}
#endif // QMLVIEWPROPERTIES_H
