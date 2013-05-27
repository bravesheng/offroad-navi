#include <QPainter>
#include "UnitsScreen.h"
#include "RtSettingButton.h"
#include "RtGlobalDefine.h"
//#include <QMessageBox>
#include "ImagePool.h"

UnitsScreen::UnitsScreen(QWidget *parent,int iSelect)
    : QDialog(parent)//,ReturnBtn(this)
{
	m_iSelect = iSelect;

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
    m_pLabelTitle->setGeometry(g_rectSettingTitle);
    m_pLabelTitle->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    m_pLabelTitle->setText(g_strTitleUnits);

// Load quit button
    RtSettingButton *pPushButtonQuit = new RtSettingButton(this);
    pPushButtonQuit->setGeometry( g_rectButtonQuit );
    pPushButtonQuit->SetImages(GetImg(IMG_SETTING_RETURN_UP), GetImg(IMG_SETTING_RETURN_DOWN));
    connect(pPushButtonQuit, SIGNAL(clicked()), this, SLOT(close()));

// Load ListBox
    m_pImageListItem1[BUTTON_UP] = GetImg(IMG_SETTING_LIST_UP);
    m_pImageListItem1[BUTTON_DOWN] = GetImg(IMG_SETTING_LIST_DOWN);
//    m_pImageListItem1[BUTTON_SEL] = GetImg(IMG_SETTING_LIST_SEL1);

 //   m_pImageListItem2[BUTTON_UP] = GetImg(IMG_SETTING_LIST_DOWN);
 //   m_pImageListItem2[BUTTON_DOWN] = GetImg(IMG_SETTING_LIST_UP);
 //   m_pImageListItem2[BUTTON_SEL] = GetImg(IMG_SETTING_LIST_SEL);

    m_pListBox = new RtSettingList(this, g_rectSetListBase.x(), g_rectSetListBase.y(),
            g_rectSetListBase.width(), g_rectSetListBase.height());

    m_pListBox->SetImages1(m_pImageListItem1[BUTTON_UP],m_pImageListItem1[BUTTON_DOWN],m_pImageListItem1[BUTTON_DOWN]);
//    m_pListBox->SetImages2(m_pImageListItem2[BUTTON_DOWN],m_pImageListItem2[BUTTON_UP],m_pImageListItem2[BUTTON_SEL]);

    connect(m_pListBox, SIGNAL(ButtonSelect(int)), this, SLOT(UListSelect(int)));
    connect(m_pListBox, SIGNAL(ButtonScroll()), this, SLOT(UListScroll(void)));

 //   m_pImageListStatus[0] = GetImg(IMG_SETTING_SELECT_ICON);
 //   m_pImageListStatus[1] = GetImg(IMG_SETTING_UNSELECT_ICON);
 //   m_pImageListStatus[2] = GetImg(IMG_SETTING_NEXT_ICON);

    int iStatus[3];
    for(int i=0;i<3;i++)
    {
        if(m_iSelect == i)
            iStatus[i] = 0;
        else
            iStatus[i] = 1;
    }

    QString strTmp1;
    QString strTmp2 = "";

    strTmp1 = "Statute";
    m_pListBox->AddButton(NULL,strTmp1,strTmp2,NULL);

    strTmp1 = "Metric";
    m_pListBox->AddButton(NULL,strTmp1,strTmp2,NULL);

    strTmp1 = "Yards";
    m_pListBox->AddButton(NULL,strTmp1,strTmp2,NULL);

    m_pListBox->ListButtonClick(m_iSelect);
/*
    strTmp1 = "Statute";
    m_pListBox->AddButton(NULL,strTmp1,strTmp2,m_pImageListStatus[iStatus[0]]);

    strTmp1 = "Metric";
    m_pListBox->AddButton(NULL,strTmp1,strTmp2,m_pImageListStatus[iStatus[1]]);

    strTmp1 = "Yards";
    m_pListBox->AddButton(NULL,strTmp1,strTmp2,m_pImageListStatus[iStatus[2]]);

    m_pListBox->ListButtonClick(m_iSelect);
*/
}

void UnitsScreen::paintEvent(QPaintEvent*)//event
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
	painter.drawPixmap(0, 0, *m_pImageBackground);
}

void UnitsScreen::UListSelect(int iSelect)
{
   if(m_iSelect != iSelect)
   {
	   m_iSelect = iSelect;
	   m_pParentDlg->m_Setting.SetUnit(m_iSelect);
	   m_pParentDlg->m_SettingLog.SetSettingValue(m_pParentDlg->m_Setting);

/*
      m_pListBox->SetIconB(m_iSelect,m_pImageListStatus[1]);
	  m_iSelect = iSelect;
      m_pListBox->SetIconB(m_iSelect,m_pImageListStatus[0]);
*/
  }
}

void UnitsScreen::UListScroll(void)
{
}

void UnitsScreen::setSelect(int iSelect)
{
    m_iSelect = iSelect;
}

/*
     int ret = QMessageBox::warning(this, tr("My Edit"),
                                    tr("Edit button.\n"
                                       "Test Test!!!"),
                                    QMessageBox::Save | QMessageBox::Discard
                                    | QMessageBox::Cancel,
                                    QMessageBox::Save);

*/
