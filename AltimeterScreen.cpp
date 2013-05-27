#include <QPainter>
#include "AltimeterScreen.h"
#include "RtSettingButton.h"
#include "RtGlobalDefine.h"
#include "ImagePool.h"

AltimeterScreen::AltimeterScreen(QWidget *parent)
    : QWidget(parent)//,ReturnBtn(this)
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
    m_pLabelTitle->setText(g_strTitleAltimeter);


    QFont font1(g_strTitleFontFamily, g_iListFontPointSize);
    font1.setStyleStrategy(QFont::PreferAntialias);

// Notes text description.
    qPalette.setColor( QPalette::Foreground, QColor( __TextBlackColor__ ) );
	m_pLabelNotes = new QLabel(this);
    m_pLabelNotes->setFont(font1);
    m_pLabelNotes->setPalette( qPalette );
    m_pLabelNotes->setGeometry(g_rect_Notes);
    m_pLabelNotes->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    m_pLabelNotes->setText(tr("Please select one way to do calibrate!"));

// Load quit button
    RtSettingButton *pPushButtonQuit = new RtSettingButton(this);
    pPushButtonQuit->setGeometry( g_rectButtonQuit );
    pPushButtonQuit->SetImages(GetImg(IMG_SETTING_RETURN_UP), GetImg(IMG_SETTING_RETURN_DOWN));
    connect(pPushButtonQuit, SIGNAL(clicked()), this, SLOT(close()));

// Load ListBox
    m_pImageListItem1[BUTTON_UP] = GetImg(IMG_SETTING_LIST_UP);
    m_pImageListItem1[BUTTON_DOWN] = GetImg(IMG_SETTING_LIST_DOWN);
//    m_pImageListItem1[BUTTON_SEL] = GetImg(IMG_SETTING_LIST_SEL1);

//    m_pImageListItem2[BUTTON_UP] = GetImg(IMG_SETTING_LIST_DOWN);
//    m_pImageListItem2[BUTTON_DOWN] = GetImg(IMG_SETTING_LIST_UP);
//    m_pImageListItem2[BUTTON_SEL] = GetImg(IMG_SETTING_LIST_SEL);

    m_pListBox = new RtSettingList(this, g_rectSetAltListBase.x(), g_rectSetAltListBase.y(),
            g_rectSetAltListBase.width(), g_rectSetAltListBase.height());

    m_pListBox->SetImages1(m_pImageListItem1[BUTTON_UP],m_pImageListItem1[BUTTON_DOWN],
                          m_pImageListItem1[BUTTON_DOWN]);
//    m_pListBox->SetImages2(m_pImageListItem2[BUTTON_DOWN],m_pImageListItem2[BUTTON_UP],
//                          m_pImageListItem2[BUTTON_SEL]);

    connect(m_pListBox, SIGNAL(ButtonSelect(int)), this, SLOT(ListSelect(int)));
    //connect(m_pListBox, SIGNAL(ButtonScroll()), this, SLOT(UListScroll(void)));

    QString strTmp1;
    QString strTmp2 = "";
    strTmp1 = "Barometer";
    m_pListBox->AddButton(NULL,strTmp1,strTmp2,NULL);

    strTmp1 = "Altitude";
    m_pListBox->AddButton(NULL,strTmp1,strTmp2,NULL);

    strTmp1 = "GPS";
    m_pListBox->AddButton(NULL,strTmp1,strTmp2,NULL);

}

void AltimeterScreen::paintEvent(QPaintEvent*) //event
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
	painter.drawPixmap(0, 0, *m_pImageBackground);
}

void AltimeterScreen::ListSelect(int iSelect)
{
	if(iSelect == CALIBRATE_BAROMETER)
	{
	}
	else if(iSelect == CALIBRATE_ALTITUDE)
	{
	}
	else if(iSelect == CALIBRATE_GPS)
	{
	}

}