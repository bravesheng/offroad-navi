#include <QPainter>
#include <QTimer>
#include "waypointscreen.h"
#include "WEditScreen.h"
#include "RtWaypointButton.h"
#include "ImagePool.h"
#include "RtGPS.h"
#include "QPOIDatabase.h"
#include "QItemInfo.h"
#include "RdGuideEngine.h"

#include "GPXUtility.h"
#include <QDebug>

//#include <QMessageBox>

extern CGuideEngine g_Guide;

WaypointScreen::WaypointScreen(QWidget *parent)
        : QDialog(parent)
{
    setGeometry(0, 0, __nWidth__, __nHeight__);

// Load background image
    m_pImageBackground = GetImg(IMG_LIST_BK);

// Get Unit information.
	m_SettingLog.GetSettingValue(m_Setting);
	int iUnit = m_Setting.GetUnit();

	if(iUnit == 0)
		m_iUnit = CGlobal::UNIT_MILE;
	else if(iUnit == 1)
		m_iUnit = CGlobal::UNIT_KM;
	else
		m_iUnit = CGlobal::UNIT_YARD;
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
    m_pLabelTitle->setText(g_strTitleWaypoint);

// Load quit button
    RtPushButton *pPushButtonQuit = new RtPushButton(this);
    pPushButtonQuit->setGeometry( g_rectButtonQuit );
    m_pImageQuit[BUTTON_UP] = GetImg(IMG_BTN_RETURN);
    m_pImageQuit[BUTTON_DOWN] = GetImg(IMG_BTN_RETURN_DOWN);
    pPushButtonQuit->SetImages(m_pImageQuit[BUTTON_UP], m_pImageQuit[BUTTON_DOWN]);
    connect(pPushButtonQuit, SIGNAL(clicked()), this, SLOT(close()));

// Load Home button
    m_pPushButtonHome = new RtPushButton(this);
    m_pPushButtonHome->setGeometry(g_rectButtonHome);
    m_pImageHome[BUTTON_UP] = GetImg(IMG_BTN_HOME_UP);
    m_pImageHome[BUTTON_DOWN] = GetImg(IMG_BTN_HOME_DOWN);
    m_pPushButtonHome->SetImages(m_pImageHome[BUTTON_UP], m_pImageHome[BUTTON_DOWN]);
    connect(m_pPushButtonHome, SIGNAL(clicked()), this, SLOT(Home()));


// Load View On Map button
    m_pPushButtonView = new RtPushButton(this);
    m_pPushButtonView->setGeometry(g_rectButtonView);
    m_pImageMapView[BUTTON_UP] = GetImg(IMG_BTN_VIEWMAP_UP);
    m_pImageMapView[BUTTON_DOWN] = GetImg(IMG_BTN_VIEWMAP_DOWN);
    m_pPushButtonView->SetImages(m_pImageMapView[BUTTON_UP], m_pImageMapView[BUTTON_DOWN]);
    QString strViewText = QString("View On Map");
    QRect rectViewText = QRect(1,45,63,12);
    m_pPushButtonView->SetButtonText(strViewText,rectViewText);
    connect(m_pPushButtonView, SIGNAL(clicked()), this, SLOT(ViewOnMap()));

// Load Target button
    m_pPushButtonTarget = new RtPushButton(this);
    m_pPushButtonTarget->setGeometry(g_rectButtonTarget);
    m_pImageTarget[BUTTON_UP] = GetImg(IMG_BTN_TARGET_UP);
    m_pImageTarget[BUTTON_DOWN] = GetImg(IMG_BTN_TARGET_DOWN);
    m_pPushButtonTarget->SetImages(m_pImageTarget[BUTTON_UP], m_pImageTarget[BUTTON_DOWN]);
    QString strTargetText = QString("Target");
    QRect rectTargetText = QRect(1,45,63,12);
    m_pPushButtonTarget->SetButtonText(strTargetText,rectTargetText);

    connect(m_pPushButtonTarget, SIGNAL(clicked()), this, SLOT(Target()));

// Load Edit button
    m_pPushButtonEdit = new RtPushButton(this);
    m_pPushButtonEdit->setGeometry(g_rectButtonEdit);
    m_pImageEdit[BUTTON_UP] = GetImg(IMG_BTN_EDIT_UP);
    m_pImageEdit[BUTTON_DOWN] = GetImg(IMG_BTN_EDIT_DOWN);
    m_pPushButtonEdit->SetImages(m_pImageEdit[BUTTON_UP], m_pImageEdit[BUTTON_DOWN]);
    QString strEditText = QString("Edit");
    QRect rectEditText = QRect(1,45,63,12);
    m_pPushButtonEdit->SetButtonText(strEditText,rectEditText);
    connect(m_pPushButtonEdit, SIGNAL(clicked()), this, SLOT(Edit()));

// Load Share button
    m_pPushButtonShare = new RtPushButton(this);
    m_pPushButtonShare->setGeometry(g_rectButtonShare);
    m_pImageShare[BUTTON_UP] = GetImg(IMG_BTN_SHARE_UP);
    m_pImageShare[BUTTON_DOWN] = GetImg(IMG_BTN_SHARE_DOWN);
    m_pPushButtonShare->SetImages(m_pImageShare[BUTTON_UP], m_pImageShare[BUTTON_DOWN]);
    QString strShareText = QString("Share");
    QRect rectShareText = QRect(1,45,63,12);
    m_pPushButtonShare->SetButtonText(strShareText,rectShareText);
    connect(m_pPushButtonShare, SIGNAL(clicked()), this, SLOT(Share()));

// Load ListBox
    m_pListBox = new RtListBox(this, g_rectListBoxBase.x(), g_rectListBoxBase.y(),
            g_rectListBoxBase.width(), g_rectListBoxBase.height());

    connect(m_pListBox, SIGNAL(ButtonSelect(int)), this, SLOT(ListSelect(int)));
    connect(m_pListBox, SIGNAL(ButtonScroll()), this, SLOT(ListScroll(void)));

    m_pImageListItem1[BUTTON_UP] = GetImg(IMG_LIST_ITEM);
    m_pImageListItem1[BUTTON_DOWN] = GetImg(IMG_LIST_ITEM_DOWN);
    m_pImageListItem1[BUTTON_SEL] = GetImg(IMG_LIST_ITEM_SELECTED1);

    m_pImageListItem2[BUTTON_UP] = GetImg(IMG_LIST_ITEM_DOWN);
    m_pImageListItem2[BUTTON_DOWN] = GetImg(IMG_LIST_ITEM);
    m_pImageListItem2[BUTTON_SEL] = GetImg(IMG_LIST_ITEM_SELECTED);

    for(int j=0;j<LIST_ICON_NUM;j++)
        m_pImageIcons[j] = GetImg((IMG_ID)(IMG_WAYPOINT_LIST_ICON1+j));

    m_pImageDirectIcon = GetImg(IMG_WAYPOINT_DIRECT_ICON);

    m_iSelect = -1;

	EnableFunctionButton(false);

//	m_pListThread = new ListThread();
//	connect(m_pListThread, SIGNAL(UpdateListbox()), this, SLOT(UpdateListbox()));
//   m_pListThread->start();

    m_pTestDirect = new QTimer(this);
    connect(m_pTestDirect, SIGNAL(timeout()), this, SLOT(UpdateDirect()));
    m_pTestDirect->start(1000);


	m_pListTimer = new QTimer(this);
	connect(m_pListTimer, SIGNAL(timeout()), this, SLOT(UpdateListbox()));
	m_pListTimer->start(200);

}

