#include ".\SKETCHCreate2DArcCenterEnds.h"

#include <iostream>

#include <uf_sket.h>
#include <uf_modl.h>
#include <uf_csys.h>
#include <uf_mtx.h>

#include "FSketch.h"

SKETCHCreate2DArcCenterEnds::SKETCHCreate2DArcCenterEnds(FSketch* pFSketch, TransCAD::IStdSketchGeometryPtr spItem)
	: SKETCHItem (pFSketch, spItem)
{
}

SKETCHCreate2DArcCenterEnds::~SKETCHCreate2DArcCenterEnds(void)
{
}

void SKETCHCreate2DArcCenterEnds::GetInfo()
{
	TransCAD::IStdSketchCircularArcPtr spItem = GetTransCADGeometryItem();

	_ugCircularArc.arc_center[0] = spItem->CenterPoint->X;
	_ugCircularArc.arc_center[1] = spItem->CenterPoint->Y;
	_ugCircularArc.arc_center[2] = 0;
	// UF_CALL(UF_CURVE_ask_arc_data( GetFeatureTag(), &_ugCircularArc ) );
	_ugCircularArc.radius=spItem->Radius;
	_ugCircularArc.start_angle = spItem->StartAngle;
	_ugCircularArc.end_angle = spItem->EndAngle;
	cout << "    start angle : " << spItem->StartAngle * 180/PI << endl;
	cout << "    end   angle : " << spItem->EndAngle * 180/PI<< endl;
	if (_ugCircularArc.start_angle > _ugCircularArc.end_angle )
		_ugCircularArc.end_angle += PI*2;
	double sx = _ugCircularArc.arc_center[0] * cos(spItem->StartAngle);
	double sy = _ugCircularArc.arc_center[1] * sin(spItem->StartAngle);
	double ex = _ugCircularArc.arc_center[0] * cos(spItem->EndAngle);
	double ey = _ugCircularArc.arc_center[1] * sin(spItem->EndAngle);
	_startPoint.SetXYZ(sx,sy,0);
	_endPoint.SetXYZ(ex,ey,0);
}

void SKETCHCreate2DArcCenterEnds::ToUG()
{
	tag_t wcs_tag, matrix_id;
	double origin[3],mtx[9],transpose_mtx[9];
	UF_CSYS_ask_wcs(&wcs_tag);
	UF_CSYS_ask_csys_info(wcs_tag,&matrix_id,origin);
	UF_CSYS_ask_matrix_values(matrix_id,mtx);
	UF_MTX3_transpose(mtx,transpose_mtx);
	UF_MTX3_vec_multiply(_ugCircularArc.arc_center,transpose_mtx,_ugCircularArc.arc_center);

	_ugCircularArc.arc_center[0]+=origin[0];
	_ugCircularArc.arc_center[1]+=origin[1];
	_ugCircularArc.arc_center[2]+=origin[2];

	//UF_MTX3_vec_multiply(origin,transpose_mtx,origin);
	UF_CSYS_ask_matrix_of_object(wcs_tag,&_ugCircularArc.matrix_tag);	
	UF_MTX3_vec_multiply(_ugCircularArc.arc_center,mtx,_ugCircularArc.arc_center);

	UF_CURVE_create_arc(&_ugCircularArc,&_ugTag);
	UF_SKET_add_objects(GetFeatureSketch()->GetSketchTag(), 1, &_ugTag);
	UF_MODL_put_list_item(GetFeatureSketch()->_ugObjectsList, _ugTag);
	cout << "    SKETCHCreate2DArcCenterEnds " << GetSketchItemName() << endl;
}