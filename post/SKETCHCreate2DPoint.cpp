#include ".\SKETCHCreate2DPoint.h"

#include "Part.h"
#include "FSketch.h"

SKETCHCreate2DPoint::SKETCHCreate2DPoint(FSketch * pFSketch, TransCAD::IStdSketchGeometryPtr spItem)
	: SKETCHItem(pFSketch, spItem)
{
}

SKETCHCreate2DPoint::~SKETCHCreate2DPoint(void)
{
}

void SKETCHCreate2DPoint::GetInfo()
{
	// not used yet
}
void SKETCHCreate2DPoint::ToUG()
{
	// not used yet
}