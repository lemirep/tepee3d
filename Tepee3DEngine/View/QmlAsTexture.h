#ifndef QMLASTEXTURE_H
#define QMLASTEXTURE_H

#include <QQuickItem>
#include <QSGDynamicTexture>
#include <QQuickEffect>
#include <QSGTextureProvider>
#include <QTimer>

class QmlAsTexture : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem* sourceItem READ getSourceItem WRITE setSourceItem NOTIFY sourceItemChanged)
    Q_PROPERTY(QQuickEffect* effectItem READ getEffectItem WRITE setEffectItem NOTIFY effectItemChanged)
public:
    QmlAsTexture(QQuickItem* parent = 0);
    QQuickItem*     getSourceItem();
    void            setSourceItem(QQuickItem* sourceItem);
    QQuickEffect*   getEffectItem();
    void            setEffectItem(QQuickEffect* effectItem);

protected:
    QSGNode *       updatePaintNode(QSGNode * oldNode, UpdatePaintNodeData * updatePaintNodeData);

private:
    QQuickItem*         sourceItem;
    QQuickEffect*       effectItem;
    GLuint              textureId;
    QSGTextureProvider* provider;
    QSGTexture*         texture;


    void            applyTextureToEffect();

private slots:
    void            textureChanged();

signals:
    void    sourceItemChanged();
    void    effectItemChanged();


};

#endif // QMLASTEXTURE_H
