#include ".\SKETCHCreate2DCenterline.h"

#include <iostream>

#include <uf_sket.h>
#include <uf_modl.h>
#include <uf_csys.h>
#include <uf_mtx.h>

#include "FSketch.h"

using namespace std;

SKETCHCreate2DCenterline::SKETCHCreate2DCenterline(FSketch * pFSketch, TransCAD::IStdSketchGeometryPtr spItem)
	: SKETCHItem(pFSketch, spItem)
{
}

SKETCHCreate2DCenterline::~SKETCHCreate2DCenterline(void)
{
}

void SKETCHCreate2DCenterline::GetInfo()
{
	// Cast --> TransCAD::IStdSketchLinePtr
	TransCAD::IStdSketchCenterlinePtr spItem = GetTransCADGeometryItem();

	_ugLine.start_point[0] = spItem->StartPoint->X;
	_ugLine.start_point[1] = spItem->StartPoint->Y;
	_ugLine.start_point[2] = 0;

	_ugLine.end_point[0] = spItem->EndPoint->X;
	_ugLine.end_point[1] = spItem->EndPoint->Y;
	_ugLine.end_point[2] = 0;
}

void SKETCHCreate2DCenterline::ToUG()
{
	UF_CSYS_map_point(UF_CSYS_ROOT_WCS_COORDS,_ugLine.start_point,UF_CSYS_WORK_COORDS,_ugLine.start_point);
	UF_CSYS_map_point(UF_CSYS_ROOT_WCS_COORDS,_ugLine.end_point,UF_CSYS_WORK_COORDS,_ugLine.end_point);

	cout << "    SKETCHCreate2DCenterline " << GetSketchItemName() << endl;
}