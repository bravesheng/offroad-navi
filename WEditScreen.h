#ifndef WEDITSCREEN_H
#define WEDITSCREEN_H

#include <QDialog>
#include <QLabel>
#include <QTimeLine>
#include "RtPushButton.h"
#include "RtEditButton.h"
#include "RtGlobalDefine.h"
#include "RtKeyboard.h"
#include "buttons.h"

#define __ICON_NUMS__   10
class WEditScreen : public QDialog
{
    Q_OBJECT
public:
	enum{
		BTN_TYPE_SAVE_DEL,
		BTN_TYPE_SAVE_ONLY
	};
	WEditScreen(QWidget *parent = 0,int iBtnType=BTN_TYPE_SAVE_DEL);
    ~WEditScreen();
    QString getEditText(void);
    void setEditText(QString& strText);
    int  getIconIdx(void);
    void setIconIdx(int iIconIdx);

public slots:
    void IconClicked();
    void NameClicked();
    void ButtonClick(int iSelect);
    void OnSave();
    void OnDelete();
    void OnCancel();
    void setFrame(int frame);

private:
    CReturnButton ReturnBtn;

private Q_SLOTS:
    void keySelected (const QString& key);
    void backspace(void);
    void switchKeypad(void);

protected:
    int            m_iSelect;
    int            m_iStartX;
    int            m_iStartY;
	int			   m_iBtnType;//0:Save,Delete , 1: Save only
    QPixmap        *m_pImageBackground;
    QPixmap        m_ImageSymbol[BUTTON_IMG_COUNT];
    QPixmap        m_ImageIcons[BUTTON_IMG_COUNT][__ICON_NUMS__];
	QPixmap		   *m_pImageBtnUp[__ICON_NUMS__];
	QPixmap		   *m_pImageBtnDown;
	QPixmap		   *m_pImageIcon[BUTTON_IMG_COUNT];
    QPixmap        m_ImageName[BUTTON_IMG_COUNT];
    QPixmap        m_ImageSave[BUTTON_IMG_COUNT];
    QPixmap        m_ImageDelete[BUTTON_IMG_COUNT];
    QPixmap        m_ImageCancel[BUTTON_IMG_COUNT];
    QLabel         *m_pLabelTitle;
    QTimer         *m_pQTimerEffect;
    QTimeLine      *timeLine;
    RtPushButton   *m_pPushButtonSave;
    RtPushButton   *m_pPushButtonDelete;
    RtPushButton   *m_pPushButtonCancel;
	RtPushButton   *m_pPushButtonIcon;
    RtPushButton   *m_pButtonSelected;
    RtEditButton   *m_pPushButtonName;
    RtPushButton   *m_pButtonIcons[__ICON_NUMS__];
    RtKeyboard     *m_pKeyboard;

    void paintEvent(QPaintEvent *event);
    void PrepareMainIconImage(QPixmap &imageUp, QPixmap &imageDown, int iNo);
    void PrepareIconImage(QPixmap &imageUp, QPixmap &imageDown, int iNo);
	bool CheckWhiteSpace(void);
};

#endif // WEDITSCREEN_H
