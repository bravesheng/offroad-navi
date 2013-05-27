#ifndef WEDITSCREEN_H
#define WEDITSCREEN_H

#include <QDialog>
#include <QLabel>
#include "RtPushButton.h"
#include "RtEditButton.h"
#include "RtGlobalDefine.h"
#include "RtKeyboard.h"
#include "buttons.h"
#include "Track.h"

typedef enum _DLG_RETURN_TYPE_
{
	DLG_RETURN_SAVE,
	DLG_RETURN_DELETE,
	DLG_RETURN_CANCEL
} DLG_RETURN_TYPE;

#define __ICON_NUMS__   10
class TEditScreen : public QDialog
{
    Q_OBJECT
public:
	enum
	{
		BTN_TYPE_SAVE_DEL,
		BTN_TYPE_SAVE_ONLY
	};
	TEditScreen(QWidget *parent, CTrack* pTrack, int iBtnType = BTN_TYPE_SAVE_DEL);
    ~TEditScreen();

public slots:
    void IconClicked();
    void NameClicked();
    void ButtonClick(int iSelect);
    void OnSave();
    void OnDelete();
	void OnCancel();
	void DoEffect();

private:
	CTrack* m_pTrack;
    CReturnButton ReturnBtn;
	void PrepareParametersIntoWidget(void);
    QString getEditText(void);
    void setEditText(QString& strText);
    void setIconIdx(int iIconIdx);

private Q_SLOTS:
    void keySelected (const QString& key);
    void backspace(void);
    void switchKeypad(void);

protected:
    int            m_iSelect;
	int			   m_iBtnType;//0:Save,Delete , 1: Save only
	QPixmap        *m_pImageBackground;
    QPixmap        m_ImageSymbol[BUTTON_IMG_COUNT];
    QPixmap        m_ImageIcons[BUTTON_IMG_COUNT][BUTTON_IMG_COUNT];
	QPixmap		   *m_pImageBtnUp[BUTTON_IMG_COUNT];
	QPixmap		   *m_pImageBtnDown;
	QPixmap		   *m_pImageIcon[BUTTON_IMG_COUNT];
    QPixmap        *m_pImageName[BUTTON_IMG_COUNT];
    QPixmap        *m_pImageSave[BUTTON_IMG_COUNT];
    QPixmap        *m_pImageDelete[BUTTON_IMG_COUNT];
    QPixmap        m_ImageCancel[BUTTON_IMG_COUNT];
    QLabel         *m_pLabelTitle;
    QTimer         *m_pQTimerEffect;
    RtPushButton   *m_pPushButtonSave;
    RtPushButton   *m_pPushButtonDelete;
    RtPushButton   *m_pPushButtonCancel;
    RtPushButton   *m_pPushButtonIcon;
    RtEditButton   *m_pPushButtonName;
    RtPushButton   *m_pButtonSelected;
    RtPushButton   *m_pButtonIcons[__ICON_NUMS__];
    RtKeyboard     *m_pKeyboard;

    void paintEvent(QPaintEvent *event);
    void PrepareMainIconImage(QPixmap &imageUp, QPixmap &imageDown, int iNo);
    void PrepareIconImage(QPixmap &imageUp, QPixmap &imageDown, int iNo);
	bool CheckWhiteSpace(void);
};

#endif // TEditScreen_H
