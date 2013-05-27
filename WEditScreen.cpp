#include <QPainter>
#include "WEditScreen.h"
#include "ImagePool.h"
#include <QMessageBox>

WEditScreen::WEditScreen(QWidget *parent,int iBtnType)
        : QDialog(parent),ReturnBtn(this)
{
    setGeometry(0, 0, __nWidth__, __nHeight__);

	m_iBtnType = iBtnType;

// Load background image
    m_pImageBackground = GetImg(IMG_EDIT_BK);

	//standard symbol icon
	m_pImageIcon[BUTTON_UP] = GetImg(IMG_EDIT_ICON_UP);
	m_pImageIcon[BUTTON_DOWN] = GetImg(IMG_EDIT_ICON_DOWN);

	//select waypoint icon
	for(int l=0;l<__ICON_NUMS__;l++)
	{
		m_pImageBtnUp[l] = GetImg((IMG_ID)(IMG_WAYPOINT_ICON_C1+l));
	}

	m_pImageBtnDown = GetImg(IMG_WAYPOINT_ICON_BACK);

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
    m_ImageName[BUTTON_UP] = QPixmap(g_strButtonNameUp);
    m_ImageName[BUTTON_DOWN] = QPixmap(g_strButtonNameDown);
    m_pPushButtonName->SetImages(&m_ImageName[BUTTON_UP], &m_ImageName[BUTTON_DOWN], &m_ImageName[BUTTON_DOWN]);
    m_pPushButtonName->setCheckable(true);
    connect(m_pPushButtonName, SIGNAL(clicked()), this, SLOT(NameClicked()));
   //m_pPushButtonName->setEnabled(false);

// Load Icon buttons
    for (int i=0; i<__ICON_NUMS__; i++)
    {
        m_pButtonIcons[i] = new RtPushButton(this);
        m_pButtonIcons[i]->setGeometry(g_rectWayPtBtnIconClr[i]);
        PrepareIconImage(m_ImageIcons[BUTTON_UP][i], m_ImageIcons[BUTTON_DOWN][i], i);
        m_pButtonIcons[i]->SetImages(&m_ImageIcons[BUTTON_UP][i], &m_ImageIcons[BUTTON_DOWN][i]);
        connect(m_pButtonIcons[i], SIGNAL(ButtonClick(int)), this, SLOT(ButtonClick(int)));
    }

// Load Save button
    m_pPushButtonSave = new RtPushButton(this);
    m_pPushButtonSave->setGeometry(g_rectEditButtonSave);
    m_ImageSave[BUTTON_UP] = QPixmap(g_strEditButtonSaveUp);
    m_ImageSave[BUTTON_DOWN] = QPixmap(g_strEditButtonSaveDown);
    m_pPushButtonSave->SetImages(&m_ImageSave[BUTTON_UP], &m_ImageSave[BUTTON_DOWN]);
    QString strSaveText = QString("Save");
    QRect rectSaveText = QRect(1,45,63,12);
    m_pPushButtonSave->SetButtonText(strSaveText,rectSaveText);
    connect(m_pPushButtonSave, SIGNAL(clicked()), this, SLOT(OnSave()));

	if(m_iBtnType == BTN_TYPE_SAVE_DEL)
	{
	  // Load Delete button
		m_pPushButtonDelete = new RtPushButton(this);
		m_pPushButtonDelete->setGeometry(g_rectEditButtonDel);
		m_ImageDelete[BUTTON_UP] = QPixmap(g_strEditButtonDelUp);
		m_ImageDelete[BUTTON_DOWN] = QPixmap(g_strEditButtonDelDown);
		m_pPushButtonDelete->SetImages(&m_ImageDelete[BUTTON_UP], &m_ImageDelete[BUTTON_DOWN]);
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

/*
    timeLine = new QTimeLine(1000, this);
    timeLine->setDirection(QTimeLine::Forward);
    timeLine->setFrameRange(0, 100);
//    timeLine->setCurveShape(QTimeLine::EaseInCurve);
    connect(timeLine, SIGNAL(frameChanged(int)), this, SLOT(setFrame(int)));
*/
    m_iStartX = 0;
    m_iStartY = 0;
}

WEditScreen::~WEditScreen()
{
    if(m_pKeyboard)
    {
        delete m_pKeyboard;
        m_pKeyboard = NULL;
    }
}

void WEditScreen::paintEvent(QPaintEvent* /*event*/)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPixmap(0, 0, *m_pImageBackground);
}

void WEditScreen::PrepareMainIconImage(QPixmap &imageUp, QPixmap &imageDown, int iNo)
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

void WEditScreen::PrepareIconImage(QPixmap &imageUp, QPixmap &imageDown, int iNo)
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

