#ifndef BUFFEREDTEXTURESOURCE_H
#define BUFFEREDTEXTURESOURCE_H

#include <QtQuick/QQuickItem>
#include <QOpenGLFramebufferObject>
#include <QtCore/qmath.h>
#include "BufferedTextureProvider.h"
#include "BufferedTextureGSNode.h"

class BufferedTextureQSGTexture;
class BufferedTextureProvider;

class BufferedTextureSource : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(WrapMode wrapMode READ wrapMode WRITE setWrapMode NOTIFY wrapModeChanged)
    Q_PROPERTY(QQuickItem *sourceItem READ sourceItem WRITE setSourceItem NOTIFY sourceItemChanged)
    Q_PROPERTY(QSize textureSize READ textureSize WRITE setTextureSize NOTIFY textureSizeChanged)
    Q_PROPERTY(bool live READ live WRITE setLive NOTIFY liveChanged)
    Q_PROPERTY(Format format READ format WRITE setFormat NOTIFY formatChanged)

    Q_ENUMS(WrapMode Format)

public:
    enum WrapMode
    {
        ClampToEdge,
        RepeatHorizontally,
        RepeatVertically,
        Repeat
    };

    enum Format
    {
        Alpha = GL_ALPHA,
        RGB = GL_RGB,
        RGBA = GL_RGBA
    };

public:

    BufferedTextureSource(QQuickItem *parent = 0);
    bool isTextureProvider() const;
    QSGTextureProvider *textureProvider() const;

private:

    BufferedTextureProvider     *mTextureProvider;
    BufferedTextureQSGTexture   *mTexture;
    QQuickItem         *mSourceItem;
    WrapMode            mWrapMode;
    Format              mFormat;
    QSize               mTextureSize;
    bool                mLive;

    void                ensureTexture();

private slots:
    void                updateTest();

public:

    QQuickItem         *sourceItem()  const;
    WrapMode            wrapMode()    const;
    Format              format()      const;
    QSize               textureSize() const;
    bool                live()        const;

    void                setSourceItem(QQuickItem *sourceItem);
    void                setWrapMode(WrapMode wrapMode);
    void                setFormat(Format format);
    void                setTextureSize(QSize textureSize);
    void                setLive(bool live);

    static void         getWrapMode(BufferedTextureSource::WrapMode mode,  QSGTexture::WrapMode *hWrap, QSGTexture::WrapMode *vWrap);

protected :
    QSGNode *   updatePaintNode(QSGNode *, UpdatePaintNodeData *);

signals :

    void                sourceItemChanged();
    void                wrapModeChanged();
    void                formatChanged();
    void                textureSizeChanged();
    void                liveChanged();
    void                scheduledUpdateCompleted();
};

#endif // BUFFEREDTEXTURESOURCE_H
