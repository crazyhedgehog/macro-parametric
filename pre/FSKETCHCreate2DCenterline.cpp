#include ".\FSKETCHCreate2DCenterline.h"

#include <iostream>

#include "Part.h"
#include "FSketch.h"

int FSKETCHCreate2DCenterline::_nCLineCnt = 0;

FSKETCHCreate2DCenterline::FSKETCHCreate2DCenterline(Part * part, tag_t fTag, FSketch * pFSketch)
	: Feature(part, fTag)
{
	_pFSketch = pFSketch;
}

FSKETCHCreate2DCenterline::~FSKETCHCreate2DCenterline(void)
{
}

void FSKETCHCreate2DCenterline::GetUGInfo(double pos[3], double dir[3])
{	
	UF_CURVE_line_t ugLine;
	for (int i=0; i<3; i++) 
	{
		ugLine.start_point[i] = pos[i];
		ugLine.end_point[i] = pos[i]+dir[i];
	}

	// To get sketch infomation to tranlsate from world to local coordinate
	double sketInfo[12];
	GetFSketch()->GetSketInfo(sketInfo);

	Map(sketInfo,ugLine.start_point);       // XY plane(local) 값으로 ...
	Map(sketInfo,ugLine.end_point);         // XY plane(local) 값으로 ...

	ValRndPnt(ugLine.start_point);
	ValRndPnt(ugLine.end_point);

	// To set both start and end points
	SetStaPnt(ugLine.start_point);
	SetEndPnt(ugLine.end_point);
	
	//----------  Set Result_Object_Name  ----------//
	char buffer[20];
	_itoa(_nCLineCnt ++ , buffer, 10 );
    SetName("centerline2D" + (string)buffer);
}

void FSKETCHCreate2DCenterline::ToTransCAD()
{
	// Get SketchEditorPtr
	TransCAD::ISketchEditorPtr spSketchEditor = GetFSketch()->GetSketchEditorPtr();
	// Create Centerline
	spSketchEditor->Create2DCenterline2Points(GetName().c_str(),_sP.X(),_sP.Y(),_eP.X(),_eP.Y());
	//DEBUG
	cout << "  " << GetName() << " : " << _sP.X() << " " << _sP.Y() << " " << _eP.X() << " " << _eP.Y() << endl;
}
