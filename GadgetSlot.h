#ifndef CGADGETSLOT_H
#define CGADGETSLOT_H

#include <QWidget>
class CGadget;

class CGadgetSlot
{
public:
    CGadgetSlot();
    QRect Geometry; //coordinate about this slot.
    bool IfCoordinateInArea(int x, int y); //detect x y coordinate is in this slot's area
    void UpdateGadgetPosition(void);
    bool AssignGadget(CGadget* item);
    void RemoveGadget(void);
    CGadget* GetGadget(void);
	int ArrayX;
	int ArrayY;
private:
    CGadget* pGadget;  //Current Gadget in this slot
};

#endif // CGADGETSLOT_H
