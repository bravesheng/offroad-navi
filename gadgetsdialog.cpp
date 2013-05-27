#include "gadgetsdialog.h"
#include <QPainter>
#include "StdGadgets.h"
#include "ImagePool.h"

CGadgetsDialog::CGadgetsDialog(QWidget *parent, int mode)
: QWidget(parent),
ReturnBtn(this),
m_GadgetListBar(this),
m_UpdateTimer(this),
m_UpdateTimerTickCount(0),
LayoutMode(mode)
{
	m_GadgetListBar.raise();
    setGeometry(QRect(0, 0, 320, 240));
    PrepareSlotsCoordinate();

	if(LayoutMode == TRIP_COMPUTER_MODE)
	{
		AddGadget(GADGET_ELEVATION);
		AddGadget(GADGET_SPEED);
		AddGadget(GADGET_ODOMETR);
		AddGadget(GADGET_LOCATION);
		AddGadget(GADGET_HEART_RATE);
	}
	else if(LayoutMode == COMPASS_MODE)
	{
		AddGadget(GADGET_ELEVATION);
		AddGadget(GADGET_BIG_COMPASS);
		AddGadget(GADGET_TIME_OF_DAY);
	}
	else
	{
		AddGadget(GADGET_ELEVATION);
		AddGadget(GADGET_CADENCE);
		AddGadget(GADGET_POINTER);
		AddGadget(GADGET_ELEVATION_PLOT);
	}
	//prepare update timer for update per 1 second
    connect(&m_UpdateTimer, SIGNAL(timeout()), SLOT(UpdateGadgets()));
    m_UpdateTimer.start(1000);
}

CGadgetsDialog::~CGadgetsDialog()
{
    //clean up pMyGadget
	while(!GadgetList.isEmpty())
	{
		delete GadgetList.takeFirst();
	}
}

void CGadgetsDialog::UpdateGadgets(void)
{
	for(int i=0; i < GadgetList.count(); i++)
    {
		CGadget* pGadget = GadgetList.at(i);
		if(pGadget != NULL)
        {
			pGadget->UpdateInfo(m_UpdateTimerTickCount++);
        }
    }
}

void CGadgetsDialog::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    painter.drawPixmap(0, 0, 320, 240, *GetImg(IMG_BACKGROUND_STD));
}

bool CGadgetsDialog::InsertGadgetIntoSlot(CGadget* pGadget)
{
	for(int j=0; j < SLOT_NUMS_Y; j++)
	{
		for(int i=0; i < SLOT_NUMS_X; i++)
		{
			if(InsertGadgetIntoSlot(pGadget, &SlotArray[i][j]))	//insert success
			{
				return true;
			}
		}
	}
	return false;
}

/* There are some case when drop gadget.
1. Drop in empty slot. Will cause this gadget in new position.
2. Drop in original slot. Will cause this gadget in stick in original position.
3. Drop in gadget-existed slot. Will cause this gadget go back to original slot.
4. Drop in area that out of slots area. Will go back to oroginal slot.
5. Drop in trash can area. Will delete this gadget.
*/
bool CGadgetsDialog::DropGadget(CGadget* pGadget, int x, int y)
{
    CGadgetSlot* pTargetSlot = CoordinateToSlot(x, y);
	if(IfTrashCanArea(x,y))	//if in trash can area
	{
		DeleteGadget(pGadget);
	}
	else if(pTargetSlot)	//means drop position on a slot area.
	{
		return InsertGadgetIntoSlot(pGadget, pTargetSlot);
	}
	else	//if in no-meaning area
	{
		pGadget->pCurrentSlot->UpdateGadgetPosition();
	}
	return false;
}

bool CGadgetsDialog::IfTrashCanArea(int x, int y)
{
	return m_GadgetListBar.IfTabArea(x,y);
}

bool CGadgetsDialog::DeleteGadget(CGadget* pGadget)
{
	if(pGadget)
	{
		GadgetList.removeAt(GadgetList.indexOf(pGadget));
		RemoveGadgetFromCurrentSlot(pGadget);
		delete pGadget;
		return true;
	}
	return false;
}

