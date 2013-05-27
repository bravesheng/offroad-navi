#include <QPainter>
#include "RtKeyboard.h"
#include "RtGlobalDefine.h"

#include <QMessageBox>

RtKeyboard::RtKeyboard(QWidget *parent)
        : QWidget(parent)
{
// Disable the window's frame.
//   this->setWindowFlags(Qt::FramelessWindowHint);

    m_pExtKey = NULL;

    //Load button images.
    LoadButtonImages();

    // Setup Signal Mapper
    signalMapper = new QSignalMapper;
    connect(signalMapper, SIGNAL(mapped(const QString&)),
                    this, SIGNAL(keySelected(const QString&)));

    //setup function button.
    setupFuncKey();

    //setup key button.
    setupKeyboardAZ();

    //setup number button.
    setupKeyboard09();

    //Initial parameter.
    m_pSelectKey = NULL;
    m_KeypadFlag = KEYPAD_AZ;
    m_ABCabcFlag = KEYPAD_UPPER_CASE;
    m_SpecWordFlag = KEYPAD_UPPER_CASE;

    setKeypadFlag(KEYPAD_AZ);

    m_pExtTimer = new QTimer(this);
    connect(m_pExtTimer, SIGNAL(timeout()), this, SLOT(EnableExtKey()));
//    m_pExtTimer->start(1000);
}

void RtKeyboard::paintEvent(QPaintEvent*)///* event*/
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, m_ImageBackground);
}

void RtKeyboard::MousePress(int iPressY,int iIndex)
{
    iPressY = 0;

    QPoint keyOffset = QPoint( -10,-60);   
    QRect rectBtnText = QRect(18,16,15,15);
    QString strKey;
    QRect rectPressBtn;

    if(m_KeypadFlag == KEYPAD_AZ)
      rectPressBtn = m_pKeyButton[iIndex]->geometry();
    else if(m_KeypadFlag == KEYPAD_09)
      rectPressBtn = m_pNumberButton[iIndex]->geometry();

    //Delete the Select Key, if it is exist.
    if(m_pSelectKey) {
        delete m_pSelectKey;
        m_pSelectKey = NULL;
    }

    QWidget *parent = (QWidget*)this->parent();
    if(parent == NULL)
        parent = this;

    if(m_KeypadFlag == KEYPAD_AZ)
	{
		strKey = m_pKeyButton[iIndex]->text();
	}
    else if(m_KeypadFlag == KEYPAD_09)
	{
		strKey = m_pNumberButton[iIndex]->text();
	}
    QRect rectKeyboard = this->geometry();
    int iSrcWidth = rectKeyboard.x()+rectPressBtn.x()+keyOffset.x();
    int iSrcHeight = rectKeyboard.y()+rectPressBtn.y()+keyOffset.y();

    m_pSelectKey = new RtKeyButton(parent);
    m_pSelectKey->SetImages(&m_Key1[1],&m_Key1[1]);
    m_pSelectKey->setGeometry(iSrcWidth,iSrcHeight,m_Key1[1].width(),m_Key1[1].height());
    m_pSelectKey->setButtonText(strKey,rectBtnText);
    m_pSelectKey->setAlignStyle(RtKeyButton::AlignCenter);
    m_pSelectKey->setEnabled(false);
    QString strTmp = strKey.toLower();
    QString strChar[]={"a","c","e","i","n","o","s","u","y"};
    m_strExtKey = "";
    bool bExtKey = false;
    for(int i=0;i<9;i++)
    {
        if(strTmp.compare(strChar[i])==0){
            m_strExtKey = strKey;
            bExtKey = true;
            break;
        }
    }

    if(bExtKey){
      m_pSelectKey->setExtKey(bExtKey);
      m_pExtTimer->start(1000);
    }
    m_pSelectKey->show();
}

