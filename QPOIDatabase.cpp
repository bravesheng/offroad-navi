#include "QPOIDatabase.h"
#include "RtGPS.h"
#include "Global.h"

#define ID_ITEM_HEADER		0xA0F0
#define ID_ITEM_TAIL        0xA0F1
#define ID_END_OF_DATA		0x0000
#define ID_HEADER_OF_DATA	0xA000

#define SIZE_OF_ID		2

int QPOIDatabase::m_ItemCount = 0;
//const QString g_strWayPtDB_Path	      ("\\ShellDisk\\Shell\\OffRoadNavi\\data\\WaypointDB.db");
//const QString g_strTargetPath		  ("\\ShellDisk\\Shell\\OffRoadNavi\\data\\target.tag");
#define g_strWayPtDB_Path	  ("\\ShellDisk\\Shell\\OffRoadNavi\\data\\WaypointDB.db")
#define g_strTargetPath		  ("\\ShellDisk\\Shell\\OffRoadNavi\\data\\target.tag")

QPOIDatabase::QPOIDatabase()
{
    m_ItemCount = 0;
    m_UniqueIdNums = 0;
    m_OrderType = ORDER_BY_NAME;
}

QPOIDatabase::~QPOIDatabase()
{
    DeleteAllInfo();
}

bool QPOIDatabase::AddPOIItem(QItemInfo* pItemInfo)
{
    if(m_ItemCount < MAX_ITEM_NUMS)
    {
        if(pItemInfo)
        {
            m_pItemArray[m_ItemCount] = new QItemInfo();
            *m_pItemArray[m_ItemCount] = pItemInfo;
            IncreaseItemCount(m_pItemArray[m_ItemCount]);
            return true;
        }
    }
    return false;
}

void QPOIDatabase::IncreaseItemCount(QItemInfo* pItemInfo)
{
    pItemInfo->m_UniqueId = m_UniqueIdNums;
    m_UniqueIdNums++;
    m_ItemCount++;
}

bool QPOIDatabase::SaveDatabase(QString strPathName)
{
    unsigned short RecvedBytes = 0;
    bool ret = false;

    //No any data,so we will not do the save action.
    if(m_ItemCount<=0)
        return ret;

    m_DbFile.setFileName(strPathName);
    if(!m_DbFile.open(QIODevice::Truncate | QIODevice::WriteOnly))
      return ret;

    //write file header
    RecvedBytes = ID_HEADER_OF_DATA;
    m_DbFile.write((char*)&RecvedBytes, sizeof(RecvedBytes));

   //Write
   for(int i=0; i < m_ItemCount; i++)
   {
      WriteItem(m_pItemArray[i]);
   }

   //write file end
   RecvedBytes = ID_END_OF_DATA;
   m_DbFile.write((char*)&RecvedBytes, sizeof(RecvedBytes));

   m_DbFile.close();
   ret = true;

   return ret;
}

bool QPOIDatabase::SavePOIItem(QItemInfo* pItemInfo)
{
     unsigned short DataHeader = ID_END_OF_DATA;
     unsigned short RecvedBytes = 0;
	 bool ret = false;

     m_DbFile.setFileName(g_strWayPtDB_Path);
	 if(m_DbFile.exists() && m_DbFile.open(QIODevice::ReadWrite))
	 {
		 qint64 size = m_DbFile.size();
		 if(size<=2)
			 return ret;

		m_DbFile.seek(size-sizeof(RecvedBytes));

		RecvedBytes = m_DbFile.read((char*)&DataHeader, SIZE_OF_ID);
		if((RecvedBytes) && (DataHeader == ID_END_OF_DATA))
		{
			m_DbFile.seek(size-sizeof(RecvedBytes));

			WriteItem(pItemInfo);

		   //write file end
		   RecvedBytes = ID_END_OF_DATA;
		   m_DbFile.write((char*)&RecvedBytes, sizeof(RecvedBytes));

		   m_DbFile.close();
		}

	 }
	 else
	 {
	    if(!m_DbFile.open(QIODevice::Truncate | QIODevice::WriteOnly))
		  return ret;

		//write file header
		RecvedBytes = ID_HEADER_OF_DATA;
		m_DbFile.write((char*)&RecvedBytes, sizeof(RecvedBytes));

        WriteItem(pItemInfo);

	   //write file end
	   RecvedBytes = ID_END_OF_DATA;
	   m_DbFile.write((char*)&RecvedBytes, sizeof(RecvedBytes));

	   m_DbFile.close();
	   ret = true;
	 }

	 return ret;
}

