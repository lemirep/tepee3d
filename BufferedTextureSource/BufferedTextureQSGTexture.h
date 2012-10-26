#ifndef BUFFEREDTEXTUREQSGTEXTURE_H
#define BUFFEREDTEXTUREQSGTEXTURE_H

#include <QtQuick/QSGDynamicTexture>
#include <QtQuick/QQuickItem>
#include <QOpenGLFramebufferObject>
#include <QtQuick/QQuickWindow>
#include <QSize>
#include <QImage>
#include <stdlib.h>
#include "BufferedTextureSource.h"

class BufferedTextureQSGTexture : public QSGDynamicTexture
{
    Q_OBJECT
public:

    BufferedTextureQSGTexture();
    ~BufferedTextureQSGTexture();

private :
    bool                                     mAlphaChannel;
    bool                                     mMipmaps;
    bool                                     mIsTextureDirty;
    QSize                                    mSize;
    QRectF                                   mRect;
    GLenum                                   mFormat;
    QQuickItem                              *mItem;
    QQuickWindow                            *textureRenderer;
    QOpenGLFramebufferObject                *mFbo;
    QOpenGLFramebufferObject                *mSecondaryFbo;
    bool                                     updateRequest;

    int     textureId()             const;
    void    bind();
    bool    hasAlphaChannel()       const;
    bool    hasMipmaps()            const;
    bool    updateTexture();
    QSize   textureSize()           const;
    void    grab();



public :
    void    setItem(QQuickItem *item);
    void    setAlphaChannel(bool alphaChannel);
    void    setMipmaps(bool mipmaps);
    void    setTextureSize(QSize size);
    void    setRect(QRect rect);
    void    setFormat(GLenum format);
    void    scheduleUpdate();

//    QImage  toImage() const;

signals :

    void    updateRequested();
    void    scheduledUpdateCompleted();

private slots:

    void    markDirtyTexture();
    void    beforeRendering();
    void    afterRendering();
    void    initializeTextureRenderer();
};

#endif // BUFFEREDTEXTUREQSGTEXTURE_H
