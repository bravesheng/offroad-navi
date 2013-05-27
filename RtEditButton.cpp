#include "RtEditButton.h"

RtEditButton::RtEditButton(QWidget *parent)
        :RtPushButton(parent)
{
    m_pEditBox = new RtEditBox(this);
    m_pEditBox->setGeometry(15,15,150,35);//w:180,h:65
    m_pEditBox->setText("");
    m_EditImg = QPixmap(QObject::tr("images\\Waypoints\\EditBoxBK.PNG"));
    m_pEditBox->setImages(&m_EditImg);

    QFont font("tahoma", 16);
    font.setStyleStrategy(QFont::PreferAntialias);
    m_pEditBox->setFont(font);
    m_pEditBox->setMaxLength(40);
    m_pEditBox->setDragEnabled(true);
}

void RtEditButton::paintCustomEvent(QPaintEvent* /*event*/)
{
//    m_pEditBox->paintEvent(event);
}

void RtEditButton::setEditEnabled(bool bEnable)
{
    m_pEditBox->setEnabled(bEnable);
    if(bEnable)
        m_pEditBox->setFocus();
}

void RtEditButton::insertText(const QString &Text)
{
    m_pEditBox->insert(Text);
    m_pEditBox->setFocus();
}

QString RtEditButton::getEditText(void)
{
    return m_pEditBox->text();
}

void RtEditButton::setEditText(QString& strText)
{
    m_pEditBox->setText(strText);
    m_pEditBox->setFocus();
}

void RtEditButton::backspace(void)
{
    m_pEditBox->backspace();
    m_pEditBox->setFocus();
}

void RtEditButton::setEditFocus(void)
{
    m_pEditBox->setFocus();
}
