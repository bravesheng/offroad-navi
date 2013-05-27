#include <QPainter>
#include "ANTsportScreen.h"
#include "RtSettingButton.h"
#include "RtGlobalDefine.h"
#include "ImagePool.h"

ANTsportScreen::ANTsportScreen(QWidget *parent)
    : QDialog(parent)//,ReturnBtn(this)
{
    m_pParentDlg = (SettingScreen*)parent;

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
    m_pLabelTitle->setText(g_strTitleANTsport);

// Load quit button
    RtSettingButton *pPushButtonQuit = new RtSettingButton(this);
    pPushButtonQuit->setGeometry( g_rectButtonQuit );
    pPushButtonQuit->SetImages(GetImg(IMG_SETTING_RETURN_UP), GetImg(IMG_SETTING_RETURN_DOWN));
    connect(pPushButtonQuit, SIGNAL(clicked()), this, SLOT(close()));

// Load ListBox
    m_pImageListItem1[BUTTON_UP] = GetImg(IMG_SETTING_LIST_UP);
    m_pImageListItem1[BUTTON_DOWN] = GetImg(IMG_SETTING_LIST_UP);
//    m_pImageListItem1[BUTTON_SEL] = GetImg(IMG_SETTING_LIST_SEL1);

//    m_pImageListItem2[BUTTON_UP] = GetImg(IMG_SETTING_LIST_DOWN);
//    m_pImageListItem2[BUTTON_DOWN] = GetImg(IMG_SETTING_LIST_UP);
//    m_pImageListItem2[BUTTON_SEL] = GetImg(IMG_SETTING_LIST_SEL);

    m_pListBox = new RtSettingList(this, g_rectSetAntListBase.x(), g_rectSetAntListBase.y(),
            g_rectSetAntListBase.width(), g_rectSetAntListBase.height());

    m_pListBox->SetImages1(m_pImageListItem1[BUTTON_UP],m_pImageListItem1[BUTTON_DOWN],
                          m_pImageListItem1[BUTTON_DOWN]);
//    m_pListBox->SetImages2(m_pImageListItem2[BUTTON_DOWN],m_pImageListItem2[BUTTON_UP],
//                          m_pImageListItem2[BUTTON_SEL]);

    connect(m_pListBox, SIGNAL(ButtonSelect(int)), this, SLOT(ListSelect(int)));
    //connect(m_pListBox, SIGNAL(ButtonScroll()), this, SLOT(UListScroll(void)));
    //connect(m_pListBox, SIGNAL(ButtonOnOff(int,int)), this, SLOT(ButtonOnOff(int,int)));


	m_iCandenceEnable = m_pParentDlg->m_Setting.GetCandenceEnable();
	m_iHeartRateEnable = m_pParentDlg->m_Setting.GetHeartRateEnable();

    m_pImageListStatus[0] = GetImg(IMG_SETTING_SWITCH_OFF);
    m_pImageListStatus[1] = GetImg(IMG_SETTING_SWITCH_ON);

    QString strTmp1;
    QString strTmp2 = "";
    strTmp1 = "Enable Candence";
    m_pListBox->AddButton(NULL,strTmp1,strTmp2,m_pImageListStatus[m_iCandenceEnable]);
	m_pListBox->SetIconB_OffsetX(0,230);

    strTmp1 = "Enable Heart Rate";
    m_pListBox->AddButton(NULL,strTmp1,strTmp2,m_pImageListStatus[m_iHeartRateEnable]);
	m_pListBox->SetIconB_OffsetX(1,230);


}

void ANTsportScreen::paintEvent(QPaintEvent*) //event
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
        painter.drawPixmap(0, 0, *m_pImageBackground);
}

void ANTsportScreen::ListSelect(int iSelect)
{
	if(iSelect>=LIST_MAX_NUM)
		return;

	qint8 iTmp = 0;

	if(iSelect == LIST_CANDENCE){
		m_iCandenceEnable = 1-m_iCandenceEnable;
		m_pParentDlg->m_Setting.SetCandenceEnable(m_iCandenceEnable);
		iTmp = m_iCandenceEnable;
	}else if(iSelect == LIST_HEART_RATE){
		m_iHeartRateEnable = 1- m_iHeartRateEnable;
		m_pParentDlg->m_Setting.SetHeartRateEnable(iTmp);
		iTmp = m_iHeartRateEnable;
	}

	m_pListBox->SetIconB(iSelect,m_pImageListStatus[iTmp]);
	m_pParentDlg->m_SettingLog.SetSettingValue(m_pParentDlg->m_Setting);
}

void ANTsportScreen::ButtonOnOff(int iSelect,int iOnOff)//iOnOff - 0->off, 1->on .
{
	if(iSelect>=LIST_MAX_NUM)
		return;

	qint8 iTmp = (qint8)iOnOff;

	if(iSelect == LIST_CANDENCE){
		if(m_iCandenceEnable == iTmp)
			return;
		else
		{
			m_iCandenceEnable = iTmp;
			m_pParentDlg->m_Setting.SetCandenceEnable(iTmp);
		}
	}else if(iSelect == LIST_HEART_RATE){
		if(m_iHeartRateEnable == iTmp)
			return;
		else
		{
			m_iHeartRateEnable = iTmp;
			m_pParentDlg->m_Setting.SetHeartRateEnable(iTmp);
		}
	}

	m_pListBox->SetIconB(iSelect,m_pImageListStatus[iTmp]);
	m_pParentDlg->m_SettingLog.SetSettingValue(m_pParentDlg->m_Setting);
}
