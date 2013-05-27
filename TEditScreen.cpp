#include <QPainter>
#include <QTimer>
#include <QMessageBox>
#include "TEditScreen.h"
#include "ImagePool.h"
#include "Track.h"


TEditScreen::TEditScreen(QWidget *parent, CTrack* pTrack,int iBtnType)
:QDialog(parent),
m_pTrack(pTrack),
ReturnBtn(this)
{
    setGeometry(0, 0, __nWidth__, __nHeight__);
	m_iBtnType = iBtnType;

// Load background image
    m_pImageBackground = GetImg(IMG_EDIT_BK);
	m_pImageIcon[BUTTON_UP] = GetImg(IMG_EDIT_ICON_UP);
	m_pImageIcon[BUTTON_DOWN] = GetImg(IMG_EDIT_ICON_DOWN);

	for(int l=0;l<__ICON_NUMS__;l++)
	{
		m_pImageBtnUp[l] = GetImg((IMG_ID)(IMG_TRACK_ICON_C1+l));
	}

	m_pImageBtnDown = GetImg(IMG_TRACK_ICON_BACK);

// Set Title Text
    m_pLabelTitle = new QLabel(this);
    QFont font(g_strTitleFontFamily, g_iTitleFontPointSize);
    font.setStyleStrategy(QFont::PreferAntialias);
    m_pLabelTitle->setFont(font);
    QPalette qPalette;
    qPalette.setColor( QPalette::Foreground, QColor( __TitleTextColor__ ) );
    m_pLabelTitle->setPalette( qPalette );
    m_pLabelTitle->setGeometry(g_rectEditTitle);
    m_pLabelTitle->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    m_pLabelTitle->setText(g_strTitleEdit);

    m_iSelect = 0;
// Load Select Icon
    m_pPushButtonIcon = new RtPushButton(this);
    m_pPushButtonIcon->setGeometry(g_rectButtonIcon);
    PrepareMainIconImage(m_ImageSymbol[BUTTON_UP], m_ImageSymbol[BUTTON_DOWN], m_iSelect);
    m_pPushButtonIcon->SetImages(&m_ImageSymbol[BUTTON_UP], &m_ImageSymbol[BUTTON_DOWN], &m_ImageSymbol[BUTTON_DOWN]);
    m_pPushButtonIcon->setCheckable(true);
    connect(m_pPushButtonIcon, SIGNAL(clicked()), this, SLOT(IconClicked()));

// Load Name button
    m_pPushButtonName = new RtEditButton(this);
    m_pPushButtonName->setGeometry(g_rectButtonName);
    m_pImageName[BUTTON_UP] = GetImg(IMG_EDIT_NAME_UP);
    m_pImageName[BUTTON_DOWN] = GetImg(IMG_EDIT_NAME_DOWN);
    m_pPushButtonName->SetImages(m_pImageName[BUTTON_UP], m_pImageName[BUTTON_DOWN], m_pImageName[BUTTON_DOWN]);
    m_pPushButtonName->setCheckable(true);
    connect(m_pPushButtonName, SIGNAL(clicked()), this, SLOT(NameClicked()));
   //m_pPushButtonName->setEnabled(false);

// Load Icon buttons
    for (int i=0; i<__ICON_NUMS__; i++)
    {
        m_pButtonIcons[i] = new RtPushButton(this);
        m_pButtonIcons[i]->setGeometry(g_rectTrackBtnIconClr[i]);
        PrepareIconImage(m_ImageIcons[BUTTON_UP][i], m_ImageIcons[BUTTON_DOWN][i], i);
        m_pButtonIcons[i]->SetImages(&m_ImageIcons[BUTTON_UP][i], &m_ImageIcons[BUTTON_DOWN][i]);
        connect(m_pButtonIcons[i], SIGNAL(ButtonClick(int)), this, SLOT(ButtonClick(int)));
    }

// Load Save button
    m_pPushButtonSave = new RtPushButton(this);
    m_pPushButtonSave->setGeometry(g_rectEditButtonSave);
    m_pImageSave[BUTTON_UP] = GetImg(IMG_EDIT_SAVE_UP);
    m_pImageSave[BUTTON_DOWN] = GetImg(IMG_EDIT_SAVE_DOWN);
    m_pPushButtonSave->SetImages(m_pImageSave[BUTTON_UP], m_pImageSave[BUTTON_DOWN]);
    QString strSaveText = QString("Save");
    QRect rectSaveText = QRect(1,45,63,12);
    m_pPushButtonSave->SetButtonText(strSaveText,rectSaveText);
    connect(m_pPushButtonSave, SIGNAL(clicked()), this, SLOT(OnSave()));

	if(m_iBtnType == BTN_TYPE_SAVE_DEL)
	{
	// Load Delete button
		m_pPushButtonDelete = new RtPushButton(this);
		m_pPushButtonDelete->setGeometry(g_rectEditButtonDel);
		m_pImageDelete[BUTTON_UP] = GetImg(IMG_EDIT_DELETE_UP);
		m_pImageDelete[BUTTON_DOWN] = GetImg(IMG_EDIT_DELETE_DOWN);
		m_pPushButtonDelete->SetImages(m_pImageDelete[BUTTON_UP], m_pImageDelete[BUTTON_DOWN]);
		QString strDelText = QString("Delete");
		QRect rectDelText = QRect(1,45,63,12);
		m_pPushButtonDelete->SetButtonText(strDelText,rectDelText);
		connect(m_pPushButtonDelete, SIGNAL(clicked()), this, SLOT(OnDelete()));
	}

	if(m_iBtnType == BTN_TYPE_SAVE_ONLY)
	{
	  // Load Cancel button
		m_pPushButtonCancel = new RtPushButton(this);
		m_pPushButtonCancel->setGeometry(g_rectEditButtonDel);
		m_ImageCancel[BUTTON_UP] = QPixmap(g_strEditButtonDelUp);
		m_ImageCancel[BUTTON_DOWN] = QPixmap(g_strEditButtonDelDown);
		m_pPushButtonCancel->SetImages(&m_ImageCancel[BUTTON_UP], &m_ImageCancel[BUTTON_DOWN]);
		QString strDelText = QString("Cancel");
		QRect rectDelText = QRect(1,45,63,12);
		m_pPushButtonCancel->SetButtonText(strDelText,rectDelText);
		connect(m_pPushButtonCancel, SIGNAL(clicked()), this, SLOT(OnCancel()));
	}

    m_pKeyboard = NULL;
    m_pKeyboard = new RtKeyboard(this);
    m_pKeyboard->setGeometry(g_rectKeyboard);
    m_pKeyboard->hide();
    connect(m_pKeyboard, SIGNAL(keySelected(const QString&)),
                        this, SLOT(keySelected(const QString&)));
    connect(m_pKeyboard, SIGNAL(backspace(void)),
                        this, SLOT(backspace(void)));
    connect(m_pKeyboard, SIGNAL(switchKeypad(void)),
                        this, SLOT(switchKeypad(void)));

    m_pButtonSelected = NULL;

	if(m_iBtnType == BTN_TYPE_SAVE_ONLY)
		NameClicked();
	else
		IconClicked();

    m_pQTimerEffect = new QTimer(this);
    connect(m_pQTimerEffect, SIGNAL(timeout()), this, SLOT(DoEffect()));
}