void WEditScreen::IconClicked()
{
    m_pKeyboard->CloseExtDlg();
    m_pPushButtonIcon->setChecked(true);

    for(int i=0;i<__ICON_NUMS__;i++)
        m_pButtonIcons[i]->show();

    m_pPushButtonName->setChecked(false);
    m_pKeyboard->hide();
    m_pPushButtonName->setEditEnabled(false);
}

void WEditScreen::NameClicked()
{
	m_pKeyboard->CloseExtDlg();
    m_pPushButtonIcon->setChecked(false);

     for(int i=0;i<__ICON_NUMS__;i++)
        m_pButtonIcons[i]->hide();

    m_pPushButtonName->setChecked(true);
    m_pKeyboard->show();
    m_pPushButtonName->setEditEnabled(true);

}

void WEditScreen::ButtonClick(int iSelect)
{
    m_iSelect = iSelect;
    PrepareMainIconImage(m_ImageSymbol[BUTTON_UP], m_ImageSymbol[BUTTON_DOWN], m_iSelect);
    m_pPushButtonIcon->SetImages(&m_ImageSymbol[BUTTON_UP], &m_ImageSymbol[BUTTON_DOWN], &m_ImageSymbol[BUTTON_DOWN]);
    m_pPushButtonIcon->update();

/*
    if (m_pButtonSelected!=NULL) delete m_pButtonSelected;
    m_pButtonSelected = new RtPushButton(this, iSelect);
    m_pButtonSelected->setGeometry(g_rectWayPtBtnIconClr[iSelect]);
    m_pButtonSelected->SetImages(&m_ImageIcons[BUTTON_DOWN][iSelect]);
    m_pButtonSelected->show();
    m_pButtonSelected->setEnabled(false);

    m_iSelect = iSelect;

    if (timeLine->state() != QTimeLine::NotRunning)
        timeLine->stop();

    QRect rect = m_pButtonSelected->frameGeometry();
    m_iStartX = rect.x();
    m_iStartY = rect.y();

    timeLine->start();
*/
}

void WEditScreen::setFrame(int frame)
{
    int iTargetX = g_rectButtonIcon.x()+abs(g_rectButtonIcon.width()-m_pButtonSelected->width())/2;
    int iTargetY = g_rectButtonIcon.y()+abs(g_rectButtonIcon.height()-m_pButtonSelected->height())/2;

    int iEndFrame = timeLine->endFrame();
    int iMoveX = (m_iStartX - iTargetX)*(frame)/iEndFrame;
    int iMoveY = (m_iStartY - iTargetY)*(frame)/iEndFrame;

    if(frame == iEndFrame)
    {
        delete m_pButtonSelected;
        m_pButtonSelected = NULL;
        PrepareMainIconImage(m_ImageSymbol[BUTTON_UP], m_ImageSymbol[BUTTON_DOWN], m_iSelect);
        m_pPushButtonIcon->SetImages(&m_ImageSymbol[BUTTON_UP], &m_ImageSymbol[BUTTON_DOWN], &m_ImageSymbol[BUTTON_DOWN]);
        m_pPushButtonIcon->update();
        timeLine->stop();
        m_iStartX = 0;
        m_iStartY = 0;

    }else {
        m_pButtonSelected->move(m_iStartX-iMoveX,m_iStartY-iMoveY);
    }
}

void WEditScreen::OnSave()
{
    this->done(1);
}

void WEditScreen::OnDelete()
{
    this->done(2);
}

void WEditScreen::OnCancel()
{
    this->done(3);
}

void WEditScreen::keySelected (const QString& key)
{
    m_pPushButtonName->insertText(key);

	CheckWhiteSpace();
}

void WEditScreen::backspace(void)
{
    m_pPushButtonName->backspace();

	CheckWhiteSpace();
}

void WEditScreen::switchKeypad(void)
{
    m_pPushButtonName->setEditFocus();
}

QString WEditScreen::getEditText(void)
{
    return m_pPushButtonName->getEditText();
}

void WEditScreen::setEditText(QString& strText)
{
    m_pPushButtonName->setEditText(strText);

	CheckWhiteSpace();
}

int  WEditScreen::getIconIdx(void)
{
    return m_iSelect;
}

void WEditScreen::setIconIdx(int iIconIdx)
{
    m_iSelect = iIconIdx;
    PrepareMainIconImage(m_ImageSymbol[BUTTON_UP], m_ImageSymbol[BUTTON_DOWN], m_iSelect);
    m_pPushButtonIcon->SetImages(&m_ImageSymbol[BUTTON_UP], &m_ImageSymbol[BUTTON_DOWN], &m_ImageSymbol[BUTTON_DOWN]);

}

bool WEditScreen::CheckWhiteSpace(void)
{
	bool ret = false;

	QString strTmp = "";
	strTmp = getEditText();
	strTmp = strTmp.trimmed();

	if(!strTmp.isEmpty()){
		m_pPushButtonSave->setEnabled(true);
	}else{
		m_pPushButtonSave->setEnabled(false);
		ret = true;
	}

	return ret;
}
