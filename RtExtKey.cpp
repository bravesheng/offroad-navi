#include <QPainter>
#include "RtExtKey.h"
#include "RtGlobalDefine.h"

RtExtKey::RtExtKey(QWidget *parent,QString strExtKey)
        : QDialog(parent)
{
    m_strExtKey = strExtKey;

   this->setWindowFlags(Qt::FramelessWindowHint);

//  Load background image
    m_ImageBackground = QPixmap(g_strKeyboardBK);

// Load Key1 image
    m_Key1[0] = QPixmap(g_strKey1Up);
    m_Key1[1] = QPixmap(g_strKey1Down);

// Load Key2 image
    m_Key2[0] = QPixmap(g_strKey2Up);
    m_Key2[1] = QPixmap(g_strKey2Down);

// Setup Signal Mapper
    signalMapper = new QSignalMapper;
    connect(signalMapper, SIGNAL(mapped(const QString&)),
                    this, SIGNAL(keySelected(const QString&)));

    QString strTmp = m_strExtKey.toLower();
    if(strTmp.compare("a")== 0)
        setupExtA(m_strExtKey);
    else if(strTmp.compare("c")== 0)
        setupExtC(m_strExtKey);
    else if(strTmp.compare("e")== 0)
        setupExtE(m_strExtKey);
    else if(strTmp.compare("i")== 0)
        setupExtI(m_strExtKey);
    else if(strTmp.compare("n")== 0)
        setupExtN(m_strExtKey);
    else if(strTmp.compare("o")== 0)
        setupExtO(m_strExtKey);
    else if(strTmp.compare("s")== 0)
        setupExtS(m_strExtKey);
    else if(strTmp.compare("u")== 0)
        setupExtU(m_strExtKey);
    else if(strTmp.compare("y")== 0)
        setupExtY(m_strExtKey);

}

void RtExtKey::paintEvent(QPaintEvent*)///* event*/
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, m_ImageBackground);
}

