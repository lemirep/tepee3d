#include "BufferedTextureQSGTexture.h"

#include <iostream>

BufferedTextureQSGTexture::BufferedTextureQSGTexture() : QSGDynamicTexture()
{
    std::cout << ">>>>>>>>>>>>>Texture is Created" << std::endl;

    this->textureRenderer = new QQuickWindow();
    this->mItem = NULL;
    this->mFbo = NULL;
    this->mSecondaryFbo = NULL;
    this->mAlphaChannel = false;
    this->mMipmaps = false;
    this->mIsTextureDirty = false;
    this->mFormat = GL_RGB;
    this->updateRequest = false;
    //    this->updateTexture();
    QObject::connect(this->textureRenderer, SIGNAL(beforeSynchronizing()), this, SLOT(initializeTextureRenderer()), Qt::DirectConnection);
    std::cout << "Texture is Created" << std::endl;
}

BufferedTextureQSGTexture::~BufferedTextureQSGTexture()
{

}


void    BufferedTextureQSGTexture::initializeTextureRenderer()
{
    QObject::connect(this->textureRenderer, SIGNAL(beforeRendering()),this, SLOT(beforeRendering()), Qt::DirectConnection);
    QObject::connect(this->textureRenderer, SIGNAL(afterRendering()),this, SLOT(afterRendering()), Qt::DirectConnection);
}

void    BufferedTextureQSGTexture::beforeRendering()
{
    std::cout << "-----Before Rendering" << std::endl;
}

void    BufferedTextureQSGTexture::afterRendering()
{
    std::cout << "-----After Rendering" << std::endl;
}

void    BufferedTextureQSGTexture::markDirtyTexture()
{
    std::cout << "Texture is dirty requesting update " << std::endl;
    this->mIsTextureDirty = true;
    if (this->updateRequest)
        emit (updateRequested());
}

void    BufferedTextureQSGTexture::bind()
{
    std::cout << "TEXTURE IS BINDED" << std::endl;
    glBindTexture(GL_TEXTURE_2D, (this->mFbo != NULL) ? this->mFbo->texture() : 0);
    this->updateBindOptions(false);
}


int     BufferedTextureQSGTexture::textureId() const
{
    if (this->mFbo != NULL)
        return this->mFbo->texture();
    return 0;
}

QSize   BufferedTextureQSGTexture::textureSize() const
{
    return this->mSize;
}

bool    BufferedTextureQSGTexture::updateTexture()
{
    std::cout << " ++++++++++ UPDATE TEXTURE 1" << std::endl;
    bool doGrab = this->updateRequest && this->mIsTextureDirty;
    if (doGrab)
        this->grab();
    if (this->updateRequest)
        emit (scheduledUpdateCompleted());
    this->updateRequest = false;
    return doGrab;
}

void    BufferedTextureQSGTexture::grab()
{
    std::cout << "GRAB" << std::endl;
    if (this->mItem == NULL)
        std::cout << "mItemIsNull" << std::endl;
    if (mItem && !mSize.isNull())
    {
        std::cout << " ++++++++++ UPDATE TEXTURE 2" << std::endl;
        // CREATE FRAME BUFFER OBJECT
        QOpenGLFramebufferObjectFormat format;
        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        format.setInternalTextureFormat(this->mFormat);
        format.setMipmap(this->mMipmaps);
        this->mFbo = new QOpenGLFramebufferObject(this->mSize, format);
        // SET RENDER TARGET TO FBO
        this->textureRenderer->setRenderTarget(this->mFbo);
        this->mIsTextureDirty = false;
        emit (scheduledUpdateCompleted());
    }
}

bool    BufferedTextureQSGTexture::hasAlphaChannel() const
{
    return this->hasAlphaChannel();
}

bool    BufferedTextureQSGTexture::hasMipmaps() const
{
    return this->hasMipmaps();
}

void    BufferedTextureQSGTexture::setItem(QQuickItem *item)
{
    if (this->mItem != item)
    {
        std::cout << "Setting Source Item in Texture" << std::endl;
        this->mItem = item;
        // SET mItem AS ELEMENT TO RENDER IN RENDER BY SETTING THE RENDERER'S ROOT ITEM AS ITS PARENT
//        this->mItem->setParentItem(this->textureRenderer->rootItem());
        markDirtyTexture();
    }
}

void    BufferedTextureQSGTexture::setAlphaChannel(bool alphaChannel)
{
    if (this->mAlphaChannel != alphaChannel)
    {
        this->mAlphaChannel = alphaChannel;
        markDirtyTexture();
    }
}

void    BufferedTextureQSGTexture::setMipmaps(bool mipmaps)
{
    if (this->mMipmaps != mipmaps)
    {
        this->mMipmaps = mipmaps;
        markDirtyTexture();
    }
}

void    BufferedTextureQSGTexture::setTextureSize(QSize size)
{
    if (this->mSize != size)
    {
        this->mSize = size;
        markDirtyTexture();
    }
}

void    BufferedTextureQSGTexture::setRect(QRect rect)
{
    if (this->mRect != rect)
    {
        this->mRect = rect;
        markDirtyTexture();
    }
}

void    BufferedTextureQSGTexture::setFormat(GLenum format)
{
    if (this->mFormat != format)
    {
        this->mFormat = format;
        markDirtyTexture();
    }
}

//QImage  BufferedTextureQSGTexture::toImage() const
//{
//    if (this->mFbo != NULL)
//    {
//        std::cout << "{{{{{FBO NOT NULL }}}}}" << std::endl;
//        return this->mFbo->toImage();
//    }
//    return QImage();
//}

void    BufferedTextureQSGTexture::scheduleUpdate()
{
    std::cout << "QSGTexture scheduleUpdate" << std::endl;
    std::cout << "dirty " << this->mIsTextureDirty << " update " << this->updateRequest << std::endl;
    if (this->updateRequest)
        return ;
    this->updateRequest = true;
    std::cout << "scheduleUpdate step 2 " << std::endl;
    if (this->mIsTextureDirty)
    {
        std::cout << "scheduleUpdate step 3 --> emit updateRequested" << std::endl;
        emit (updateRequested());
    }
}

