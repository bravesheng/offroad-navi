#ifndef RtSettingButton_H
#define RtSettingButton_H

#define __ICON1_OFFSETX__   8
#define __ICON1_WIDTH__     29
#define __ICON2_OFFSETX__   280
#define __ICON2_WIDTH__     25

#define __TEXT1_OFFSETX__   40
#define __TEXT1_WIDTH__     120
#define __TEXT2_OFFSETX__   165
#define __TEXT2_WIDTH__     55

#define __TOUCH_INTERVAL__  5

#include <QPushButton>
//#include <QAbstractButton>
class RtSettingButton: public QPushButton
{
        Q_OBJECT
public:
        RtSettingButton(QWidget *parent, int iListIndex = -1);

        int GetImageHeight(void);
        void SetImages(QPixmap *pimgUp = NULL,QPixmap *pimgDown = NULL,QPixmap *pimgSelect = NULL);
        void SetComponent(QPixmap *pIconA,QString &Text1,QString &Text2,QPixmap *pIconB);
		void SetText1(QString &Text1);
        void SetIconB(QPixmap *pIconB);
        void SetIconB_OffsetX(int iOffsetX);
		void SetListIndex(int iListIndex) { m_iListIndex = iListIndex; };

protected:
	int			   m_iIconBOffsetX;
    int            m_iListIndex; // -1: Normal button
    int            m_iStartY;
	int			   m_iStartX;
    bool           m_bIsScroll;

    QPixmap         *m_pimgUp;
    QPixmap         *m_pimgDown;
    QPixmap         *m_pimgSelect;
	QPixmap			*m_pimgDisable;

    QPixmap         *m_pimgIconA;
    QPixmap         *m_pimgIconB;

    QString        m_strText1;
    QString        m_strText2;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

// New Add slots/signals
signals:
    void MousePress(int iPressY);
    void MoveInterval(int iDiffY);
	void MoveIntervalX(int iListIndex,int iDiffX);
    void MouseRelease();
    void ButtonClick(int iListIndex);

public slots:
    void ButtonScroll();
    void ButtonClicked();
};

#endif // RtSettingButton_H
