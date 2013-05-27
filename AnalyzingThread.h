#ifndef ANALYZING_THREAD_H
#define ANALYZING_THREAD_H

#include <QThread>
#include <QTimer>

class CAnalyzingThread : public QThread
{
	Q_OBJECT
public:
	virtual void run(void);
public slots:
	void OneSecondUpdate(void);
private:
	QTimer* m_pTimerOneSec;
};

#endif//ANALYZING_THREAD_H