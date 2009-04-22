#pragma once

#include "UGPre.h"
#include "Feature.h"

class Part;
class FSketch;


//!	FSKETCHCreate2DPoint class
/*!
	2D point class applicable to 3D point
*/
class FSKETCHCreate2DPoint : public Feature
{

public:

	FSKETCHCreate2DPoint(Part * part, tag_t fTag, FSketch * pFSketch);
	virtual ~FSKETCHCreate2DPoint(void);

	void SetPoint(const Point3D & point);
	void GetPoint(Point3D & point);

	virtual void GetUGInfo();
	virtual void ToTransCAD();

private:
	Point3D _point;
	Feature * _pFSketch;
};
