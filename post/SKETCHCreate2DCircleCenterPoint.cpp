#include ".\SKETCHCreate2DCircleCenterPoint.h"

#include <iostream>

#include <uf_sket.h>
#include <uf_modl.h>
#include <uf_csys.h>
#include <uf_mtx.h>

#include "FSketch.h"

SKETCHCreate2DCircleCenterPoint::SKETCHCreate2DCircleCenterPoint(FSketch* pFSketch, TransCAD::IStdSketchGeometryPtr spItem)
	: SKETCHItem (pFSketch, spItem)
{
}

SKETCHCreate2DCircleCenterPoint::~SKETCHCreate2DCircleCenterPoint(void)
{
}

void SKETCHCreate2DCircleCenterPoint::GetInfo()
{
	TransCAD::IStdSketchCirclePtr spItem = GetTransCADGeometryItem();

	_ugCircle.arc_center[0]=spItem->CenterPoint->X;
	_ugCircle.arc_center[1]=spItem->CenterPoint->Y;
	_ugCircle.arc_center[2]=0;
	_ugCircle.radius=spItem->Radius;

	_ugCircle.start_angle = 0.0;
	_ugCircle.end_angle = 360.0*DEGRA;
}

void SKETCHCreate2DCircleCenterPoint::ToUG()
{
	tag_t wcs_tag, matrix_id;
	double origin[3],mtx[9],transpose_mtx[9];
	UF_CSYS_ask_wcs(&wcs_tag);
	UF_CSYS_ask_csys_info(wcs_tag,&matrix_id,origin);
	UF_CSYS_ask_matrix_values(matrix_id,mtx);
	UF_MTX3_transpose(mtx,transpose_mtx);
	UF_MTX3_vec_multiply(_ugCircle.arc_center,transpose_mtx,_ugCircle.arc_center);

	_ugCircle.arc_center[0]+=origin[0];
	_ugCircle.arc_center[1]+=origin[1];
	_ugCircle.arc_center[2]+=origin[2];
	//UF_MTX3_vec_multiply(origin,transpose_mtx,origin);

	UF_CSYS_ask_matrix_of_object(wcs_tag,&_ugCircle.matrix_tag);	
	UF_MTX3_vec_multiply(_ugCircle.arc_center,mtx,_ugCircle.arc_center);

	UF_CURVE_create_arc(&_ugCircle,&_ugTag);
	UF_SKET_add_objects(GetFeatureSketch()->GetSketchTag(), 1, &_ugTag);
	UF_MODL_put_list_item(GetFeatureSketch()->_ugObjectsList, _ugTag);
	cout << "    SKETCHCreate2DCircleCenterPoint " << GetSketchItemName() << endl;	
}