TEditScreen::~TEditScreen()
{
    if(m_pKeyboard)
    {
        delete m_pKeyboard;
        m_pKeyboard = NULL;
    }
}

void TEditScreen::PrepareParametersIntoWidget(void)
{
	//track name
	m_pPushButtonName->setEditText(m_pTrack->name());
	//track color
}

void TEditScreen::paintEvent(QPaintEvent*)//event
{
        QPainter painter(this);
        painter.drawPixmap(0,0,*m_pImageBackground);
}

void TEditScreen::PrepareMainIconImage(QPixmap &imageUp, QPixmap &imageDown, int iNo)
{
    if(!imageUp.isNull())
        imageUp.detach();

    if(!imageDown.isNull())
        imageDown.detach();

    imageUp = QPixmap(*m_pImageIcon[BUTTON_UP]);
    imageDown = QPixmap(*m_pImageIcon[BUTTON_DOWN]);
    QPixmap imageTmp(*m_pImageBtnUp[iNo]);

    QPainter painterTmp;
    QRect rect = imageUp.rect();
    painterTmp.begin(&imageUp);
    painterTmp.drawPixmap( rect, imageTmp );
    painterTmp.end();
    rect = imageDown.rect();
    painterTmp.begin(&imageDown);
    painterTmp.drawPixmap( rect, imageTmp );
    painterTmp.end();
}

void TEditScreen::PrepareIconImage(QPixmap &imageUp, QPixmap &imageDown, int iNo)
{
   if(!imageUp.isNull())
        imageUp.detach();

    if(!imageDown.isNull())
        imageDown.detach();

    imageUp = QPixmap(*m_pImageBtnUp[iNo]);
    imageDown = QPixmap(*m_pImageBtnDown);

    QPainter painterTmp;
    painterTmp.begin(&imageDown);
    painterTmp.drawPixmap( 0, 0, imageUp );
    painterTmp.end();
}

void TEditScreen::IconClicked()
{
   m_pKeyboard->CloseExtDlg();
   m_pPushButtonIcon->setChecked(true);

    for(int i=0;i<__ICON_NUMS__;i++)
        m_pButtonIcons[i]->show();

    m_pPushButtonName->setChecked(false);
    m_pKeyboard->hide();
    m_pPushButtonName->setEditEnabled(false);
}

