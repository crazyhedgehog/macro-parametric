#include ".\FSKETCHCreate2DCircleCenterPoint.h"

#include <iostream>

#include "Part.h"
#include "FSketch.h"

int FSKETCHCreate2DCircleCenterPoint::_circle2DCPCnt = 0;

FSKETCHCreate2DCircleCenterPoint::FSKETCHCreate2DCircleCenterPoint(Part * part, tag_t fTag, FSketch * pFSketch)
	: Feature (part, fTag)
{
	_pFSketch = pFSketch;
}

FSKETCHCreate2DCircleCenterPoint::~FSKETCHCreate2DCircleCenterPoint(void)
{
}

void FSKETCHCreate2DCircleCenterPoint::GetUGInfo()
{
	// To get curve arc coordinate infomation from a object feature Tag
	UF_CURVE_arc_t ugArc;
	UF_CALL(UF_CURVE_ask_arc_data( GetFTag(), &ugArc ) );

	// To translate center point from world to local coord
	double sketInfo[12];
	GetFSketch()->GetSketInfo(sketInfo);
	Cir_Map(sketInfo, ugArc.arc_center);

	// set center point and dR
	SetCntPnt(ugArc.arc_center);
	SetRadius(ugArc.radius);
	
	//----------  Set Result_Object_Name  ----------//
	char buffer[20];
	_itoa( _circle2DCPCnt ++ , buffer, 10 );
    SetName("circle2DCP" + (string)buffer);
}

void FSKETCHCreate2DCircleCenterPoint::ToTransCAD()
{
	// Get SketchEditorPtr
	TransCAD::ISketchEditorPtr spSketchEditor = GetFSketch()->GetSketchEditorPtr();
	// Create sketch lines
	spSketchEditor->Create2DCircleCenterPoint(GetName().c_str(), _cP[0], _cP[1], GetRadius());
	
	//DEBUG
	cout << "  Center Point " << _cP[0] << " " << _cP[1] << " " << _cP[2] << endl;
}