bool CGadgetsDialog::RemoveGadgetFromCurrentSlot(CGadget* pGadget)
{
	CGadgetSlot* pCurrentSlot = pGadget->pCurrentSlot;
	if(pGadget->pCurrentSlot)
	{
		pGadget->pCurrentSlot = NULL;
		for(int i=0; i < pGadget->WidthSlotNums; i++)
		{
			for(int j=0; j < pGadget->HeightSlotNums; j++)
			{
				//remove Gadget to let follow indicate code can work correctly.
				int RemoveX = pCurrentSlot->ArrayX + i;
				int RemoveY = pCurrentSlot->ArrayY + j;
				SlotArray[RemoveX][RemoveY].RemoveGadget();
			}
		}
		return true;
	}
	return false;
}


bool CGadgetsDialog::InsertGadgetIntoSlot(CGadget* pGadget, CGadgetSlot* pTargetSlot)
{
	CGadgetSlot* pCurrentSlot = pGadget->pCurrentSlot;
    if(pTargetSlot) //means we are under one of slot
    {
		if(pCurrentSlot != pTargetSlot)
		{
			RemoveGadgetFromCurrentSlot(pGadget);
			//indicate if area available
			for(int i=0; i < pGadget->WidthSlotNums; i++)
			{
				for(int j=0; j < pGadget->HeightSlotNums; j++)
				{
					int CheckX = pTargetSlot->ArrayX + i;	//Array X prepare for check
					int CheckY = pTargetSlot->ArrayY + j;	//Array Y prepare for check
					if((CheckX >= SLOT_NUMS_X) || (CheckY >= SLOT_NUMS_Y))
					{
						pGadget->pCurrentSlot = pCurrentSlot;	//Rollback original position
						goto SETUP_POSITION;
					}
					if(CheckX < SLOT_NUMS_X)	//Array X not out of range.
					{
						if(CheckY < SLOT_NUMS_Y)	//Array Y not out of range.
						{
							if(SlotArray[CheckX][CheckY].GetGadget())	//means this slot is NOT empty
							{
								pGadget->pCurrentSlot = pCurrentSlot;	//Rollback original position
								goto SETUP_POSITION;
							}
						}
					}
				}
			}
			pGadget->pCurrentSlot = pTargetSlot;	//start transfer to new slots
SETUP_POSITION:
			if(pGadget->pCurrentSlot)	
			{
				for(int i=0; i < pGadget->WidthSlotNums; i++)
				{
					for(int j=0; j < pGadget->HeightSlotNums; j++)
					{
						//remove Gadget to let follow indicate code can work correctly.
						int AddX = pGadget->pCurrentSlot->ArrayX + i;
						int AddY = pGadget->pCurrentSlot->ArrayY + j;
						SlotArray[AddX][AddY].AssignGadget(pGadget);
					}
				}
				
			}
		}
		else	//target slot is same as current slot
		{

		}
		if(pGadget->pCurrentSlot)
		{
			pGadget->pCurrentSlot->UpdateGadgetPosition();
			return true;	//return true means gadget find slot suitable for it.
		}
    }
	return false; //return false means gadget can not have slot.
}

void CGadgetsDialog::PrepareSlotsCoordinate(void)
{
	int X;
	int Y;
	//prepare coordinate and relationship
	for(X=0; X < SLOT_NUMS_X; X++)
	{
		for(Y=0; Y < SLOT_NUMS_Y; Y++)
		{
			//coordinate
			SlotArray[X][Y].Geometry.setRect(10 + 100 * X, 35 + 100 * Y, 100, 100);
			//location in slot array
			SlotArray[X][Y].ArrayX = X;
			SlotArray[X][Y].ArrayY = Y;
		}
    }
}

CGadgetSlot* CGadgetsDialog::CoordinateToSlot(int x, int y)
{
    for(int i=0; i < SLOT_NUMS; i++)
    {
        if(SlotArray[i % SLOT_NUMS_X][i / SLOT_NUMS_X].IfCoordinateInArea(x,y))
        {
            return &SlotArray[i % SLOT_NUMS_X][i / SLOT_NUMS_X];
        }
    }
    return NULL;
}

