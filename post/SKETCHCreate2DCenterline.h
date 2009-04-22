#pragma once

#include <uf_curve.h>

#include ".\postug.h"
#include "SKETCHItem.h"
#include "Definition.h"

class FSketch;

//!	SKETCHCreate2DCenterline class
/*!
	2D Line class with two 2DPoint structs
*/
class SKETCHCreate2DCenterline : public SKETCHItem
{
public:

	// A constructor
	SKETCHCreate2DCenterline(FSketch * pFSketch, TransCAD::IStdSketchGeometryPtr spItem);
	// A Desturctor
	virtual ~SKETCHCreate2DCenterline(void);

	virtual void GetInfo();
	virtual void ToUG();

public:
	UF_CURVE_line_t _ugLine;
};
