#ifndef RtEditBox_H
#define RtEditBox_H

#include <QWidget>
#include <QLineEdit>

class RtEditBox : public QLineEdit
{
public:
    RtEditBox(QWidget *parent = 0);
    void setImages(QPixmap *pimgBK = NULL);
    ~RtEditBox();

protected:
    void paintEvent ( QPaintEvent * event );
    QPixmap      *m_pEditBK;

};

#endif // RtEditBox_H
