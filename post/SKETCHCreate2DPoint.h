#pragma once

#include "postug.h"
#include "SKETCHItem.h"
#include "Definition.h"

class FSketch;

class SKETCHCreate2DPoint : public SKETCHItem
{

public:
	// constructor
	SKETCHCreate2DPoint(FSketch * pFSketch, TransCAD::IStdSketchGeometryPtr spItem);
	// destructor
	virtual ~SKETCHCreate2DPoint(void);

	void SetPoint(const Point3D & point) { _point = point; }
	void GetPoint(Point3D & point) { point = _point; }
	double X() { return _point.X(); }
	double Y() { return _point.Y(); }

	virtual void GetInfo();
	virtual void ToUG();

private:
	Point3D _point;
};
