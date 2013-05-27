#ifndef BUTTONS_H
#define BUTTONS_H
#include <QAbstractButton>

//class CAbstractButton

class CRtAbstractButton : public QAbstractButton
{
public:
	CRtAbstractButton(QWidget* pParent);
protected:
    void paintEvent(QPaintEvent* event);
    QPixmap* pNormalImage;		//main skin for this Gadgets
	QPixmap* pDownImage;	//pressed down or focus skin for this Gadgets
};

class CReturnButton : public CRtAbstractButton
{
public:
	CReturnButton(QWidget* pParent);
};
/*
class CColorPicker : public QAbstractButton
{

}
*/
#endif // BUTTONS_H

