#include <QPainter>
#include "SysInfoScreen.h"
#include "RtSettingButton.h"
#include "RtGlobalDefine.h"
#include "ImagePool.h"

SysInfoScreen::SysInfoScreen(QWidget *parent)
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
    m_pLabelTitle->setText(g_strTitleSysInfo);

    QFont font1(g_strTitleFontFamily, g_iListFontPointSize);
    font1.setStyleStrategy(QFont::PreferAntialias);

// Load quit button
    RtSettingButton *pPushButtonQuit = new RtSettingButton(this);
    pPushButtonQuit->setGeometry( g_rectButtonQuit );
    pPushButtonQuit->SetImages(GetImg(IMG_SETTING_RETURN_UP), GetImg(IMG_SETTING_RETURN_DOWN));
    connect(pPushButtonQuit, SIGNAL(clicked()), this, SLOT(close()));

    qPalette.setColor( QPalette::Foreground, QColor( __TextBlackColor__ ) );

//Set AP version
    m_pLabelAPver = new QLabel(this);
    m_pLabelAPver->setFont(font1);
    m_pLabelAPver->setPalette( qPalette );
    m_pLabelAPver->setGeometry(g_rectAP_Ver);
    m_pLabelAPver->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    m_pLabelAPver->setText(tr("AP:Alpha1 version"));

//Set OS version
    m_pLabelOSver = new QLabel(this);
    m_pLabelOSver->setFont(font1);
    m_pLabelOSver->setPalette( qPalette );
    m_pLabelOSver->setGeometry(g_rectOS_Ver);
    m_pLabelOSver->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    m_pLabelOSver->setText(tr("OS:vX.X.X.X"));

//Set Boot loader version
    m_pLabelBootver = new QLabel(this);
    m_pLabelBootver->setFont(font1);
    m_pLabelBootver->setPalette( qPalette );
    m_pLabelBootver->setGeometry(g_rectBoot_Ver);
    m_pLabelBootver->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    m_pLabelBootver->setText(tr("Boot Loader:vX.X.X.X"));

//Set Serial Number version
    m_pLabelSerialNumber = new QLabel(this);
    m_pLabelSerialNumber->setFont(font1);
    m_pLabelSerialNumber->setPalette( qPalette );
    m_pLabelSerialNumber->setGeometry(g_rectSN_Ver);
    m_pLabelSerialNumber->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    m_pLabelSerialNumber->setText(tr("SN:123456789012"));

}

void SysInfoScreen::paintEvent(QPaintEvent*)///*event*/
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
	painter.drawPixmap(0, 0, *m_pImageBackground);
}