#define POS_ATTR_ID     	0
#define POS_DATA_LEN            1
#define POS_WRITE_HEADER_BYTES	4
bool QPOIDatabase::WriteItem(QItemInfo* pItemInfo)
{
    unsigned short AttributeId = 0;
    unsigned short DataLength = 0;
    wchar_t WRITE_DATA[MAX_VALUE_LENGTH];

    memset(WRITE_DATA, 0, sizeof(WRITE_DATA));
    //write item header
    AttributeId = ID_ITEM_HEADER;
    m_DbFile.write((char*)&AttributeId, sizeof(AttributeId));

    // Icon ID
    m_DbFile.write((char*)&pItemInfo->m_IconId, sizeof(pItemInfo->m_IconId));

    // Lon data
    m_DbFile.write((char*)&pItemInfo->m_Lon, sizeof(pItemInfo->m_Lon));

    // Lat data
    m_DbFile.write((char*)&pItemInfo->m_Lat, sizeof(pItemInfo->m_Lat));

    // Alt data
    m_DbFile.write((char*)&pItemInfo->m_Alt, sizeof(pItemInfo->m_Alt));

    DataLength = pItemInfo->m_Name.toWCharArray(WRITE_DATA);
    // Name length
    m_DbFile.write((char*)&DataLength, sizeof(DataLength));

    // Name Data
    m_DbFile.write((char*)&WRITE_DATA, 2*DataLength);

    //write item tail
    AttributeId = ID_ITEM_TAIL;
    m_DbFile.write((char*)&AttributeId, sizeof(AttributeId));
    return false;
}

bool QPOIDatabase::WriteTarget(QItemInfo* pItemInfo)
{
	bool bRet = false;
    unsigned short AttributeId = 0;
    unsigned short DataLength = 0;
    wchar_t WRITE_DATA[MAX_VALUE_LENGTH];

	QFile targetFile;
	targetFile.setFileName(g_strTargetPath);

    if(!targetFile.open(QIODevice::Truncate | QIODevice::WriteOnly))
		  return bRet;

    memset(WRITE_DATA, 0, sizeof(WRITE_DATA));
    //write item header
    AttributeId = ID_ITEM_HEADER;
    targetFile.write((char*)&AttributeId, sizeof(AttributeId));

    // Icon ID
    targetFile.write((char*)&pItemInfo->m_IconId, sizeof(pItemInfo->m_IconId));

    // Lon data
    targetFile.write((char*)&pItemInfo->m_Lon, sizeof(pItemInfo->m_Lon));

    // Lat data
    targetFile.write((char*)&pItemInfo->m_Lat, sizeof(pItemInfo->m_Lat));

    // Alt data
    targetFile.write((char*)&pItemInfo->m_Alt, sizeof(pItemInfo->m_Alt));

    DataLength = pItemInfo->m_Name.toWCharArray(WRITE_DATA);
    // Name length
    targetFile.write((char*)&DataLength, sizeof(DataLength));

    // Name Data
    targetFile.write((char*)&WRITE_DATA, 2*DataLength);

    //write item tail
    AttributeId = ID_ITEM_TAIL;
    targetFile.write((char*)&AttributeId, sizeof(AttributeId));
	targetFile.close();
	bRet = true;

    return bRet;
}

bool QPOIDatabase::ReadItem(QItemInfo* pItemInfo)
{
    bool bRet = false;
    unsigned short RecvedBytes = 0;
    unsigned short DataLength = 0;
    unsigned short DataHeader = ID_END_OF_DATA;
    double TmpData = 0.0;
    wchar_t READ_DATA[MAX_VALUE_LENGTH];

    memset(READ_DATA, 0, sizeof(READ_DATA));

    //read icon index
    m_DbFile.read((char*)&RecvedBytes,sizeof(RecvedBytes));
    pItemInfo->m_IconId = RecvedBytes;

    //read Lon data
    TmpData = 0.0;
    m_DbFile.read((char*)&TmpData,sizeof(TmpData));
    pItemInfo->m_Lon = TmpData;

    //read Lat data
    TmpData = 0.0;
    m_DbFile.read((char*)&TmpData,sizeof(TmpData));
    pItemInfo->m_Lat = TmpData;

    //read Alt data
    TmpData = 0.0;
    m_DbFile.read((char*)&TmpData,sizeof(TmpData));
    pItemInfo->m_Alt = TmpData;

    //read Name length
    DataLength = 0;
    m_DbFile.read((char*)&DataLength,sizeof(DataLength));
    //copy data into READ_DATA
    if((DataLength > 0) && (DataLength < MAX_VALUE_LENGTH))	//means data length exist
    {
        int ReadLen = 2*DataLength;
        RecvedBytes = m_DbFile.read((char*)READ_DATA, ReadLen);
        if(RecvedBytes == ReadLen)
        {
            pItemInfo->m_Name = pItemInfo->m_Name.fromWCharArray(READ_DATA,DataLength);
        }
    }

    DataHeader = 0;
    m_DbFile.read((char*)&DataHeader,SIZE_OF_ID);
    if(DataHeader & ID_ITEM_TAIL)
    {
        //means end of item
        bRet = true;
    }
    return bRet;
}

