#ifndef Setting_LOG_H
#define Setting_LOG_H
#include <QFile>

using namespace std;
class CSetting
{
public:
    enum UNIT
    {
        UNIT_STATUTE = 0,    //MI,
        UNIT_METRIC,
        UNIT_YARDS,
        UNIT_MAX_NUM
    };

	enum CANDENCE
	{
		CANDENCE_OFF = 0,
		CANDENCE_ON,
		CANDENCE_MAX_NUM
	};

	enum HEART_RATE
	{
		HEART_RATE_OFF = 0,
		HEART_RATE_ON,
		HEART_RATE_MAX_NUM
	};

	CSetting(const CSetting& Rhs);
	CSetting& operator=(const CSetting& Rhs);
    CSetting();

        void ResetData();
		qint8 GetUnit()	{return m_iUnit;}
        bool SetUnit(qint8 iUint);
		qint8 GetCandenceEnable() {return m_iCandenceEnable;}
		bool SetCandenceEnable(qint8 iCandenceEnable);
		qint8 GetHeartRateEnable() {return m_iHeartRateEnable;}
		bool SetHeartRateEnable(qint8 iHeartEnable);
private:
    qint8   m_iUnit;
	qint8   m_iCandenceEnable;
	qint8   m_iHeartRateEnable;
};

class SettingLog
{
public:
	SettingLog();
	bool SetSettingValue(CSetting& Setting);
	bool GetSettingValue(CSetting& Setting);
private:
	QFile	Log;
};
#endif // Setting_H
