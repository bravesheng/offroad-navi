#ifndef RTKEYBUTTON_H
#define RTKEYBUTTON_H

#define __MOVE_INTERVAL__   5

#include <QPushButton>
class RtKeyButton: public QPushButton
{
        Q_OBJECT
public:
    enum{
        AlignLeftTop,
        AlignRightBottom,
        AlignLeftBottom,
        AlignRightTop,
        AlignBottomCenter,
        AlignTopCenter,
        AlignLeftCenter,
        AlignRightCenter,
        AlignCenter,
    };
        RtKeyButton(QWidget *parent=NULL, int iListIndex = -1);

        int  GetImageHeight(void);
        void setTopLeft(int iX,int iY);
        void SetImages(QPixmap *pimgUp = NULL,
                   QPixmap *pimgDown = NULL,
                   QPixmap *pimgSelect = NULL,
                   QPixmap *pimgDisable = NULL);
        void setButtonText(QString &strText,QRect &rectText);
        void SetListIndex(int iListIndex) { m_iListIndex = iListIndex; };
        void setAlignStyle(int iStyle);
        void setExtKey(bool bExtKey);
        void EnableKeyButton(bool bEnable);

private:
        QPoint getLeftTopOffset(int iStyle);

protected:
    int            m_iListIndex; // -1: Normal button
    int            m_iStartY;
    int            m_iStyle;
    bool           m_bIsScroll;
    bool           m_bExtKey;

    QPixmap        *m_pimgUp;
    QPixmap        *m_pimgDown;
    QPixmap        *m_pimgSelect;
    QPixmap        *m_pimgDisable;

    QRect           m_RectText;

    QPoint          m_LeftTop;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void leaveEvent ( QEvent * event );
    void paintEvent(QPaintEvent* /*event*/);
    virtual void paintCustomEvent(QPaintEvent* /*event*/){};

// New Add slots/signals
signals:
    void MousePress(int iPressY,int iListIndex);
    void MoveInterval(int iDiffY);
    void MouseRelease();
    void ButtonClick(int iListIndex);

public slots:
    void ButtonScroll();
    void ButtonClicked();
};

#endif // RtKeyButton_H
