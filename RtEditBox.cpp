#include <QPainter>
#include "RtEditBox.h"

RtEditBox::RtEditBox(QWidget *parent)
    : QLineEdit(parent)
{
    m_pEditBK = NULL;

    //Set the background brush as transparent
    QPalette palette = this->palette();
    QBrush brush(QColor(0, 0, 0, 0));
    brush.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::All, QPalette::Base, brush);
    palette.setColor(QPalette::Text,QColor(255,255,255));
    this->setPalette(palette);
    this->setFrame(false);
}

RtEditBox::~RtEditBox()
{
}

void RtEditBox::setImages(QPixmap *pimgBK)
{
    if(pimgBK)
    {
        m_pEditBK = pimgBK;
//        setGeometry(0,0,m_pEditBK->width(),m_pEditBK->height());
    }
}

void RtEditBox::paintEvent ( QPaintEvent *event )
{
    if(m_pEditBK)
    {
        QPainter painter(this);
        painter.drawPixmap(0, 0, *m_pEditBK);
    }

    QLineEdit::paintEvent(event);
}