void WaypointScreen::paintEvent(QPaintEvent* /*event*/)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPixmap(0, 0, *m_pImageBackground);
}

void WaypointScreen::ViewOnMap()
{
//	GPXUtility m_GPX;
//	QString strPath = QDir::currentPath();
//	strPath+=g_strWayPtDB_Path;

//	m_GPX.WPT2GPX(g_strWayPtDB_Path);
//    m_pTestDirect->start(1000);
}

void WaypointScreen::Target()
{
	QItemInfo m_ItemTarget;
	m_ItemTarget = m_Database.GetPOIItem(m_iSelect);
	m_Database.WriteTarget(&m_ItemTarget);
	g_Guide.SetTarget(&m_ItemTarget);  //-- Set target to guide engine //-- 20090730 Richard.Lin

//    m_pTestDirect->stop();
}

void WaypointScreen::Edit()
{
    if(m_iSelect != -1)
    {
        WEditScreen *pWEditScreen = new WEditScreen;
        pWEditScreen->setModal(true);

        QString strName = "";
        RtWaypointButton *m_pItem = (RtWaypointButton*)m_pListBox->GetButton(m_iSelect);
        strName = m_pItem->getName();
        int iIconIdx =  m_pItem->getSymbolIdx();

        pWEditScreen->setIconIdx(iIconIdx);
        pWEditScreen->setEditText(strName);

        int iRet = pWEditScreen->exec();

        if(iRet == 1)//Save
        {
            QString strModify = "";
            strModify = pWEditScreen->getEditText();
            int iIconModify = pWEditScreen->getIconIdx();
            if(strName.compare(strModify) != 0 || (iIconIdx != iIconModify))
            {
                iIconModify %= LIST_ICON_NUM;
                m_pItem->setSymbol(iIconModify,m_pImageIcons[iIconModify]);
                m_pItem->setName(strModify);
                QItemInfo m_ItemInfo;
                m_ItemInfo = m_Database.GetPOIItem(m_iSelect);
                m_ItemInfo.m_IconId = iIconModify;
                m_ItemInfo.m_Name = strModify;
                m_Database.ModifyPOIItem(m_iSelect,&m_ItemInfo);
                m_Database.SaveDatabase(g_strWayPtDB_Path);

				int iPOImCount = m_Database.GetItemCount();
				GPXUtility mGPX;
				mGPX.WPT2GPX(m_Database, iPOImCount, g_strWayPtDB_Path);
            }
        }
        else if(iRet == 2)//Delete
        {
            m_pListBox->DeleteButton(m_iSelect);
            m_Database.DeleteItem(m_iSelect,false);
            m_Database.SaveDatabase(g_strWayPtDB_Path);
            m_iSelect = -1;
        }
    }

}

