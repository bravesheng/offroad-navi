#include "GadgetSlot.h"
#include "Gadget.h"

CGadgetSlot::CGadgetSlot()
: pGadget(NULL),
ArrayX(NULL),
ArrayY(NULL)
{

}

void CGadgetSlot::UpdateGadgetPosition(void)
{
    if(pGadget)
    {
        pGadget->move(Geometry.x(), Geometry.y());
    }
}

bool CGadgetSlot::IfCoordinateInArea(int x, int y)
{
    return Geometry.contains(x,y);
}

bool CGadgetSlot::AssignGadget(CGadget* item)
{
    if(!pGadget)    //if this slot already have gadget?
    {
        //if all candidate slot is empty.
        pGadget = item;
        return true;
    }
    return false;
}

void CGadgetSlot::RemoveGadget(void)
{
    pGadget = NULL;
}

CGadget* CGadgetSlot::GetGadget(void)
{
    return pGadget;
}
