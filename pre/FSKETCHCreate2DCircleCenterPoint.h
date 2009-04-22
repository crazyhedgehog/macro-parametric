#pragma once

#include "Feature.h"

class Part;
class FSketch;

//!	FSKETCHCreate2DLine2Points class
/*!
	2D Line class with two 2DPoint structs
*/

class FSKETCHCreate2DCircleCenterPoint :
	public Feature
{
public:

	FSKETCHCreate2DCircleCenterPoint(Part * part, tag_t fTag, FSketch * pFSketch);
	virtual ~FSKETCHCreate2DCircleCenterPoint(void);

	void SetCntPnt(const Point3D & cP) {_cP = cP;}
	void SetRadius(const double dR) {_dR = dR;}
	
	FSketch * GetFSketch() {return _pFSketch;}
	void GetCntPnt(Point3D & cP) {cP = _cP;}
	double GetRadius() const {return _dR;}
	
	virtual void GetUGInfo();
	virtual void ToTransCAD();

private:
	static int _circle2DCPCnt;

	Point3D		_cP;
    double		_dR;
	FSketch *	_pFSketch;
};