void RtExtKey::setupExtA(QString strExt)
{
    QString strKeyUpper[7] = {
        "\xC0","\xC1","\xC2","\xC3","\xC4",
        "\xC5","\xC6"
    };

    QString strKeyLower[7] = {
        "\xE0","\xE1","\xE2","\xE3","\xE4",
        "\xE5","\xE6"
    };

    QString strKeyText[7];
    if(strExt.compare("A")==0)
    {
        for(int l=0;l<7;l++)
            strKeyText[l] = strKeyUpper[l];
    }
    else
    {
        for(int l=0;l<7;l++)
            strKeyText[l] = strKeyLower[l];
    }

    QPoint keyPoints[7] = {
        QPoint( 7,  7),QPoint(31, 7),QPoint(55,7),QPoint(79,7),QPoint(103,7),
        QPoint(127, 7),QPoint(151,7)
    };
    QRect rectBtnText = QRect(5,8,15,15);

    //Key buttons
    for(int i=0;i<7;i++)
    {
        m_pExtKey[i] = new RtKeyButton(this,i);
        m_pExtKey[i]->SetImages(&m_Key1[0],&m_Key2[0]);
        m_pExtKey[i]->setGeometry(keyPoints[i].x(),keyPoints[i].y(),m_Key1[0].width(),m_Key1[0].height());
        m_pExtKey[i]->setButtonText(strKeyText[i],rectBtnText);
        connect(m_pExtKey[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(m_pExtKey[i], strKeyText[i]);
        m_pExtKey[i]->show();

 //       connect(m_pExtKey[i], SIGNAL(MousePress(int,int)), this, SLOT(MousePress(int,int)));
 //       connect(m_pExtKey[i], SIGNAL(MouseRelease()), this, SLOT(MouseRelease()));
        connect(m_pExtKey[i], SIGNAL(ButtonClick(int)), this, SLOT(ButtonClick(int)));
    }

    QPoint CancelPt= QPoint(175,7);
    AddCancelButton(CancelPt);
}

void RtExtKey::setupExtC(QString strExt)
{
    QString strKeyText[1];
    if(strExt.compare("C")==0){
        strKeyText[0] = "\xC7";
    }else{
        strKeyText[0] = "\xE7";
    }

    QPoint keyPoints[] = {QPoint( 7,  7)};

    QRect rectBtnText = QRect(5,8,15,15);

    //Key buttons
    for(int i=0;i<1;i++)
    {
        m_pExtKey[i] = new RtKeyButton(this,i);
        m_pExtKey[i]->SetImages(&m_Key1[0],&m_Key2[0]);
        m_pExtKey[i]->setGeometry(keyPoints[i].x(),keyPoints[i].y(),m_Key1[0].width(),m_Key1[0].height());
        m_pExtKey[i]->setButtonText(strKeyText[i],rectBtnText);
        connect(m_pExtKey[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(m_pExtKey[i], strKeyText[i]);
        m_pExtKey[i]->show();

 //       connect(m_pExtKey[i], SIGNAL(MousePress(int,int)), this, SLOT(MousePress(int,int)));
 //       connect(m_pExtKey[i], SIGNAL(MouseRelease()), this, SLOT(MouseRelease()));
        connect(m_pExtKey[i], SIGNAL(ButtonClick(int)), this, SLOT(ButtonClick(int)));
    }

    QPoint CancelPt= QPoint(31, 7);
    AddCancelButton(CancelPt);
}

void RtExtKey::setupExtE(QString strExt)
{
    QString strKeyUpper[] = {
        "\xC8","\xC9","\xCA","\xCB"
    };

    QString strKeyLower[] = {
        "\xE8","\xE9","\xEA","\xEB"
    };

    QString strKeyText[4];
    if(strExt.compare("E")==0)
    {
        for(int l=0;l<4;l++)
            strKeyText[l] = strKeyUpper[l];
    }
    else
    {
        for(int l=0;l<4;l++)
            strKeyText[l] = strKeyLower[l];
    }

    QPoint keyPoints[4] = {
        QPoint( 7,  7),QPoint(31, 7),QPoint(55,7),QPoint(79,7)
    };
    QRect rectBtnText = QRect(5,8,15,15);

    //Key buttons
    for(int i=0;i<4;i++)
    {
        m_pExtKey[i] = new RtKeyButton(this,i);
        m_pExtKey[i]->SetImages(&m_Key1[0],&m_Key2[0]);
        m_pExtKey[i]->setGeometry(keyPoints[i].x(),keyPoints[i].y(),m_Key1[0].width(),m_Key1[0].height());
        m_pExtKey[i]->setButtonText(strKeyText[i],rectBtnText);
        connect(m_pExtKey[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(m_pExtKey[i], strKeyText[i]);
        m_pExtKey[i]->show();

 //       connect(m_pExtKey[i], SIGNAL(MousePress(int,int)), this, SLOT(MousePress(int,int)));
 //       connect(m_pExtKey[i], SIGNAL(MouseRelease()), this, SLOT(MouseRelease()));
        connect(m_pExtKey[i], SIGNAL(ButtonClick(int)), this, SLOT(ButtonClick(int)));
    }

    QPoint CancelPt= QPoint(103,7);
    AddCancelButton(CancelPt);
}

void RtExtKey::setupExtI(QString strExt)
{
    QString strKeyUpper[] = {
        "\xCC","\xCD","\xCE","\xCF"
    };

    QString strKeyLower[] = {
        "\xEC","\xED","\xEE","\xEF"
    };

    QString strKeyText[4];
    if(strExt.compare("I")==0)
    {
        for(int l=0;l<4;l++)
            strKeyText[l] = strKeyUpper[l];
    }
    else
    {
        for(int l=0;l<4;l++)
            strKeyText[l] = strKeyLower[l];
    }

    QPoint keyPoints[4] = {
        QPoint( 7,  7),QPoint(31, 7),QPoint(55,7),QPoint(79,7)
    };
    QRect rectBtnText = QRect(5,8,15,15);

    //Key buttons
    for(int i=0;i<4;i++)
    {
        m_pExtKey[i] = new RtKeyButton(this,i);
        m_pExtKey[i]->SetImages(&m_Key1[0],&m_Key2[0]);
        m_pExtKey[i]->setGeometry(keyPoints[i].x(),keyPoints[i].y(),m_Key1[0].width(),m_Key1[0].height());
        m_pExtKey[i]->setButtonText(strKeyText[i],rectBtnText);
        connect(m_pExtKey[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(m_pExtKey[i], strKeyText[i]);
        m_pExtKey[i]->show();

 //       connect(m_pExtKey[i], SIGNAL(MousePress(int,int)), this, SLOT(MousePress(int,int)));
 //       connect(m_pExtKey[i], SIGNAL(MouseRelease()), this, SLOT(MouseRelease()));
        connect(m_pExtKey[i], SIGNAL(ButtonClick(int)), this, SLOT(ButtonClick(int)));
    }

    QPoint CancelPt= QPoint(103,7);
    AddCancelButton(CancelPt);
}

void RtExtKey::setupExtN(QString strExt)
{
    QString strKeyText[1];
    if(strExt.compare("N")==0){
        strKeyText[0] = "\xD1";
    }else{
        strKeyText[0] = "\xF1";
    }

    QPoint keyPoints[] = {QPoint( 7,  7)};

    QRect rectBtnText = QRect(5,8,15,15);

    //Key buttons
    for(int i=0;i<1;i++)
    {
        m_pExtKey[i] = new RtKeyButton(this,i);
        m_pExtKey[i]->SetImages(&m_Key1[0],&m_Key2[0]);
        m_pExtKey[i]->setGeometry(keyPoints[i].x(),keyPoints[i].y(),m_Key1[0].width(),m_Key1[0].height());
        m_pExtKey[i]->setButtonText(strKeyText[i],rectBtnText);
        connect(m_pExtKey[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(m_pExtKey[i], strKeyText[i]);
        m_pExtKey[i]->show();

 //       connect(m_pExtKey[i], SIGNAL(MousePress(int,int)), this, SLOT(MousePress(int,int)));
 //       connect(m_pExtKey[i], SIGNAL(MouseRelease()), this, SLOT(MouseRelease()));
        connect(m_pExtKey[i], SIGNAL(ButtonClick(int)), this, SLOT(ButtonClick(int)));
    }

    QPoint CancelPt= QPoint(31, 7);
    AddCancelButton(CancelPt);
}

void RtExtKey::setupExtO(QString strExt)
{
    QString strKeyUpper[] = {
        "\xD2","\xD3","\xD4","\xD5","\xD6",
        "\xD8"
    };

    QString strKeyLower[] = {
        "\xF2","\xF3","\xF4","\xF5","\xF6",
        "\xF8"
    };

    QString strKeyText[6];
    if(strExt.compare("O")==0)
    {
        for(int l=0;l<6;l++)
            strKeyText[l] = strKeyUpper[l];
    }
    else
    {
        for(int l=0;l<6;l++)
            strKeyText[l] = strKeyLower[l];
    }

    QPoint keyPoints[6] = {
        QPoint( 7,  7),QPoint(31, 7),QPoint(55,7),QPoint(79,7),QPoint(103,7),
        QPoint(127, 7)
    };
    QRect rectBtnText = QRect(5,8,15,15);

    //Key buttons
    for(int i=0;i<6;i++)
    {
        m_pExtKey[i] = new RtKeyButton(this,i);
        m_pExtKey[i]->SetImages(&m_Key1[0],&m_Key2[0]);
        m_pExtKey[i]->setGeometry(keyPoints[i].x(),keyPoints[i].y(),m_Key1[0].width(),m_Key1[0].height());
        m_pExtKey[i]->setButtonText(strKeyText[i],rectBtnText);
        connect(m_pExtKey[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(m_pExtKey[i], strKeyText[i]);
        m_pExtKey[i]->show();

 //       connect(m_pExtKey[i], SIGNAL(MousePress(int,int)), this, SLOT(MousePress(int,int)));
 //       connect(m_pExtKey[i], SIGNAL(MouseRelease()), this, SLOT(MouseRelease()));
        connect(m_pExtKey[i], SIGNAL(ButtonClick(int)), this, SLOT(ButtonClick(int)));
    }

    QPoint CancelPt= QPoint(151,7);
    AddCancelButton(CancelPt);
}

void RtExtKey::setupExtS(QString strExt)
{
    QString strKeyUpper[] = {
        "\xA7","\xDF"
    };

    QString strKeyLower[] = {
        "\xA7","\xDF"
    };

    QString strKeyText[2];
    if(strExt.compare("S")==0)
    {
        for(int l=0;l<2;l++)
            strKeyText[l] = strKeyUpper[l];
    }
    else
    {
        for(int l=0;l<2;l++)
            strKeyText[l] = strKeyLower[l];
    }

    QPoint keyPoints[2] = {
        QPoint( 7,  7),QPoint(31, 7)
    };
    QRect rectBtnText = QRect(5,8,15,15);

    //Key buttons
    for(int i=0;i<2;i++)
    {
        m_pExtKey[i] = new RtKeyButton(this,i);
        m_pExtKey[i]->SetImages(&m_Key1[0],&m_Key2[0]);
        m_pExtKey[i]->setGeometry(keyPoints[i].x(),keyPoints[i].y(),m_Key1[0].width(),m_Key1[0].height());
        m_pExtKey[i]->setButtonText(strKeyText[i],rectBtnText);
        connect(m_pExtKey[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(m_pExtKey[i], strKeyText[i]);
        m_pExtKey[i]->show();

 //       connect(m_pExtKey[i], SIGNAL(MousePress(int,int)), this, SLOT(MousePress(int,int)));
 //       connect(m_pExtKey[i], SIGNAL(MouseRelease()), this, SLOT(MouseRelease()));
        connect(m_pExtKey[i], SIGNAL(ButtonClick(int)), this, SLOT(ButtonClick(int)));
    }

    QPoint CancelPt= QPoint(55,7);
    AddCancelButton(CancelPt);
}

void RtExtKey::setupExtU(QString strExt)
{
    QString strKeyUpper[] = {
        "\xD9","\xDA","\xDB","\xDC"
    };

    QString strKeyLower[] = {
        "\xF9","\xFA","\xFB","\xFC"
    };

    QString strKeyText[4];
    if(strExt.compare("U")==0)
    {
        for(int l=0;l<4;l++)
            strKeyText[l] = strKeyUpper[l];
    }
    else
    {
        for(int l=0;l<4;l++)
            strKeyText[l] = strKeyLower[l];
    }

    QPoint keyPoints[4] = {
        QPoint( 7,  7),QPoint(31, 7),QPoint(55,7),QPoint(79,7)
    };
    QRect rectBtnText = QRect(5,8,15,15);

    //Key buttons
    for(int i=0;i<4;i++)
    {
        m_pExtKey[i] = new RtKeyButton(this,i);
        m_pExtKey[i]->SetImages(&m_Key1[0],&m_Key2[0]);
        m_pExtKey[i]->setGeometry(keyPoints[i].x(),keyPoints[i].y(),m_Key1[0].width(),m_Key1[0].height());
        m_pExtKey[i]->setButtonText(strKeyText[i],rectBtnText);
        connect(m_pExtKey[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(m_pExtKey[i], strKeyText[i]);
        m_pExtKey[i]->show();

 //       connect(m_pExtKey[i], SIGNAL(MousePress(int,int)), this, SLOT(MousePress(int,int)));
 //       connect(m_pExtKey[i], SIGNAL(MouseRelease()), this, SLOT(MouseRelease()));
        connect(m_pExtKey[i], SIGNAL(ButtonClick(int)), this, SLOT(ButtonClick(int)));
    }

    QPoint CancelPt= QPoint(103,7);
    AddCancelButton(CancelPt);
}

void RtExtKey::setupExtY(QString strExt)
{
    QString strKeyUpper[] = {
        "\xDD"
    };

    QString strKeyLower[] = {
        "\xFD"
    };

    QString strKeyText[1];
    if(strExt.compare("Y")==0)
    {
        for(int l=0;l<1;l++)
            strKeyText[l] = strKeyUpper[l];
    }
    else
    {
        for(int l=0;l<1;l++)
            strKeyText[l] = strKeyLower[l];
    }

    QPoint keyPoints[2] = {
        QPoint( 7,  7)//,QPoint(31, 7)
    };
    QRect rectBtnText = QRect(5,8,15,15);

    //Key buttons
    for(int i=0;i<1;i++)
    {
        m_pExtKey[i] = new RtKeyButton(this,i);
        m_pExtKey[i]->SetImages(&m_Key1[0],&m_Key2[0]);
        m_pExtKey[i]->setGeometry(keyPoints[i].x(),keyPoints[i].y(),m_Key1[0].width(),m_Key1[0].height());
        m_pExtKey[i]->setButtonText(strKeyText[i],rectBtnText);
        connect(m_pExtKey[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(m_pExtKey[i], strKeyText[i]);
        m_pExtKey[i]->show();

 //       connect(m_pExtKey[i], SIGNAL(MousePress(int,int)), this, SLOT(MousePress(int,int)));
 //       connect(m_pExtKey[i], SIGNAL(MouseRelease()), this, SLOT(MouseRelease()));
        connect(m_pExtKey[i], SIGNAL(ButtonClick(int)), this, SLOT(ButtonClick(int)));
    }

    QPoint CancelPt= QPoint(31,7);
    AddCancelButton(CancelPt);
}

void RtExtKey::AddCancelButton(QPoint &rectCancel)
{
    QRect rectBtnText = QRect(5,8,15,15);
    m_pCancelKey = new RtKeyButton(this,0);
    m_pCancelKey->SetImages(&m_Key2[0],&m_Key1[0]);
    m_pCancelKey->setGeometry(rectCancel.x(),rectCancel.y(),m_Key2[0].width(),m_Key2[0].height());
    QString strTmp = "X";
    m_pCancelKey->setButtonText(strTmp,rectBtnText);
    connect(m_pCancelKey, SIGNAL(ButtonClick(int)), this, SLOT(close()));
    m_pCancelKey->show();
}

void RtExtKey::ButtonClick(int iIndexKey)
{
    this->done(iIndexKey);
}
