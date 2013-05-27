#include <QPainter>
#include "TrackScreen.h"
#include "TEditScreen.h"
#include "RtTrackButton.h"
#include "ImagePool.h"
#include "Track.h"
#include "GPXUtility.h"
#include "ViewOnMap.h"
#include "TrackList.h"
#include "CurrentTrack.h"

extern CTrackList g_TrackList;

TrackScreen::TrackScreen(QWidget *parent)
:QDialog(parent),
ReturnBtn(this),
m_ListBox(this, g_rectListBoxBase.x(), g_rectListBoxBase.y(), g_rectListBoxBase.width(), g_rectListBoxBase.height())
{
   setGeometry(0, 0, __nWidth__, __nHeight__);

// Load background image
    m_pImageBackground = GetImg(IMG_LIST_BK);

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
    m_pLabelTitle->setText(g_strTitleTrack);

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

// Load Elevation button
    m_pPushButtonElevation = new RtPushButton(this);
    m_pPushButtonElevation->setGeometry(g_rectButtonElevation);
    m_pImageElevation[BUTTON_UP] = GetImg(IMG_BTN_ELEVATION_UP);
    m_pImageElevation[BUTTON_DOWN] = GetImg(IMG_BTN_ELEVATION_DOWN);
    m_pPushButtonElevation->SetImages(m_pImageElevation[BUTTON_UP], m_pImageElevation[BUTTON_DOWN]);
    QString strElevationText = QString("Elev. Plot");
    QRect rectElevationText(1,45,63,12);
    m_pPushButtonElevation->SetButtonText(strElevationText,rectElevationText);
    connect(m_pPushButtonElevation, SIGNAL(clicked()), this, SLOT(Elevation()));

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

    m_iSelect = -1;

// Load ListBox
    connect(&m_ListBox, SIGNAL(ButtonSelect(int)), this, SLOT(ListSelect(int)));
    connect(&m_ListBox, SIGNAL(ButtonScroll()), this, SLOT(ListScroll(void)));

/*
    for(int j=0;j<LIST_ICON_NUM;j++)
        m_pImageIcons[j] = GetImg((IMG_ID)(IMG_TRACK_LIST_ICON1+j));
*/
	EnableFunctionButton(false);

	//delay display content for better user experence
	m_pListTimer = new QTimer(this);
	connect(m_pListTimer, SIGNAL(timeout()), this, SLOT(UpdateListbox()));
	m_pListTimer->start(200);
}

TrackScreen::~TrackScreen()
{

}

void TrackScreen::paintEvent(QPaintEvent*)//event
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPixmap(0, 0, *m_pImageBackground);
}

void TrackScreen::EnableFunctionButton(bool bEnable)
{
    m_pPushButtonView->setEnabled(bEnable);
    m_pPushButtonElevation->setEnabled(bEnable);
    m_pPushButtonEdit->setEnabled(bEnable);
    m_pPushButtonShare->setEnabled(bEnable);
    m_pPushButtonHome->setEnabled(bEnable);
}

void TrackScreen::ListSelect(int iSelect)
{
    m_iSelect = iSelect;
    EnableFunctionButton(true);
}

void TrackScreen::ListScroll(void)
{
    m_iSelect = -1;
    EnableFunctionButton(false);
}

void TrackScreen::ViewOnMap()
{
    if(m_iSelect != -1)
    {
		CTrack* pSelectTrack = g_TrackList.track(m_iSelect);

	    //conture widget
		CViewOnMap* MyViewMap = new CViewOnMap;
		MyViewMap->m_ContouWidget.DrawTrackLog( *pSelectTrack );
		MyViewMap->show();
	}
}

void TrackScreen::Elevation()
{
}

void TrackScreen::Edit()
{
	//Current Track case.
	if(m_iSelect == 0)
	{
		OnEditCurrentTrack();
	}

    if(m_iSelect != -1)
    {
		TEditScreen *pTEditScreen = new TEditScreen(this, g_TrackList.track(m_iSelect));
        pTEditScreen->setModal(true);

        int iRet = pTEditScreen->exec();

        if(iRet == DLG_RETURN_SAVE)//Save
        {
			//m_pListBox->GetButton(m_iSelect)->update();
			//TODO:: Please save modified in pTEditScreen itself.
        }
        else if(iRet == DLG_RETURN_DELETE)//Delete
        {
			//TODO:: Please do delete action in pTEditScreen itself.
        }
    }
}

void TrackScreen::Share()
{
}

void TrackScreen::Home()
{
}

void TrackScreen::UpdateListbox(void)
{
	m_pListTimer->stop();
	g_TrackList.update();
	m_ListBox.DeleteAllButton();

	RtTrackButton* pTrackButton;
	//add tracks
	for(int i=0; i < g_TrackList.count(); i++)
    {
        pTrackButton = new RtTrackButton(&m_ListBox);
		pTrackButton->show();
        m_ListBox.AddButton(pTrackButton);
    }
}

void TrackScreen::OnEditCurrentTrack()
{
	TEditScreen *pTEditScreen = new TEditScreen(this, g_TrackList.currentTrack(),TEditScreen::BTN_TYPE_SAVE_ONLY);
    pTEditScreen->setModal(true);
    int iRet = pTEditScreen->exec();

    if(iRet == DLG_RETURN_SAVE)//Save
	{
		UpdateListbox();
    }
}