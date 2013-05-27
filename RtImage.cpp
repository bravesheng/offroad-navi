#include <QPainter>
#include "RtImage.h"

RtImage::RtImage(QWidget *parent,QPixmap *pImage)
        : QWidget(parent)
{
    _image = pImage;
    _zoom = 1.0;
}

void RtImage::paintEvent(QPaintEvent*)//event
{
    if(_image)
    {
        int x  = width()/2-_image->width()/2;
        int y  = height()/2-_image->height()/2;
        int x2 = width()/2;
        int y2 = height()/2;

        QPointF c(x2, y2);
        QPainter painter(this);
        painter.translate(c);
        painter.rotate(_rotation);
        painter.scale(_zoom, _zoom);
        painter.translate(-c);
        painter.drawPixmap(QPoint(x, y), *_image);
        painter.end();
    }
}

void RtImage::onZoomOut()
{
    _zoom -= 0.5;
    update();
}

void RtImage::onZoomIn()
{
    _zoom += 0.5;
    update();
}

void RtImage::setAngle(qreal degrees )
{
    _rotation = degrees;
    update();
}

void RtImage::setImage( QPixmap *pImage)
{
    if(!pImage->isNull())
        _image = pImage;
}

