#pragma once

#include <uf_curve.h>

#include ".\postug.h"
#include "SKETCHItem.h"
#include "Definition.h"

class FSketch;

//!	SKETCHCreate2DLine2Points class
/*!
	2D Line class with two 2DPoint structs
*/
class SKETCHCreate2DLine2Points : public SKETCHItem
{
public:

	// A constructor
	SKETCHCreate2DLine2Points(FSketch * pFSketch, TransCAD::IStdSketchGeometryPtr spItem);
	// A Desturctor
	virtual ~SKETCHCreate2DLine2Points(void);

	void SetStartPoint(const Point3D & startPoint) {_startPoint = startPoint;}
	void SetEndPoint(const Point3D & endPoint) {_endPoint = endPoint;}

	void GetStartPoint(Point3D & startPoint) {startPoint = _startPoint;}
	void GetEndPoint(Point3D & endPoint) {endPoint = _endPoint;}
	void GetPickingPoint(Point3D & pickPnt) {pickPnt = (_startPoint+_endPoint)*0.5;}

	virtual void GetInfo();
	virtual void ToUG();
	

public:
	UF_CURVE_line_t _ugLine;

private:
	Point3D _startPoint;
	Point3D _endPoint;
};
