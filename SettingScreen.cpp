#include <QPainter>
#include "SettingScreen.h"
#include "RtSettingButton.h"
#include "RtGlobalDefine.h"
#include "UnitsScreen.h"
#include "AltimeterScreen.h"
#include "SysInfoScreen.h"
#include "ImagePool.h"
#include "ANTsportScreen.h"

SettingScreen::SettingScreen(QWidget *parent)
    : QDialog(parent)//,ReturnBtn(this)
{
    setGeometry(0, 0, __nWidth__, __nHeight__);

// Load background image
    m_pImageBackground = GetImg(IMG_SETTING_BK);

// Set Title Text
    m_pLabelTitle = new QLabel(this);
    QFont font(g_strTitleFontFamily, g_iTitleFontPointSize);
    font.setStyleStrategy(QFont::PreferAntialias);
    m_pLabelTitle->setFont(font);
    QPalette qPalette;
    qPalette.setColor( QPalette::Foreground, QColor( __TitleTextColor__ ) );
    m_pLabelTitle->setPalette( qPalette );
    m_pLabelTitle->setGeometry(g_rectTitle);
    m_pLabelTitle->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    m_pLabelTitle->setText(g_strTitleSettings);

// Load quit button
    RtSettingButton *pPushButtonQuit = new RtSettingButton(this);
    pPushButtonQuit->setGeometry( g_rectButtonQuit );
    pPushButtonQuit->SetImages(GetImg(IMG_SETTING_RETURN_UP), GetImg(IMG_SETTING_RETURN_DOWN));
    connect(pPushButtonQuit, SIGNAL(clicked()), this, SLOT(close()));

// Load ListBox
    m_pImageListItem1[BUTTON_UP] = GetImg(IMG_SETTING_LIST_UP);
    m_pImageListItem1[BUTTON_DOWN] = GetImg(IMG_SETTING_LIST_DOWN);
    m_pImageListItem1[BUTTON_SEL] = GetImg(IMG_SETTING_LIST_DOWN);

 //   m_pImageListItem2[BUTTON_UP] = GetImg(IMG_SETTING_LIST_DOWN);
 //   m_pImageListItem2[BUTTON_DOWN] = GetImg(IMG_SETTING_LIST_UP);
 //   m_pImageListItem2[BUTTON_SEL] = GetImg(IMG_SETTING_LIST_SEL);

 //   m_pListIcon[0] = GetImg(IMG_SETTING_LIST_ICON1);
 //   m_pListIcon[1] = GetImg(IMG_SETTING_LIST_ICON2);
 //   m_pListIcon[2] = GetImg(IMG_SETTING_LIST_ICON3);
 //   m_pListIcon[3] = GetImg(IMG_SETTING_LIST_ICON4);

 //   m_pImageListStatus[0] = GetImg(IMG_SETTING_SELECT_ICON);
 //   m_pImageListStatus[1] = GetImg(IMG_SETTING_UNSELECT_ICON);
 //   m_pImageListStatus[2] = GetImg(IMG_SETTING_NEXT_ICON);

    m_pListBox = new RtSettingList(this, g_rectSetListBase.x(), g_rectSetListBase.y(),
            g_rectSetListBase.width(), g_rectSetListBase.height());

    m_pListBox->SetImages1(m_pImageListItem1[BUTTON_UP],m_pImageListItem1[BUTTON_DOWN],
                          m_pImageListItem1[BUTTON_SEL]);
 //   m_pListBox->SetImages2(m_pImageListItem2[BUTTON_DOWN],m_pImageListItem2[BUTTON_UP],
 //                         m_pImageListItem2[BUTTON_SEL]);

    connect(m_pListBox, SIGNAL(ButtonSelect(int)), this, SLOT(SListSelect(int)));
    connect(m_pListBox, SIGNAL(ButtonScroll()), this, SLOT(SListScroll(void)));

    m_iSelect = 0;
	m_SettingLog.GetSettingValue(m_Setting);
	m_iUnit = m_Setting.GetUnit();

    QString strTmp1;
    QString strTmp2 = "";
    QString strIconPath;
    QString strUnit[3]={" - Statute"," - Metric"," - Yards"};

//    int iTmp = 0;
    strTmp1 = "Unit";
	if((m_iUnit>=0)&&(m_iUnit<CSetting::UNIT_MAX_NUM))
		strTmp1 += strUnit[m_iUnit];

    m_pListBox->AddButton(NULL,strTmp1,strTmp2,NULL);

    strTmp1 = "Altimeter Calibration";
    m_pListBox->AddButton(NULL,strTmp1,strTmp2,NULL);

    strTmp1 = "ANT+Sport";
    m_pListBox->AddButton(NULL,strTmp1,strTmp2,NULL);

    strTmp1 = "About";
    m_pListBox->AddButton(NULL,strTmp1,strTmp2,NULL);

/*
    m_pListBox->AddButton(m_pListIcon[0],strTmp1,strTmp2,m_pImageListStatus[2]);

    strTmp1 = "Altimeter Calibration";
    m_pListBox->AddButton(m_pListIcon[1],strTmp1,strTmp2,m_pImageListStatus[2]);

    strTmp1 = "ANT+Sport";
    m_pListBox->AddButton(m_pListIcon[2],strTmp1,strTmp2,m_pImageListStatus[2]);

    strTmp1 = "About";
    m_pListBox->AddButton(m_pListIcon[3],strTmp1,strTmp2,m_pImageListStatus[2]);
*/
}

SettingScreen::~SettingScreen()
{

}

void SettingScreen::paintEvent(QPaintEvent*)//event
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPixmap(0, 0, *m_pImageBackground);
}

void SettingScreen::SListSelect(int iSelect)
{
    m_iSelect = iSelect;

    switch(m_iSelect)
    {
    case SYS_ID_UNIT:
        OnUnitScreen();
        break;
    case SYS_ID_ALTIMETER:
        OnAltimeterScreen();
        break;
	case SYS_ID_ANT_SPORT:
		OnAntSport();
		break;
    case SYS_ID_ABOUT:
        OnAboutScreen();
        break;
    }
}

void SettingScreen::SListScroll(void)
{
}

void SettingScreen::OnUnitScreen(void)
{
    UnitsScreen *pUnitScreen = new UnitsScreen(this,m_iUnit);
    pUnitScreen->setModal(true);

    pUnitScreen->exec();

	m_iUnit = pUnitScreen->getSelect();

	
    QString strUnit[3]={" - Statute"," - Metric"," - Yards"};
    QString strTmp1 = "Unit";
	if((m_iUnit>=0)&&(m_iUnit<CSetting::UNIT_MAX_NUM))
		strTmp1 += strUnit[m_iUnit];

	RtSettingButton* pSettingBtn = m_pListBox->GetButton(0);
	pSettingBtn->SetText1(strTmp1);
}

void SettingScreen::OnAltimeterScreen(void)
{
    AltimeterScreen *pAltimeterScreen = new AltimeterScreen(this);
    pAltimeterScreen->show();
}

void SettingScreen::OnAntSport(void)
{
    ANTsportScreen  *pAntSportScreen = new ANTsportScreen(this);
    pAntSportScreen->show();
}

void SettingScreen::OnAboutScreen(void)
{
    SysInfoScreen *pAboutScreen = new SysInfoScreen(this);
    pAboutScreen->show();
}