void WaypointScreen::Share()
{
}

void WaypointScreen::Home()
{
}

void WaypointScreen::EnableFunctionButton(bool bEnable)
{
    m_pPushButtonView->setEnabled(bEnable);
    m_pPushButtonTarget->setEnabled(bEnable);
    m_pPushButtonEdit->setEnabled(bEnable);
    m_pPushButtonShare->setEnabled(bEnable);
    m_pPushButtonHome->setEnabled(bEnable);
}

void WaypointScreen::ListSelect(int iSelect)
{
    m_iSelect = iSelect;
    EnableFunctionButton(true);
}

void WaypointScreen::ListScroll(void)
{
    m_iSelect = -1;
    EnableFunctionButton(false);
}

void WaypointScreen::UpdateDirect(void)
{
    if(RtGPS_IfFix())
	{
		int iCount = m_pListBox->count();
		RtWaypointButton *pTmpButton;
		double dDistance = 0.0;
		double dCurLon = 0.0;
		double dCurLat = 0.0;
		double dCurEle = 0.0;
		double dAngle = 0.0;
		static int iCnt = 0;

		RtGPS_GetPos(&dCurLon, &dCurLat, &dCurEle);

		for(int i=0;i<iCount;i++)
		{
			pTmpButton = (RtWaypointButton*)m_pListBox->GetButton(i);
			if(pTmpButton)
			{
				QRegion iRegion = pTmpButton->visibleRegion();
				if(!iRegion.isEmpty())
				{
					m_Database.GetDistance(i,dCurLon,dCurLat,m_iUnit,dDistance,dAngle);
					pTmpButton->setDirectAngle(dAngle);
					pTmpButton->setDistance(m_iUnit,dDistance);
				}
			}
		}
	}
}

void WaypointScreen::UpdateListbox(void)
{
   m_pListTimer->stop();

   m_Database.ReadDatabase(g_strWayPtDB_Path);
   m_Database.SortItemArray();

   int iCount = m_Database.GetItemCount();
   QItemInfo m_ItemInfo;

   int iTmp = 0;
   double dDistance = 0.0;
   double dCurLon = 0.0;
   double dCurLat = 0.0;
   double dCurEle = 0.0;
   double dAngle = 0.0;

   bool bGPS_Fix = false;

   if(RtGPS_IfFix())
   {
	   bGPS_Fix = true;
	   RtGPS_GetPos(&dCurLon, &dCurLat, &dCurEle);
   }

   for(int i=0;i<iCount;i++)
   {
        m_ItemInfo = m_Database.GetPOIItem(i);

	  if(bGPS_Fix)
		  m_Database.GetDistance(i,dCurLon,dCurLat,m_iUnit,dDistance,dAngle);

        iTmp = m_ItemInfo.m_IconId;
        iTmp %= LIST_ICON_NUM;

        RtWaypointButton *pWaypointButton = new RtWaypointButton(m_pListBox,i);
        if( i%2 == 0)
            pWaypointButton->SetImages(m_pImageListItem1[BUTTON_UP],m_pImageListItem1[BUTTON_DOWN],m_pImageListItem1[BUTTON_SEL]);
        else
            pWaypointButton->SetImages(m_pImageListItem2[BUTTON_UP],m_pImageListItem2[BUTTON_DOWN],m_pImageListItem2[BUTTON_SEL]);

        pWaypointButton->SetComponent(iTmp,m_pImageIcons[iTmp],m_ItemInfo.m_Name,m_iUnit,dDistance,m_pImageDirectIcon,dAngle);
        m_pListBox->AddButton(pWaypointButton);
		pWaypointButton->show();
		m_pListBox->show();
    }

}

/*
 int ret = QMessageBox::warning(this, tr("My Edit"),
                                tr("Edit button.\n"
                                   "Test Test!!!"),
                                QMessageBox::Save | QMessageBox::Discard
                                | QMessageBox::Cancel,
                                QMessageBox::Save);
*/