void RtKeyboard::MouseFuncPress(int iPressY,int iIndex)
{
    iPressY = 0;

    QPoint keyOffset = QPoint(-10,-60);
    QRect rectPressBtn = m_pFuncButton[iIndex]->geometry();
    QString strKey;
    QRect rectBtnText = QRect(18,16,15,15);

    //Delete the Select Key, if it is exist.
    if(m_pSelectKey) {
        delete m_pSelectKey;
        m_pSelectKey = NULL;
    }

    QWidget *parent = (QWidget*)this->parent();
    if(parent == NULL)
        parent = this;

	strKey = m_pFuncButton[iIndex]->text();

    QRect rectKeyboard = this->geometry();
    int iSrcWidth = rectKeyboard.x()+rectPressBtn.x()+keyOffset.x();
    int iSrcHeight = rectKeyboard.y()+rectPressBtn.y()+keyOffset.y();

    m_pSelectKey = new RtKeyButton(parent);

    if(iIndex == __FUN_KEY_0__)
    {
        m_pSelectKey->SetImages(&m_Key4[1],&m_Key4[1]);
        m_pSelectKey->setGeometry(iSrcWidth,iSrcHeight,m_Key4[1].width(),m_Key4[1].height());
    }
    else if(iIndex == __FUN_KEY_1__)//Function Key #1
    {
        m_pSelectKey->SetImages(&m_Key_Switch[1],&m_Key_Switch[1]);
        m_pSelectKey->setGeometry(iSrcWidth,iSrcHeight,m_Key_Switch[1].width(),m_Key_Switch[1].height());
     }
    else if(iIndex == __FUN_KEY_2__)//Function Key #2
    {
        QRect rectFun2Text = QRect(18,16,30,15);
        m_pSelectKey->setButtonText(strKey,rectFun2Text);
        m_pSelectKey->SetImages(&m_Key_Del[1],&m_Key_Del[1]);
        m_pSelectKey->setGeometry(iSrcWidth,iSrcHeight,m_Key_Del[1].width(),m_Key_Del[1].height());
    }
    else if(iIndex == __FUN_KEY_3__)//Function Key #3
    {
        QRect rectFun3Text = QRect(14,16,35,15);
        m_pSelectKey->SetImages(&m_Key7[1],&m_Key7[1]);
        m_pSelectKey->setGeometry(iSrcWidth,iSrcHeight,m_Key7[1].width(),m_Key7[1].height());
        m_pSelectKey->setButtonText(strKey,rectFun3Text);
    }
    else if(iIndex == __FUN_KEY_4__)//Function Key #4
    {
        QRect rectFun4Text = QRect(18,16,30,15);
        m_pSelectKey->SetImages(&m_Key_Enter[1],&m_Key_Enter[1]);
        m_pSelectKey->setGeometry(iSrcWidth,iSrcHeight,m_Key_Enter[1].width(),m_Key_Enter[1].height());
        m_pSelectKey->setButtonText(strKey,rectFun4Text);
    }
    else if(iIndex == __FUN_KEY_5__)//Function Key #5
    {
        m_pSelectKey->SetImages(&m_Key3[1],&m_Key3[1]);
        m_pSelectKey->setGeometry(iSrcWidth,iSrcHeight,m_Key3[1].width(),m_Key3[1].height());
        m_pSelectKey->setButtonText(strKey,rectBtnText);
    }
    else if(iIndex == __FUN_KEY_6__)//Function Key #6
    {
        m_pSelectKey->SetImages(&m_Key3[1],&m_Key3[1]);
        m_pSelectKey->setGeometry(iSrcWidth,iSrcHeight,m_Key3[1].width(),m_Key3[1].height());
        m_pSelectKey->setButtonText(strKey,rectBtnText);
    }

    m_pSelectKey->setAlignStyle(RtKeyButton::AlignCenter);
    m_pSelectKey->setEnabled(false);
    m_pSelectKey->show();
}

void RtKeyboard::MouseRelease()
{
     if(m_pSelectKey) {
        delete m_pSelectKey;
        m_pSelectKey = NULL;
        m_pExtTimer->stop();
    }
}

