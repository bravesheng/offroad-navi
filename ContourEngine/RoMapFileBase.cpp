#include "stdafx.h"
#include "RoMapFileBase.h"

int CRoMapFileBase::m_iGridWidth = 1000;
int CRoMapFileBase::m_iMeshWidth = 10000;
int CRoMapFileBase::m_iGridNum = 1;

void CRoMapFileBase :: CalcGridNum ()
{
    if (( m_iGridWidth == 0 ) || ( m_iMeshWidth == 0 ))
        return;

    m_iGridNum = ( m_iMeshWidth + m_iGridWidth - 1 ) / m_iGridWidth;
}

void CRoMapFileBase :: ExpandToMesh ()
{
    if ( _iXMin % MeshWidth () == ( MeshWidth () - 1 ))
        _iXMin++;
    else
        _iXMin -= _iXMin % MeshWidth ();
    
    if ( _iYMin % MeshWidth () == ( MeshWidth () - 1 ))
        _iYMin++;
    else
        _iYMin -= _iYMin % MeshWidth ();

    if ( _iXMax % MeshWidth ())
        _iXMax = _iXMax - ( _iXMax % MeshWidth ()) + MeshWidth ();

    if ( _iYMax % MeshWidth ())
        _iYMax = _iYMax - ( _iYMax % MeshWidth ()) + MeshWidth ();
}