void TEditScreen::NameClicked()
{
    m_pKeyboard->CloseExtDlg();
    m_pPushButtonIcon->setChecked(false);

     for(int i=0;i<__ICON_NUMS__;i++)
        m_pButtonIcons[i]->hide();

    m_pPushButtonName->setChecked(true);
    m_pKeyboard->show();
    m_pPushButtonName->setEditEnabled(true);
}

void TEditScreen::ButtonClick(int iSelect)
{
//    QImage imageUp, imageDown;
    m_iSelect = iSelect;

    if (m_pButtonSelected!=NULL) delete m_pButtonSelected;
    m_pButtonSelected = new RtPushButton(this);
    m_pButtonSelected->setGeometry(g_rectTrackBtnIconClr[iSelect]);
//    PrepareIconImage(imageUp, imageDown, iSelect);
    m_pButtonSelected->SetImages(&m_ImageIcons[BUTTON_DOWN][iSelect]);
    m_pButtonSelected->show();
    m_pButtonSelected->setEnabled(false);

    m_pQTimerEffect->start(20);
}

void TEditScreen::DoEffect()
{
#define __MOVE_INTERVAL__ 5
        int iTargetX = g_rectButtonIcon.x() + g_rectButtonIcon.width()/2;
        int iTargetY = g_rectButtonIcon.y() + g_rectButtonIcon.height()/2;
        QRect rect = m_pButtonSelected->frameGeometry();
        int iStartX = rect.x()+rect.width()/2;
        int iStartY = rect.y()+rect.height()/2;
        int iDiff = iTargetX - iStartX;
        int iDiffAbs = abs(iDiff);
        int iShift = (iDiffAbs>__MOVE_INTERVAL__)? (iDiff/iDiffAbs)*__MOVE_INTERVAL__: iDiff;

        if ( iShift == 0 )
        {
                iDiff = iTargetY - iStartY;
                iDiffAbs = abs(iDiff);
                iShift = (iDiffAbs>__MOVE_INTERVAL__)? (iDiff/iDiffAbs)*__MOVE_INTERVAL__: iDiff;
                if ( iShift == 0 )
                {
                        delete m_pButtonSelected;
                        m_pButtonSelected = NULL;
                        PrepareMainIconImage(m_ImageSymbol[BUTTON_UP], m_ImageSymbol[BUTTON_DOWN], m_iSelect);
                        m_pPushButtonIcon->SetImages(&m_ImageSymbol[BUTTON_UP], &m_ImageSymbol[BUTTON_DOWN], &m_ImageSymbol[BUTTON_DOWN]);
                        m_pQTimerEffect->stop();
                }
                else
                {
                        rect.moveTop(rect.y() + iShift);
                        m_pButtonSelected->setGeometry(rect);
                }
        }
        else
        {
                rect.moveLeft(rect.x() + iShift);
                m_pButtonSelected->setGeometry(rect);
        }
}

void TEditScreen::OnSave()
{
	this->done(DLG_RETURN_SAVE);
}

void TEditScreen::OnDelete()
{
   this->done(DLG_RETURN_DELETE);
}

void TEditScreen::OnCancel()
{
    this->done(DLG_RETURN_CANCEL);
}

void TEditScreen::keySelected (const QString& key)
{
    m_pPushButtonName->insertText(key);
	CheckWhiteSpace();
}

void TEditScreen::backspace(void)
{
    m_pPushButtonName->backspace();
	CheckWhiteSpace();
}

void TEditScreen::switchKeypad(void)
{
    m_pPushButtonName->setEditFocus();
}
QString TEditScreen::getEditText(void)
{
    return m_pPushButtonName->getEditText();
}

void TEditScreen::setEditText(QString& strText)
{
    m_pPushButtonName->setEditText(strText);

	CheckWhiteSpace();
}

void TEditScreen::setIconIdx(int iIconIdx)
{
    m_iSelect = iIconIdx;
    PrepareMainIconImage(m_ImageSymbol[BUTTON_UP], m_ImageSymbol[BUTTON_DOWN], m_iSelect);
    m_pPushButtonIcon->SetImages(&m_ImageSymbol[BUTTON_UP], &m_ImageSymbol[BUTTON_DOWN], &m_ImageSymbol[BUTTON_DOWN]);
}

bool TEditScreen::CheckWhiteSpace(void)
{
	bool ret = false;

	QString strTmp = "";
	strTmp = getEditText();
	strTmp = strTmp.trimmed();

	if(!strTmp.isEmpty())
	{
		m_pPushButtonSave->setEnabled(true);
	}
	else
	{
		m_pPushButtonSave->setEnabled(false);
		ret = true;
	}

	return ret;
}
