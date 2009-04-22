#pragma once

#include <uf_curve.h>
#include "postug.h"
#include "SKETCHItem.h"
#include "Definition.h"

class FSketch;

//!	SKETCHCreate2DCircleCenterPoint class
/*!
	Circle with radius and center point
*/

class SKETCHCreate2DCircleCenterPoint :
	public SKETCHItem
{
public:
	// constructor
	SKETCHCreate2DCircleCenterPoint(FSketch* pFSketch, TransCAD::IStdSketchGeometryPtr spItem);
	// destructor
	virtual ~SKETCHCreate2DCircleCenterPoint(void);

	virtual void GetInfo();
	virtual void ToUG();

public:
	UF_CURVE_arc_t _ugCircle;
};
