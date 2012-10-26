#include "BufferedTextureSource.h"
// FOR DEBUG
#include <iostream>
#include <QSGSimpleRectNode>

BufferedTextureSource::BufferedTextureSource(QQuickItem *parent) : QQuickItem(parent)
{
    this->mTextureProvider = NULL;
    this->mTexture = NULL;
    this->mSourceItem = NULL;

    // TELL THE QML ENGINE OUR QQUICKITEM IS RENDERED IN THE SCENEGRAPH
    this->setFlag(QQuickItem::ItemHasContents, true);

    std::cout << "CREATED NEW BUFFERED TEXTURE SOURCE" << std::endl;
}

bool BufferedTextureSource::isTextureProvider() const
{
    std::cout << " IN IS TEXTURE PROVIDER" << std::endl;
    return true;
}

QSGTextureProvider* BufferedTextureSource::textureProvider() const
{
    std::cout << ")))))))))))))TEXTURE PROVIDER CALLED" << std::endl;
    if (this->mTextureProvider == NULL)
    {

        const_cast<BufferedTextureSource *>(this)->mTextureProvider = new BufferedTextureProvider() ;
        const_cast<BufferedTextureSource *>(this)->ensureTexture();
        QObject::connect(this->mTexture, SIGNAL(updateRequested()), this->mTextureProvider, SIGNAL(textureChanged()));
        this->mTextureProvider->sourceTexture = this->mTexture;
    }
    return this->mTextureProvider;
}

QSGNode*    BufferedTextureSource::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *nodeData)
{
    //// WHERE DRAWING OF QQUICKITEM IN THE SCENEGRAPH TAKES PLACE
    std::cout << " UPDATE PAINT NODE " << std::endl;

    if (this->mSourceItem)
    {
        this->ensureTexture();

        QSize txtSize = QSize(qCeil(qAbs(this->mSourceItem->width())), qCeil(qAbs(this->mSourceItem->height())));
        this->mTexture->setFormat(this->mFormat);
        this->mTexture->setTextureSize(txtSize);
        this->mTexture->setItem(this->mSourceItem);
        this->mTexture->setAlphaChannel(true);
        this->mTexture->setMipmaps(false);


        if (this->mTextureProvider != NULL)
        {
            QSGTexture::WrapMode hWrap;
            QSGTexture::WrapMode wWrap;
            BufferedTextureSource::getWrapMode(this->mWrapMode, &hWrap, &wWrap);
            std::cout << "CREATING PROVIDER" << std::endl;
            this->mTextureProvider->filtering = QSGTexture::None;
            this->mTextureProvider->mipmapFiltering = QSGTexture::None;
            this->mTextureProvider->horizontalWrap = hWrap;
            this->mTextureProvider->verticalWrap = wWrap;
        }

        std::cout << "UPDATE REQUEST OF TEXTURE IN updatePaintNode" << std::endl;
        //        emit (this->mTexture->updateRequested());
        this->mTexture->scheduleUpdate();


//        QSGSimpleRectNode *n = static_cast<QSGSimpleRectNode *>(oldNode);
//        if (!n) {
//            n = new QSGSimpleRectNode();
//            n->setColor(Qt::red);
//        }
//        n->setRect(0, 0, this->sourceItem()->width(), this->sourceItem()->height());
//        return n;



        BufferedTextureGSNode *node = static_cast<BufferedTextureGSNode *>(oldNode);
        if (node == NULL)
        {
            std::cout << "CREATING NEW NODE 0" << std::endl;
            node = new BufferedTextureGSNode();
            std::cout << "CREATING NEW NODE 1" << std::endl;
            node->setTexture(this->mTexture);
            std::cout << "CREATING NEW NODE 2" << std::endl;
            QObject::connect(this->mTexture, SIGNAL(updateRequested()), node, SLOT(makeDirtyTexture()));
            std::cout << "CREATING NEW NODE 3" << std::endl;
        }

        node->setFiltering(this->mTextureProvider->filtering);
        node->setRect(0, 0, this->sourceItem()->width(), this->sourceItem()->height());
        // TO REPLACE BY LINE BELOW WHEN IT STARTS WORKING
        //        node->setRect(0, 0, this->width(), this->height());

        node->markDirty(QSGNode::DirtyMaterial);

        std::cout << "Returning new node" << std::endl;
        return node;
    }
    else
    {
        if (this->mTexture != NULL)
            this->mTexture->setItem(NULL);
    }
    return NULL;
}

void        BufferedTextureSource::ensureTexture()
{
    std::cout << "IN ENSURE TEXTURE " << std::endl;
    if (this->mTexture == NULL)
    {
        this->mTexture = new BufferedTextureQSGTexture();
        // CONNECT SIGNALS FROM TEXTURE HERE EVENTUALLY
        QObject::connect(this->mTexture, SIGNAL(updateRequested()), this, SLOT(update()));
        QObject::connect(this->mTexture, SIGNAL(updateRequested()), this, SLOT(updateTest()));
        QObject::connect(this->mTexture, SIGNAL(scheduledUpdateCompleted()), this, SIGNAL(scheduledUpdateCompleted()));
    }
}

void        BufferedTextureSource::updateTest()
{
    std::cout << "updateRequested Signal Received" << std::endl;
}

QQuickItem* BufferedTextureSource::sourceItem() const
{
    return this->mSourceItem;
}

BufferedTextureSource::WrapMode    BufferedTextureSource::wrapMode() const
{
    return this->mWrapMode;
}

BufferedTextureSource::Format      BufferedTextureSource::format() const
{
    return this->mFormat;
}

QSize       BufferedTextureSource::textureSize() const
{
    return this->mTextureSize;
}

bool        BufferedTextureSource::live() const
{
    return this->mLive;
}

void        BufferedTextureSource::setSourceItem(QQuickItem *sourceItem)
{
    std::cout << "Source Item Set" << std::endl;
    this->mSourceItem = sourceItem;
    this->update(); // Schedule a call to updatePaintNode which lives in another thread
}

void        BufferedTextureSource::setWrapMode(WrapMode wrapMode)
{
    this->mWrapMode = wrapMode;
    this->update(); // Schedule a call to updatePaintNode which lives in another thread
}

void        BufferedTextureSource::setFormat(Format format)
{
    this->mFormat = format;
    this->update(); // Schedule a call to updatePaintNode which lives in another thread
}

void        BufferedTextureSource::setTextureSize(QSize textureSize)
{
    this->mTextureSize = textureSize;
    this->update(); // Schedule a call to updatePaintNode which lives in another thread
}

void        BufferedTextureSource::setLive(bool live)
{
    std::cout << "Setting Live To " << live << std::endl;
    this->mLive = live;
    this->update(); // Schedule a call to updatePaintNode which lives in another thread
}

void BufferedTextureSource::getWrapMode(BufferedTextureSource::WrapMode mode, QSGTexture::WrapMode *hWrap, QSGTexture::WrapMode *vWrap)
{
    switch (mode)
    {
    case BufferedTextureSource::RepeatHorizontally:
        *hWrap = QSGTexture::Repeat;
        *vWrap = QSGTexture::ClampToEdge;
        break;
    case BufferedTextureSource::RepeatVertically:
        *vWrap = QSGTexture::Repeat;
        *hWrap = QSGTexture::ClampToEdge;
        break;
    case BufferedTextureSource::Repeat:
        *hWrap = *vWrap = QSGTexture::Repeat;
        break;
    default:
        // QQuickShaderEffectSource::ClampToEdge
        *hWrap = *vWrap = QSGTexture::ClampToEdge;
        break;
    }
}
