#ifndef QPOIDATABASE_H
#define QPOIDATABASE_H

#include <QFile>
#include <QIODevice>
#include "QItemInfo.h"

#define MAX_ITEM_NUMS       500
#define MAX_VALUE_LENGTH    256

typedef enum _ORDER_TYPE
{
        ORDER_BY_NAME  = 0,
        ORDER_BY_DISTANCE = 1
} ORDER_TYPE;

class QPOIDatabase
{
public:
    QPOIDatabase();
    virtual ~QPOIDatabase();
    bool AddPOIItem(QItemInfo* pItemInfo);
	bool SavePOIItem(QItemInfo* pItemInfo);
    bool SaveDatabase(QString strPathName);
    bool ReadDatabase(QString strPathName);
    int GetItemCount(){return m_ItemCount;}
    QItemInfo& GetPOIItem(int index);
    bool ModifyPOIItem(int index,QItemInfo* pItemInfo);
    void SortItemArray(void);
    void DeleteAllInfo(void);
    bool DeleteItem(int index, bool bDoSort);
    ORDER_TYPE GetOrderType(void);
    void SetOrderType(ORDER_TYPE OrderType);
    bool  GetDistance(int index,double dCurLong, double dCurLat, int iUnitType, double& dDistance,double& dBearing);
	bool WriteTarget(QItemInfo* pItemInfo);
	bool ReadTarget(QItemInfo* pItemInfo);

private:
    static int  m_ItemCount;
    int	m_UniqueIdNums;		//the latest unused unique number
    ORDER_TYPE  m_OrderType;
    QFile m_DbFile;
    QItemInfo* m_pItemArray[MAX_ITEM_NUMS];
    void IncreaseItemCount(QItemInfo* pItemInfo);
    bool WriteItem(QItemInfo* pItemInfo);
    bool ReadItem(QItemInfo* pItemInfo);
    static int CompareByName( const void *arg1, const void *arg2 );
	static int CompareByDistance( const void *arg1, const void *arg2 );
};

#endif // QPOIDATABASE_H