bool QPOIDatabase::ReadTarget(QItemInfo* pItemInfo)
{
    bool bRet = false;
    unsigned short RecvedBytes = 0;
    unsigned short DataLength = 0;
    unsigned short DataHeader = ID_END_OF_DATA;
    double TmpData = 0.0;
    wchar_t READ_DATA[MAX_VALUE_LENGTH];

    memset(READ_DATA, 0, sizeof(READ_DATA));

	QFile targetFile;
	targetFile.setFileName(g_strTargetPath);

    if(!targetFile.open(QIODevice::ReadOnly))
		  return bRet;

    //read item header
    targetFile.read((char*)&RecvedBytes, sizeof(RecvedBytes));
	if(RecvedBytes != ID_ITEM_HEADER)
	{
		targetFile.close();
		return bRet;
	}

    //read icon index
    targetFile.read((char*)&RecvedBytes,sizeof(RecvedBytes));
    pItemInfo->m_IconId = RecvedBytes;

    //read Lon data
    TmpData = 0.0;
    targetFile.read((char*)&TmpData,sizeof(TmpData));
    pItemInfo->m_Lon = TmpData;

    //read Lat data
    TmpData = 0.0;
    targetFile.read((char*)&TmpData,sizeof(TmpData));
    pItemInfo->m_Lat = TmpData;

    //read Alt data
    TmpData = 0.0;
    targetFile.read((char*)&TmpData,sizeof(TmpData));
    pItemInfo->m_Alt = TmpData;

    //read Name length
    DataLength = 0;
    targetFile.read((char*)&DataLength,sizeof(DataLength));
    //copy data into READ_DATA
    if((DataLength > 0) && (DataLength < MAX_VALUE_LENGTH))	//means data length exist
    {
        int ReadLen = 2*DataLength;
        RecvedBytes = targetFile.read((char*)READ_DATA, ReadLen);
        if(RecvedBytes == ReadLen)
        {
            pItemInfo->m_Name = pItemInfo->m_Name.fromWCharArray(READ_DATA,DataLength);
        }
    }

    DataHeader = 0;
    targetFile.read((char*)&DataHeader,SIZE_OF_ID);
    if(DataHeader & ID_ITEM_TAIL)
    {
        //means end of item
		targetFile.close();
        bRet = true;
    }

	targetFile.close();
    return bRet;
}

bool QPOIDatabase::ReadDatabase(QString strPathName)
{
    bool bRet = false;

    unsigned short RecvedBytes = 0;
    unsigned short DataHeader = ID_END_OF_DATA;

    //Read MyFlashDisk data file
     m_DbFile.setFileName(strPathName);
    if(m_DbFile.open(QIODevice::ReadOnly))
    {
        //read header first
        RecvedBytes = m_DbFile.read((char*)&DataHeader, SIZE_OF_ID);
        if((RecvedBytes) && (DataHeader == ID_HEADER_OF_DATA))
        {
            for(;m_ItemCount < MAX_ITEM_NUMS;)
            {
                RecvedBytes = m_DbFile.read((char*)&DataHeader, SIZE_OF_ID);
                m_pItemArray[m_ItemCount] = new QItemInfo();

                if(RecvedBytes)
                {
                    if(DataHeader == ID_ITEM_HEADER)
                    {
                        if(ReadItem(m_pItemArray[m_ItemCount]))
                        {
                            IncreaseItemCount(m_pItemArray[m_ItemCount]);
                            bRet = true;
                        }
                        else
                        {
                            delete m_pItemArray[m_ItemCount];
                            m_pItemArray[m_ItemCount] = NULL;
                        }
                    }
                    else
                    {
                        delete m_pItemArray[m_ItemCount];
                        m_pItemArray[m_ItemCount] = NULL;
                        break;
                    }
                }
                else
                {
                    delete m_pItemArray[m_ItemCount];
                    m_pItemArray[m_ItemCount] = NULL;
                    break;
                }
            }
        }
        m_DbFile.close();
    }

    return bRet;
}

