#include "SettingLog.h"
#include <QDataStream>

QDataStream &operator<<(QDataStream &out, CSetting &setting)
{
	out << setting.GetUnit() << setting.GetCandenceEnable() << setting.GetHeartRateEnable();
	return out;
}

QDataStream &operator>>(QDataStream &in, CSetting &setting)
{
	qint8 iUnit = 0;
	qint8 iCandence = 0;
	qint8 iHeartRate = 0;

	in >> iUnit >> iCandence >> iHeartRate;

	setting.SetUnit(iUnit);
	setting.SetCandenceEnable(iCandence);
	setting.SetHeartRateEnable(iHeartRate);

	return in;
}

CSetting::CSetting(const CSetting& Rhs)
{
	m_iUnit = Rhs.m_iUnit;
	m_iCandenceEnable = Rhs.m_iCandenceEnable;
	m_iHeartRateEnable = Rhs.m_iHeartRateEnable;
}

CSetting& CSetting::operator=(const CSetting& Rhs)
{
	if(this == &Rhs)
	{
		return *this;
	}
	m_iUnit = Rhs.m_iUnit;
	m_iCandenceEnable = Rhs.m_iCandenceEnable;
	m_iHeartRateEnable = Rhs.m_iHeartRateEnable;
			
	return *this;
}

CSetting::CSetting()
{
    ResetData();
}

void CSetting::ResetData()
{
    m_iUnit = UNIT_METRIC;
	m_iCandenceEnable = CANDENCE_OFF;
	m_iHeartRateEnable = HEART_RATE_OFF;
}

bool CSetting::SetUnit(qint8 iUint)
{
    if(iUint < UNIT_MAX_NUM)
    {
        m_iUnit  = iUint;
        return true;
    }
    m_iUnit = UNIT_METRIC;
    return false;
}

bool CSetting::SetCandenceEnable(qint8 iCandenceEnable)
{
    if(iCandenceEnable < CANDENCE_MAX_NUM)
    {
		m_iCandenceEnable = iCandenceEnable;
        return true;
    }
	m_iCandenceEnable = CANDENCE_OFF;
    return false;
}

bool CSetting::SetHeartRateEnable(qint8 iHeartEnable)
{
    if(iHeartEnable < HEART_RATE_MAX_NUM)
    {
		m_iHeartRateEnable = iHeartEnable;
        return true;
    }
	m_iHeartRateEnable = HEART_RATE_OFF;
    return false;
}


//Setting Log Class============================================================
const QString g_strSetting_Path	      ("\\ShellDisk\\Shell\\OffRoadNavi\\data\\Setting.dat");

SettingLog::SettingLog()
{
	Log.setFileName(g_strSetting_Path);
}

bool SettingLog::SetSettingValue(CSetting& Setting)
{
	Log.open(QIODevice::WriteOnly | QIODevice::Truncate);
	QDataStream out(&Log);
	out << Setting;							

	Log.close();
	return true;
}

bool SettingLog::GetSettingValue(CSetting& Setting)
{
	bool bRet = false;
	bool bSetDefault = false;

	if(!Log.exists())
		bSetDefault = true;


	if(!bSetDefault)
	{
		if(Log.open(QIODevice::ReadOnly))
		{	
			QDataStream in(&Log);	
			in >> Setting;

			Log.close();
			bRet = true;
		}
		else
		{
			bSetDefault = true;
		}
	}

	if(bSetDefault)
	{
		Setting.ResetData();
		SetSettingValue(Setting);
	}

	return bRet;
}