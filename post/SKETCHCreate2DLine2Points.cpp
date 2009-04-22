#include ".\SKETCHCreate2DLine2Points.h"

#include <iostream>

#include <uf_sket.h>
#include <uf_modl.h>
#include <uf_csys.h>
#include <uf_mtx.h>

#include "FSketch.h"

using namespace std;

SKETCHCreate2DLine2Points::SKETCHCreate2DLine2Points(FSketch * pFSketch, TransCAD::IStdSketchGeometryPtr spItem)
	: SKETCHItem(pFSketch, spItem)
{
}

SKETCHCreate2DLine2Points::~SKETCHCreate2DLine2Points(void)
{
}

void SKETCHCreate2DLine2Points::GetInfo()
{
	TransCAD::IStdSketchLinePtr spItem = GetTransCADGeometryItem();
	SetStartPoint(Point3D(spItem->StartPoint->X, spItem->StartPoint->Y, 0));
	SetEndPoint(Point3D(spItem->EndPoint->X, spItem->EndPoint->Y, 0));
	
	for(int i=0 ; i<3 ; ++i) {
		_ugLine.start_point[i] = _startPoint[i];
		_ugLine.end_point[i] = _endPoint[i];
	}
	cout << "   Point1 : " << _startPoint[0] << " " << _startPoint[1] << " " << _startPoint[2] << endl;
	cout << "   Point2 : " << _endPoint[0] << " " << _endPoint[1] << " " << _endPoint[2] << endl;
}

void SKETCHCreate2DLine2Points::ToUG()
{
	UF_CSYS_map_point(UF_CSYS_ROOT_WCS_COORDS,_ugLine.start_point,UF_CSYS_WORK_COORDS,_ugLine.start_point);
	UF_CSYS_map_point(UF_CSYS_ROOT_WCS_COORDS,_ugLine.end_point,UF_CSYS_WORK_COORDS,_ugLine.end_point);
	UF_CURVE_create_line(&_ugLine,&_ugTag);
	UF_SKET_add_objects(GetFeatureSketch()->GetSketchTag(), 1, &_ugTag);
	UF_MODL_put_list_item(GetFeatureSketch()->_ugObjectsList, _ugTag);
	cout << "    SKETCHCreate2DLine2Points " << GetSketchItemName() << endl;
}