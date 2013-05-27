#include <QtGui/QApplication>
#include "MainWindow.h"
#include "AnalyzingThread.h"
#include "TrackList.h"
#include "RdGuideEngine.h"
#include "RdTripComputer.h"

CTrackList g_TrackList;
CTripComputer g_TripComputer;
CGuideEngine g_Guide;

//For OnRoad/OffRoad switch
#define		WM_NAVI_BASE 				WM_APP + 0x1300
#define		WM_NAVI_SWITCH_SCREEN		WM_NAVI_BASE + 0x01
#define		WM_NAVI_DST_UPDATED			WM_NAVI_BASE + 0x02
#define		WM_NAVI_RTE_UPDATED			WM_NAVI_BASE + 0x03
#define		WM_NAVI_WPT_UPDATED			WM_NAVI_BASE + 0x04

class QMyApplication: public QApplication
{
public:
	QMyApplication(int argc, char *argv[]);	
	bool winEventFilter (MSG *msg, long * result);
	CAnalyzingThread m_AnalyzingThread;
}; 

QMyApplication::QMyApplication(int argc, char *argv[])
:QApplication(argc, argv)
{

}

//---	winEventFilter
bool QMyApplication::winEventFilter ( MSG *msg, long *result)
{
	switch (msg->message)
	{
	case WM_NAVI_SWITCH_SCREEN:
		{
			QWidget* main_window = new CMainWindow;
			*result = 1;
			if( 0 == msg->wParam)
			{
				qDebug() << "Hide all screen";			
				main_window->hide();
			}
			else if( 1 == msg->wParam)
			{
				qDebug() << "Get Navi Change MSG, WP:1, hide OffRoad";				
				main_window->hide();
			}
			else if( 2 == msg->wParam)
			{
				qDebug() << "Get Navi Change MSG, WP:2, show OffRoad";
				main_window->show();
			}
			return true;
		}
		break;	
	case WM_NAVI_DST_UPDATED:
		{
			qDebug() << "Get DST Update MSG" ;
			*result = 1;
			return true;			
		}
		break;
	case WM_NAVI_RTE_UPDATED:
		{
			qDebug() << "Get RTE Update MSG";
			*result = 1;
			return true;			
		}
		break;
	case WM_NAVI_WPT_UPDATED:
		{
			qDebug() << "Get WPT Update MSG";
			*result = 1;
			return true;		
		}
		break;
	default:
		{
			*result = 0;
			QString strmsg;
			strmsg.sprintf("%d", msg->message);
			//qDebug() << strmsg;
			return false;
		}
		break;
	}		
	//return QApplication::winEventFilter( msg, result);
}

int main(int argc, char *argv[])
{
	QMyApplication a(argc, argv);
    PrepareImagePool();
    InitializeHardwareSensor();
	QWidget* main_window = new CMainWindow;
	main_window->show();
	a.m_AnalyzingThread.start();

	int ApResult = a.exec();
	a.m_AnalyzingThread.quit();
	UninitializeHardwareSensor();
	ReleaseImagePool();
    return ApResult;
}