void RtKeyboard::LoadButtonImages(void)
{
//  Load background image
    m_ImageBackground = QPixmap(g_strKeyboardBK);

// Load Key1 image
    m_Key1[0] = QPixmap(g_strKey1Up);
    m_Key1[1] = QPixmap(g_strKey1Down);

// Load Key2 image
    m_Key2[0] = QPixmap(g_strKey2Up);
    m_Key2[1] = QPixmap(g_strKey2Down);

// Load Key3 image
    m_Key3[0] = QPixmap(g_strKey3Up);
    m_Key3[1] = QPixmap(g_strKey3Down);

// Load Key4 image
    m_Key4[0] = QPixmap(g_strKey4Up);
    m_Key4[1] = QPixmap(g_strKey4Down);

// Load Key5 image
    m_Key5[0] = QPixmap(g_strKey5Up);
    m_Key5[1] = QPixmap(g_strKey5Down);

// Load Key6 image
    m_Key6[0] = QPixmap(g_strKey6Up);
    m_Key6[1] = QPixmap(g_strKey6Down);

// Load Key7 image
    m_Key7[0] = QPixmap(g_strKey7Up);
    m_Key7[1] = QPixmap(g_strKey7Down);

// Load Key Del image
    m_Key_Del[0] = QPixmap(g_strKeyDelUp);
    m_Key_Del[1] = QPixmap(g_strKeyDelDown);

// Load Key Enter image
    m_Key_Enter[0] = QPixmap(g_strKeyEnterUp);
    m_Key_Enter[1] = QPixmap(g_strKeyEnterDown);

// Load Key Switch image
   m_Key_Switch[0] = QPixmap(g_strKeySwitchUp);
   m_Key_Switch[1] = QPixmap(g_strKeySwitchDown);
}

