#ifndef IMAGESCREEN_H
#define IMAGESCREEN_H

#include <QWidget>

class RtImage : public QWidget
{
private:
    QPixmap  *_image;
    qreal   _rotation;
    qreal   _zoom;

public:
    RtImage(QWidget *parent = 0,QPixmap *pImage=NULL);
    void setImage( QPixmap *pImage);
    void setAngle( qreal degrees );
    void onZoomOut();
    void onZoomIn();

protected:
    void paintEvent(QPaintEvent *event);

};

#endif // IMAGESCREEN_H
