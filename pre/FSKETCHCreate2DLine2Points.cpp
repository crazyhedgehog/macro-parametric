#include ".\FSKETCHCreate2DLine2Points.h"

#include <iostream>

#include "Part.h"
#include "FSketch.h"

int FSKETCHCreate2DLine2Points::_nLineCnt = 0;

FSKETCHCreate2DLine2Points::FSKETCHCreate2DLine2Points(Part * part, tag_t fTag, FSketch * pFSketch) :
	Feature(part, fTag)
{
	_pFSketch = pFSketch;
}

FSKETCHCreate2DLine2Points::~FSKETCHCreate2DLine2Points(void)
{
}

void FSKETCHCreate2DLine2Points::GetUGInfo()
{
	
	// To get curve line coordinate infomation from a line object tag
	UF_CURVE_line_t ugLine;
	UF_CALL(UF_CURVE_ask_line_data( GetFTag(), &ugLine));

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
	_itoa(_nLineCnt ++ , buffer, 10 );
    SetName("line2D" + (string)buffer);
}

void FSKETCHCreate2DLine2Points::ToTransCAD()
{
	Point3D sP, eP;
	GetStaPnt(sP);
	GetEndPnt(eP);
	// Get SketchEditorPtr
	TransCAD::ISketchEditorPtr spSketchEditor = GetFSketch()->GetSketchEditorPtr();
	// Create sketch lines
	spSketchEditor->Create2DLine2Points(GetName().c_str(), sP.X(), sP.Y(), eP.X(), eP.Y() );
	
	//DEBUG
	cout << "  " << GetName() << " : " << sP.X() << " " << sP.Y() << " " << eP.X() << " " << eP.Y() << endl;
}