void RtKeyboard::setupFuncKey(void)
{  
    QPoint FuncPoints[__FUN_NUMS__] = {
        QPoint(91,97),QPoint(7,67),QPoint(210,67),QPoint(8,97),QPoint(196,97),
        QPoint(58,97),QPoint(163,97)
    };

    // Func #0 -> Space Key
    QString strSpace = " ";
    QRect rectBtnText = QRect(0,0,0,0);
    m_pFuncButton[__FUN_KEY_0__] = new RtKeyButton(this,__FUN_KEY_0__);
    m_pFuncButton[__FUN_KEY_0__]->SetImages(&m_Key4[0],&m_Key4[0]);
    m_pFuncButton[__FUN_KEY_0__]->setGeometry(FuncPoints[__FUN_KEY_0__].x(),FuncPoints[__FUN_KEY_0__].y(),m_Key4[0].width(),m_Key4[0].height());
    m_pFuncButton[__FUN_KEY_0__]->setButtonText(strSpace,rectBtnText);
    connect(m_pFuncButton[__FUN_KEY_0__], SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(m_pFuncButton[__FUN_KEY_0__], strSpace);

    // Func #1 -> Switch ABC to abc Key
    m_pFuncButton[__FUN_KEY_1__] = new RtKeyButton(this,__FUN_KEY_1__);
    m_pFuncButton[__FUN_KEY_1__]->SetImages(&m_Key_Switch[0],&m_Key_Switch[0]);
    m_pFuncButton[__FUN_KEY_1__]->setGeometry(FuncPoints[__FUN_KEY_1__].x(),FuncPoints[__FUN_KEY_1__].y(),m_Key_Switch[0].width(),m_Key_Switch[0].height());
    connect(m_pFuncButton[__FUN_KEY_1__], SIGNAL(clicked()), this, SLOT(switchUpperLower()));

    // Func #2 -> Delete Key
    m_pFuncButton[__FUN_KEY_2__] = new RtKeyButton(this,__FUN_KEY_2__);
    m_pFuncButton[__FUN_KEY_2__]->SetImages(&m_Key_Del[0],&m_Key_Del[0]);
    m_pFuncButton[__FUN_KEY_2__]->setGeometry(FuncPoints[__FUN_KEY_2__].x(),FuncPoints[__FUN_KEY_2__].y(),m_Key_Del[0].width(),m_Key_Del[0].height());
    connect(m_pFuncButton[__FUN_KEY_2__], SIGNAL(clicked()), this, SIGNAL(backspace()));

    // Func #3 -> Switch between ABC and 123 Key
    QString strFun3 = "?123";
    QRect rectFun3 = QRect(8,6,35,16);

    m_pFuncButton[__FUN_KEY_3__] = new RtKeyButton(this,__FUN_KEY_3__);
    m_pFuncButton[__FUN_KEY_3__]->SetImages(&m_Key7[0],&m_Key7[0]);
    m_pFuncButton[__FUN_KEY_3__]->setGeometry(FuncPoints[__FUN_KEY_3__].x(),FuncPoints[__FUN_KEY_3__].y(),m_Key7[0].width(),m_Key7[0].height());
    m_pFuncButton[__FUN_KEY_3__]->setButtonText(strFun3,rectFun3);
    connect(m_pFuncButton[__FUN_KEY_3__], SIGNAL(clicked()), this, SLOT(switchAZ09()));

    // Func #4 -> Enter Key
    m_pFuncButton[__FUN_KEY_4__] = new RtKeyButton(this,__FUN_KEY_4__);
    m_pFuncButton[__FUN_KEY_4__]->SetImages(&m_Key_Enter[0],&m_Key_Enter[0]);
    m_pFuncButton[__FUN_KEY_4__]->setGeometry(FuncPoints[__FUN_KEY_4__].x(),FuncPoints[__FUN_KEY_4__].y(),m_Key_Enter[0].width(),m_Key_Enter[0].height());

  // Func #5 -> "," Key
    QString strFun5 = ",";
    QRect rectFun5 = QRect(8,6,20,16);

    m_pFuncButton[__FUN_KEY_5__] = new RtKeyButton(this,__FUN_KEY_5__);
    m_pFuncButton[__FUN_KEY_5__]->SetImages(&m_Key3[0],&m_Key3[0]);
    m_pFuncButton[__FUN_KEY_5__]->setGeometry(FuncPoints[__FUN_KEY_5__].x(),FuncPoints[__FUN_KEY_5__].y(),m_Key3[0].width(),m_Key3[0].height());
    m_pFuncButton[__FUN_KEY_5__]->setButtonText(strFun5,rectFun5);
    m_pFuncButton[__FUN_KEY_5__]->show();
    connect(m_pFuncButton[__FUN_KEY_5__], SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(m_pFuncButton[__FUN_KEY_5__], strFun5);

  // Func #6 -> "." Key
    QString strFun6 = ".";
    QRect rectFun6 = QRect(8,6,20,16);

    m_pFuncButton[__FUN_KEY_6__] = new RtKeyButton(this,__FUN_KEY_6__);
    m_pFuncButton[__FUN_KEY_6__]->SetImages(&m_Key3[0],&m_Key3[0]);
    m_pFuncButton[__FUN_KEY_6__]->setGeometry(FuncPoints[__FUN_KEY_6__].x(),FuncPoints[__FUN_KEY_6__].y(),m_Key3[0].width(),m_Key3[0].height());
    m_pFuncButton[__FUN_KEY_6__]->setButtonText(strFun6,rectFun6);
    connect(m_pFuncButton[__FUN_KEY_6__], SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(m_pFuncButton[__FUN_KEY_6__], strFun6);

    for(int i=0;i<__FUN_NUMS__;i++)
    {
        m_pFuncButton[i]->show();
        connect(m_pFuncButton[i], SIGNAL(MousePress(int,int)), this, SLOT(MouseFuncPress(int,int)));
        connect(m_pFuncButton[i], SIGNAL(MouseRelease()), this, SLOT(MouseRelease()));
//        connect(m_pKeyButton[i], SIGNAL(ButtonClick(int)), this, SLOT(ButtonClick(int)));
    }
}

void RtKeyboard::setupKeyboardAZ(void)
{
    QString strKeyText[__AZ_NUMS__] = {
        "Q","W","E","R","T","Y","U","I","O","P",
        "A","S","D","F","G","H","J","K","L",
        "Z","X","C","V","B","N","M"
    };

    QPoint keyPoints[__AZ_NUMS__] = {
        QPoint( 7,  7),QPoint(31, 7),QPoint(55,7),QPoint(79,7),QPoint(103,7),
        QPoint(127, 7),QPoint(151,7),QPoint(175,7),QPoint(199,7),QPoint(223,7),
        QPoint(18,36),QPoint(42,36),QPoint(66,36),QPoint(90,36),QPoint(114,36),
        QPoint(138,36),QPoint(162,36),QPoint(186,36),QPoint(210,36),QPoint(42,67),
        QPoint(66,67),QPoint(90,67),QPoint(114,67),QPoint(138,67),QPoint(162,67),
        QPoint(186,67)
    };
    QRect rectBtnText = QRect(5,8,15,15);

    //Key buttons
    for(int i=0;i<__AZ_NUMS__;i++)
    {
        m_pKeyButton[i] = new RtKeyButton(this,i);
        m_pKeyButton[i]->SetImages(&m_Key1[0],&m_Key1[0]);
        m_pKeyButton[i]->setGeometry(keyPoints[i].x(),keyPoints[i].y(),m_Key1[0].width(),m_Key1[0].height());
        m_pKeyButton[i]->setButtonText(strKeyText[i],rectBtnText);
        connect(m_pKeyButton[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(m_pKeyButton[i], strKeyText[i]);
        m_pKeyButton[i]->show();

        connect(m_pKeyButton[i], SIGNAL(MousePress(int,int)), this, SLOT(MousePress(int,int)));
        connect(m_pKeyButton[i], SIGNAL(MouseRelease()), this, SLOT(MouseRelease()));
        connect(m_pKeyButton[i], SIGNAL(ButtonClick(int)), this, SLOT(ButtonClick(int)));
    }
}

void RtKeyboard::setupKeyboard09(void)
{
    QString strNumerText[__09_NUMS__] = {
        "1","2","3","4","5","6","7","8","9","0",
        "@","#","$","%","&","*","-","+","(",")",
        "!","\x22","'",":",";","/","?"
    };

    QPoint NumberPoints[__09_NUMS__] = {
        QPoint( 7,  7),QPoint(31, 7),QPoint(55,7),QPoint(79,7),QPoint(103,7),
        QPoint(127, 7),QPoint(151,7),QPoint(175,7),QPoint(199,7),QPoint(223,7),
        QPoint( 7,36),QPoint(31,36),QPoint(55,36),QPoint(79,36),QPoint(103,36),
        QPoint(127,36),QPoint(151,36),QPoint(175,36),QPoint(199,36),QPoint(223,36),
        QPoint(42,67),QPoint(66,67),QPoint(90,67),QPoint(114,67),QPoint(138,67),
        QPoint(162,67),QPoint(186,67)};

    QRect rectBtnText = QRect(5,8,15,16);

    //Key buttons
    for(int i=0;i<__09_NUMS__;i++)
    {
        m_pNumberButton[i] = new RtKeyButton(this,i);
        m_pNumberButton[i]->SetImages(&m_Key1[0],&m_Key1[0]);
        m_pNumberButton[i]->setGeometry(NumberPoints[i].x(),NumberPoints[i].y(),m_Key1[0].width(),m_Key1[0].height());
        m_pNumberButton[i]->setAlignStyle(RtKeyButton::AlignCenter);
        m_pNumberButton[i]->setButtonText(strNumerText[i],rectBtnText);
        connect(m_pNumberButton[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(m_pNumberButton[i], strNumerText[i]);

        connect(m_pNumberButton[i], SIGNAL(MousePress(int,int)), this, SLOT(MousePress(int,int)));
        connect(m_pNumberButton[i], SIGNAL(MouseRelease()), this, SLOT(MouseRelease()));
        connect(m_pNumberButton[i], SIGNAL(ButtonClick(int)), this, SLOT(ButtonClick(int)));
    }
}

void RtKeyboard::ButtonClick(int iIndexKey)
{
	iIndexKey++;
 /*
    if(m_KeypadFlag == KEYPAD_AZ)
    {
        if(iIndexKey == __FUN_KEY_3__)
        {
            setKeypadFlag(KEYPAD_09);
        }
    }
    else if(m_KeypadFlag == KEYPAD_09)
    {
        if(iIndexKey == __FUN_NUM_3__)
        {
            setKeypadFlag(KEYPAD_AZ);
        }
    }
*/
}

void RtKeyboard::ShowAZ_Keypad(bool bShow)
{
    if(bShow)
    {
        for(int i=0;i<__AZ_NUMS__;i++)
            m_pKeyButton[i]->show();
    }
    else
    {
        for(int i=0;i<__AZ_NUMS__;i++)
            m_pKeyButton[i]->hide();
    }
}

void RtKeyboard::Show09_Keypad(bool bShow)
{
    if(bShow)
    {
        for(int i=0;i<__09_NUMS__;i++)
            m_pNumberButton[i]->show();
    }
    else
    {
        for(int i=0;i<__09_NUMS__;i++)
            m_pNumberButton[i]->hide();
    }
}

void RtKeyboard::switchUpperLower(void)
{
    if(m_KeypadFlag == KEYPAD_AZ)
        switchABCabc();
    else if(m_KeypadFlag == KEYPAD_09)
        switchSpecialWord();
}

void RtKeyboard::switchABCabc(void)
{
    m_ABCabcFlag = 1-m_ABCabcFlag;

    if(m_ABCabcFlag == KEYPAD_UPPER_CASE)
    {
         QString strUpperKey[__AZ_NUMS__] = {
            "Q","W","E","R","T","Y","U","I","O","P",
            "A","S","D","F","G","H","J","K","L",
            "Z","X","C","V","B","N","M"
        };
        QRect rectBtnText = QRect(5,8,15,15);
        //Key buttons
        for(int i=0;i<__AZ_NUMS__;i++)
        {
           m_pKeyButton[i]->setButtonText(strUpperKey[i],rectBtnText);
           signalMapper->setMapping(m_pKeyButton[i], strUpperKey[i]);
           m_pKeyButton[i]->update();
        }
    }
    else
    {
         QString strLowerKey[__AZ_NUMS__] = {
            "q","w","e","r","t","y","u","i","o","p",
            "a","s","d","f","g","h","j","k","l",
            "z","x","c","v","b","n","m"
        };
        QRect rectBtnText = QRect(5,8,15,15);
        //Key buttons
        for(int i=0;i<__AZ_NUMS__;i++)
        {
           m_pKeyButton[i]->setButtonText(strLowerKey[i],rectBtnText);
           signalMapper->setMapping(m_pKeyButton[i], strLowerKey[i]);
           m_pKeyButton[i]->update();
        }
     }
}

void RtKeyboard::switchSpecialWord(void)
{
    m_SpecWordFlag = 1-m_SpecWordFlag;

    if(m_SpecWordFlag == KEYPAD_UPPER_CASE)
    {
        QString strNumerText[__09_NUMS__] = {
            "1","2","3","4","5","6","7","8","9","0",
            "@","#","$","%","&","*","-","+","(",")",
            "!","\x22","'",":",";","/","?"
        };
        QRect rectBtnText = QRect(5,8,15,16);

        //Key buttons
        for(int i=0;i<__09_NUMS__;i++)
        {
            m_pNumberButton[i]->setButtonText(strNumerText[i],rectBtnText);
            signalMapper->setMapping(m_pNumberButton[i], strNumerText[i]);
            m_pNumberButton[i]->update();
         }
    }
    else
    {
        QString strNumerText[__09_NUMS__] = {
            "~","'","|","\xB7","\xC7","\xA7","\xF7","\xD7","{","}",
            "\xA5","\xA3","\xA2","\xAC","\xB0","^","_","=","[","]",
            "\xBB","\xAE","\xA9","\xB6","\\","<",">"
        };
        QRect rectBtnText = QRect(5,8,15,16);

        //Key buttons
        for(int i=0;i<__09_NUMS__;i++)
        {
            m_pNumberButton[i]->setButtonText(strNumerText[i],rectBtnText);
            signalMapper->setMapping(m_pNumberButton[i], strNumerText[i]);
            m_pNumberButton[i]->update();
         }
    }
}

void RtKeyboard::switchAZ09(void)
{
    m_KeypadFlag = 1-m_KeypadFlag;
    setKeypadFlag(m_KeypadFlag);
}

void RtKeyboard::setKeypadFlag(int iPadFlag)
{
    if(iPadFlag>=KEYPAD_NUMS)
        return;

    m_KeypadFlag = iPadFlag;
    if(m_KeypadFlag == KEYPAD_AZ)
    {
        QString strFun3 = "?123";
        QRect rectFun3 = QRect(4,6,42,16);
        m_pFuncButton[__FUN_KEY_3__]->setButtonText(strFun3,rectFun3);
        m_pFuncButton[__FUN_KEY_3__]->update();

        ShowAZ_Keypad(true);
        Show09_Keypad(false);

    }
    else if(m_KeypadFlag == KEYPAD_09)
    {
        QString strFun3 = "ABC";
        QRect rectFun3 = QRect(4,6,42,16);
        m_pFuncButton[__FUN_KEY_3__]->setButtonText(strFun3,rectFun3);
        m_pFuncButton[__FUN_KEY_3__]->update();

        ShowAZ_Keypad(false);
        Show09_Keypad(true);
    }
}

void RtKeyboard::EnableExtKey(void)
{
    m_pExtTimer->stop();
    signalMapper->blockSignals(true);

     //Delete the Select Key, if it is exist.
    if(m_pSelectKey) {
        delete m_pSelectKey;
        m_pSelectKey = NULL;
    }

    QWidget *parent = (QWidget*)this->parent();
    if(parent == NULL)
        parent = this;

    EnableKeyButton(false);

    if(m_pExtKey){
        delete m_pExtKey;
        m_pExtKey = NULL;
    }

    m_pExtKey = new RtExtKey(parent,m_strExtKey);
    connect(m_pExtKey, SIGNAL(keySelected(const QString&)),
                    this, SIGNAL(keySelected(const QString&)));
    connect(m_pExtKey, SIGNAL(getCancel()),
                    this, SIGNAL(keySelected(const QString&)));
    m_pExtKey->setModal(true);
    m_pExtKey->setEnabled(true);  
    m_pExtKey->exec();

    signalMapper->blockSignals(false);
    EnableKeyButton(true);
	m_pExtKey = NULL;
/*
    //m_strExtKey
    QMessageBox::warning(this, tr("My test"),
                                    tr("Ext button.\n"
                                       "Test Test!!!"),
                                    QMessageBox::Ok ,
                                    QMessageBox::Ok);
*/
}

void RtKeyboard::EnableKeyButton(bool bEnable)
{
   for(int i=0;i<__AZ_NUMS__;i++)
       m_pKeyButton[i]->setEnabled(bEnable);

   for(int j=0;j<__09_NUMS__;j++)
       m_pNumberButton[j]->setEnabled(bEnable);

   for(int k=0;k<__FUN_NUMS__;k++)
       m_pFuncButton[k]->setEnabled(bEnable);
}

void RtKeyboard::CloseExtDlg(void)
{
    if(m_pExtKey)
		m_pExtKey->close();

	m_pExtKey = NULL;
}
