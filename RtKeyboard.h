#ifndef RTKEYBOARD_H
#define RTKEYBOARD_H

#include <QWidget>
#include <QSignalMapper>
#include <QTimer>
#include "RtKeyButton.h"
#include "RtExtKey.h"

#define __FUN_NUMS__         7
#define __AZ_NUMS__         26
#define __09_NUMS__         27


class RtKeyboard : public QWidget
{
    Q_OBJECT
public:
    RtKeyboard(QWidget *parent = NULL);
    void setKeypadFlag(int iPadFlag);
	void EnableKeyButton(bool bEnable);
	void CloseExtDlg(void);

Q_SIGNALS:
    void keySelected (const QString& key);
    void backspace(void);
    void switchKeypad(void);

public slots:
    void MousePress(int iPressY,int iIndex);
    void MouseFuncPress(int iPressY,int iIndex);
    void MouseRelease();
    void ButtonClick(int iIndexKey);
    void switchUpperLower(void);
    void switchAZ09(void);
    void EnableExtKey(void);

private:
    void LoadButtonImages(void);
    void setupKeyboardAZ(void);
    void setupKeyboard09(void);
    void setupFuncKey(void);
    void switchABCabc(void);
    void switchSpecialWord(void);

    void ShowAZ_Keypad(bool bShow);
    void Show09_Keypad(bool bShow);

protected:
    enum{
        KEYPAD_AZ,
        KEYPAD_09,
        KEYPAD_NUMS
    };
    enum{
        KEYPAD_UPPER_CASE,
        KEYPAD_LOWER_CASE,
        KEYPAD_STYLE_NUMS
    };
    enum{
        __FUN_KEY_0__ = 0,
        __FUN_KEY_1__,
        __FUN_KEY_2__,
        __FUN_KEY_3__,
        __FUN_KEY_4__,
        __FUN_KEY_5__,
        __FUN_KEY_6__
    };
    int             m_ABCabcFlag;// 0:A~Z, 1:a~z
    int             m_SpecWordFlag;//0:0~9,1:other special character
    int             m_KeypadFlag;//0->a~z keypad,1->0~9 keypad
    QPixmap         m_ImageBackground;
    QPixmap         m_Key1[2];
    QPixmap         m_Key2[2];
    QPixmap         m_Key3[2];
    QPixmap         m_Key4[2];
    QPixmap         m_Key5[2];
    QPixmap         m_Key6[2];
    QPixmap         m_Key7[2];
    QPixmap         m_Key_Del[2];
    QPixmap         m_Key_Enter[2];
    QPixmap         m_Key_Switch[2];

    RtKeyButton    *m_pFuncButton[__FUN_NUMS__];
    RtKeyButton    *m_pKeyButton[__AZ_NUMS__];
    RtKeyButton    *m_pNumberButton[__09_NUMS__];
    RtKeyButton    *m_pSelectKey;
    RtExtKey       *m_pExtKey;
    QSignalMapper  *signalMapper;
    QTimer         *m_pExtTimer;
    QString        m_strExtKey;
    void paintEvent(QPaintEvent* /*event*/);
};

#endif // RtKeyboard_H