bool CGadgetsDialog::AddGadget(GADGET_UNIT GadgetType)
{
	CGadget* pGadget;
	switch(GadgetType)
	{
	case GADGET_LOCATION:
		pGadget = new CGadgetLocation(this);
		break;
	case GADGET_SPEED:
		pGadget = new CGadgetSpeed(this);
		break;
	case GADGET_TIME_OF_DAY:
		pGadget = new CGadgetTimeOfDay(this);
		break;
	case GADGET_ODOMETR:
		pGadget = new CGadgetOdometer(this);
		break;
	case GADGET_ELEVATION:
		pGadget = new CGadgetElevation(this);
		break;
	case GADGET_POINTER:
		pGadget = new CGadgetPointer(this);
		break;
	case GADGET_BIG_COMPASS:
		pGadget = new CGadgetBigCompass(this);
		break;
	case GADGET_GPS_SIGNAL_SMALL:
		pGadget = new CGadgetGpsSignalSmall(this);
		break;
	case GADGET_ELEVATION_PLOT:
		pGadget = new CGadgetElevationPlot(this);
		break;
	case GADGET_HEART_RATE:
		pGadget = new CGadgetHeartRate(this);
		break;
	case GADGET_CADENCE:
		pGadget = new CGadgetCadence(this);
		break;
	case GADGET_VERTICAL_SPEED:
		pGadget = new CGadgetVerticalSpeed(this);
		break;
	case GADGET_TRIP_ELEVATION:
		pGadget = new CGadgetTripElevation(this);
		break;
	case GADGET_BATTERY_LEVEL:
		pGadget = new CGadgetBatteryLevel(this);
		break;
	case GADGET_HEADING:
		pGadget = new CGadgetHeading(this);
		break;
	case GADGET_ACCURACY_GPS:
		pGadget = new CGadgetAccuracyGps(this);
		break;
	case GADGET_SPEED_OVERALL_AVG:
		pGadget = new CGadgetSpeedOverallAvg(this);
		break;
	case GADGET_TRIP_TIME_TOTAL:
		pGadget = new CGadgetTripTimeTotal(this);
		break;
	case GADGET_TRIP_TIME_STOPPING:
		pGadget = new CGadgetTripTimeStopping(this);
		break;
	case GADGET_SPEED_MOVING_AVG:
		pGadget = new CGadgetSpeedMovingAvg(this);
		break;
	case GADGET_TRIP_TIME_MOVING:
		pGadget = new CGadgetTripTimeMoving(this);
		break;
	case GADGET_TRIP_ODOMETER:
		pGadget = new CGadgetTripOdometer(this);
		break;
	case GADGET_SPEED_MAX:
		pGadget = new CGadgetSpeedMaximum(this);
		break;
	case GADGET_BEARING:
		pGadget = new CGadgetBearing(this);
		break;
	case GADGET_WPT_AT_NEXT:
		pGadget = new CGadgetWaypointAtNext(this);
		break;
	case GADGET_ETA_AT_NEXT:
		pGadget = new CGadgetEtaAtNext(this);
		break;
	case GADGET_DST_TO_NEXT:
		pGadget = new CGadgetDistanceToNext(this);
		break;
	case GADGET_TIME_TO_NEXT:
		pGadget = new CGadgetTimeToNext(this);
		break;
	case GADGET_WPT_AT_DST:
		pGadget = new CGadgetWaypointAtDest(this);
		break;
	case GADGET_DISTANCE_TO_DST:
		pGadget = new CGadgetDistanceToDest(this);
		break;
	case GADGET_ETA_AT_DST:
		pGadget = new CGadgetEtaAtDest(this);
		break;
	case GADGET_TIME_TO_DST:
		pGadget = new CGadgetTimeToDest(this);
		break;
	case GADGET_COURSE:
		pGadget = new CGadgetCourse(this);
		break;
	case GADGET_TO_COURSE:
		pGadget = new CGadgetToCourse(this);
		break;
	case GADGET_OFF_COURSE:
		pGadget = new CGadgetOffCourse(this);
		break;
	}
	if(InsertGadgetIntoSlot(pGadget))
	{
		GadgetList.append(pGadget);
		if(pGadget)
		{
			pGadget->UpdateInfo(m_UpdateTimerTickCount);
			pGadget->show();
			return true;
		}
	}
	//else
	delete pGadget;
	return false;
}
