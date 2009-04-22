#pragma once

#include <uf_curve.h>
#include "postug.h"
#include "SKETCHItem.h"
#include "Definition.h"

class FSketch;

class SKETCHCreate2DArcCenterEnds :
	public SKETCHItem
{
public:
	SKETCHCreate2DArcCenterEnds(FSketch* pFSketch, TransCAD::IStdSketchGeometryPtr spItem);
	
	virtual ~SKETCHCreate2DArcCenterEnds(void);

	void SetStartPoint(const Point3D& sP) {_startPoint=sP;}
	void SetEndPoint(const Point3D& eP) {_endPoint=eP;}
	
	void GetStartPoint(Point3D& sP) {sP=_startPoint;}
	void GetEndPoint(Point3D& eP) {eP=_endPoint;}

	virtual void GetInfo();
	virtual void ToUG();

public:
	UF_CURVE_arc_t _ugCircularArc;

private:
	static int _arc2DCenterEnds;

	Point3D _startPoint;
	Point3D _endPoint;
};
