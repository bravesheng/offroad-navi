#ifndef RtEditButton_H
#define RtEditButton_H

#include "RtPushButton.h"
#include "RtEditBox.h"

class RtEditButton : public RtPushButton
{
public:
    RtEditButton(QWidget *parent = NULL);
    void setEditEnabled(bool);
    void insertText(const QString &);
    void backspace(void);
    void setEditFocus(void);

    QString getEditText(void);
    void setEditText(QString& strText);

private:
    void paintCustomEvent(QPaintEvent *event);

protected:
    RtEditBox *m_pEditBox;
    QPixmap m_EditImg;
};

#endif // RtEditButton_H
