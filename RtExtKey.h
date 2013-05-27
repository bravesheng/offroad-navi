#ifndef RTEXTKEY_H
#define RTEXTKEY_H

#include <QDialog>
#include "RtKeyButton.h"
#include <QSignalMapper>

class RtExtKey: public QDialog
{
    Q_OBJECT
public:
    RtExtKey(QWidget *parent = NULL,QString strExtKey="A");

Q_SIGNALS:
    void keySelected (const QString& key);

public slots:
    void ButtonClick(int iIndexKey);

private:
    RtKeyButton    *m_pExtKey[7];
    RtKeyButton    *m_pCancelKey;
    QSignalMapper  *signalMapper;
    QPixmap         m_ImageBackground;
    QPixmap         m_Key1[2];
    QPixmap         m_Key2[2];
    QString         m_strExtKey;

    void AddCancelButton(QPoint &rectCancel);
    void setupExtA(QString strExt);
    void setupExtC(QString strExt);
    void setupExtE(QString strExt);
    void setupExtI(QString strExt);
    void setupExtN(QString strExt);
    void setupExtO(QString strExt);
    void setupExtS(QString strExt);
    void setupExtU(QString strExt);
    void setupExtY(QString strExt);

protected:
    void paintEvent(QPaintEvent* /*event*/);
};

#endif // RTEXTKEY_H
