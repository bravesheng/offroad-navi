#ifndef SYSINFOSCREEN_H
#define SYSINFOSCREEN_H

#include <QWidget>
#include <QLabel>
#include "buttons.h"

class SysInfoScreen : public QWidget
{
    Q_OBJECT
public:
    SysInfoScreen(QWidget *parent = 0);

private:
//    CReturnButton ReturnBtn;

protected:
    QLabel         *m_pLabelTitle;
    QLabel         *m_pLabelAPver;
    QLabel         *m_pLabelOSver;
    QLabel         *m_pLabelBootver;
    QLabel         *m_pLabelSerialNumber;
    QPixmap        *m_pImageBackground;
    void paintEvent(QPaintEvent *event);
};

#endif // SYSINFOSCREEN_H