QItemInfo& QPOIDatabase::GetPOIItem(int index)
{
	return *m_pItemArray[index];
   //if((index < m_ItemCount)&&(index >= 0))
   // {
   //     *pItemInfo = m_pItemArray[index];
   //     return true;
   // }
}

bool QPOIDatabase::ModifyPOIItem(int index,QItemInfo* pItemInfo)
{
    if(pItemInfo)
    {
        if((index < m_ItemCount)&&(index >= 0))
        {
            *m_pItemArray[index] = *pItemInfo;
            return true;
        }
    }

    return false;
}

void QPOIDatabase::SortItemArray(void)
{
    if(m_OrderType == ORDER_BY_NAME)
    {
        qsort(m_pItemArray, m_ItemCount, sizeof(QItemInfo*), CompareByName);
    }
    else if(m_OrderType == ORDER_BY_DISTANCE)
    {
        if(RtGPS_IfFix())
            qsort(m_pItemArray, m_ItemCount, sizeof(QItemInfo*), CompareByDistance);
    }
}

int QPOIDatabase::CompareByName( const void *arg1, const void *arg2 )
{
    QItemInfo* pItemInfo1 = *(QItemInfo**)arg1;
    QItemInfo* pItemInfo2 = *(QItemInfo**)arg2;
    return pItemInfo1->m_Name.compare(pItemInfo2->m_Name,Qt::CaseInsensitive);
}

int QPOIDatabase::CompareByDistance( const void *arg1, const void *arg2 )
{
    QItemInfo* pItemInfo1 = *(QItemInfo**)arg1;
    QItemInfo* pItemInfo2 = *(QItemInfo**)arg2;

    double dCurLong = 0.0;
    double dCurLat = 0.0;
    double dCurEle = 0.0;
    double dBearing = 0.0;
    double dDistItem1 = 0.0;
    double dDistItem2 = 0.0;
    RtGPS_GetPos(&dCurLong, &dCurLat, &dCurEle);

    pItemInfo1->GetDistance(dCurLong,dCurLat,CGlobal::UNIT_M,dDistItem1,dBearing);
    pItemInfo2->GetDistance(dCurLong,dCurLat,CGlobal::UNIT_M,dDistItem2,dBearing);

    if(dDistItem1<dDistItem2)
        return -1;
    else if(dDistItem1>dDistItem2)
        return 1;
    else
        return 0;
}

void QPOIDatabase::DeleteAllInfo(void)
{
    for(int i=0; i < m_ItemCount; i++)
    {
		if(m_pItemArray[i])
		{
			delete m_pItemArray[i];
			m_pItemArray[i] = NULL;
		}
    }
    m_ItemCount = 0;
}

bool QPOIDatabase::DeleteItem(int index, bool bDoSort)
{
    if(m_ItemCount > index)	//means contact exist
    {
        delete m_pItemArray[index];
        m_pItemArray[index] = NULL;
        m_pItemArray[index] = m_pItemArray[m_ItemCount-1];
        m_pItemArray[m_ItemCount-1] = NULL;
        m_ItemCount--;
        if(bDoSort)
        {
            SortItemArray();
        }
        return true;
    }
    return false;
}

ORDER_TYPE QPOIDatabase::GetOrderType(void)
{
    return m_OrderType;
}

void QPOIDatabase::SetOrderType(ORDER_TYPE OrderType)
{
    if(m_OrderType != OrderType)
    {
            m_OrderType = OrderType;
            SortItemArray();
    }
}

bool  QPOIDatabase::GetDistance(int index,double dCurLong, double dCurLat, int iUnitType, double& dDistance,double& dBearing)
{
    bool ret = false;
    if((index < m_ItemCount)&&(index >= 0))
    {
        m_pItemArray[index]->GetDistance(dCurLong,dCurLat,iUnitType,dDistance,dBearing);
        ret = true;
    }

    return ret;
}
