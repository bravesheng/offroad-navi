#ifndef RTPUSHBUTTON_H
#define RTPUSHBUTTON_H

#define __MOVE_INTERVAL__   5

#include <QPushButton>
class RtPushButton: public QPushButton
{
	friend class RtListBox;
        Q_OBJECT
public:
        RtPushButton(QWidget *parent);

        int GetImageHeight(void);
        void SetImages(QPixmap *pimgUp = NULL,
                   QPixmap *pimgDown = NULL,
                   QPixmap *pimgSelect = NULL,
                   QPixmap *pimgDisable = NULL);
        void SetButtonText(QString &strText,QRect &rectText,int Align = Qt::AlignCenter, int FontSize = 8);

protected:
    int				m_iListIndex; // -1: Normal button
    int				m_iStartY;
    bool			m_bIsScroll;

    QPixmap			*m_pimgUp;
    QPixmap         *m_pimgDown;
    QPixmap         *m_pimgSelect;
    QPixmap         *m_pimgDisable;

    QRect           m_RectText;
	int				m_FontSize;
	int				m_AlignFlag;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent* /*event*/);
    virtual void paintCustomEvent(QPaintEvent* /*event*/){};
    void SetListIndex(int iListIndex);
// New Add slots/signals
signals:
    void MousePress(int iPressY);
    void MoveInterval(int iDiffY);
    void MouseRelease();
    void ButtonClick(int iListIndex);

public slots:
    void ButtonScroll();
    void ButtonClicked();
};

#endif // RtPushButton_H
