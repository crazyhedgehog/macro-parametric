#include ".\FSKETCHCreate2DArcCenterEnds.h"

#include <iostream>
#include <math.h>

#include "Part.h"
#include "FSketch.h"

int FSKETCHCreate2DArcCenterEnds::_2DArcCtrEndsCnt = 0;

FSKETCHCreate2DArcCenterEnds::FSKETCHCreate2DArcCenterEnds(Part * part, tag_t fTag, FSketch * pFSketch)
	: Feature (part, fTag)
{
	_pFSketch = pFSketch;
}

FSKETCHCreate2DArcCenterEnds::~FSKETCHCreate2DArcCenterEnds(void)
{
}

void FSKETCHCreate2DArcCenterEnds::GetUGInfo()
{
	// To get curve arc coordinate infomation from a object feature Tag
	UF_CURVE_arc_t ugArc;
	UF_CALL(UF_CURVE_ask_arc_data( GetFTag(), &ugArc ) );

	// To translate center point from world to local coord
	double sketInfo[12];
	GetFSketch()->GetSketInfo(sketInfo);
	Cir_Map(sketInfo, ugArc.arc_center);
	
	// set dR,cP,sA,eA
	_dR = ugArc.radius;
	SetCntPnt(ugArc.arc_center);
	SetStaAng(ugArc.start_angle);		// Radian
	SetEndAng(ugArc.end_angle);			// Radian
		
	//-------------  Set sP, eP  -------------//
	_sP[0] = _cP.X() + _dR * cos(GetStaAng());
	_sP[1] = _cP.Y() + _dR * sin(GetStaAng());
	_sP[2] = 0;
	_eP[0] = _cP.X() + _dR * cos(GetEndAng());
	_eP[1] = _cP.Y() + _dR * sin(GetEndAng());
	_eP[2] = 0;
	//SetPickPnt();	// under construction
	
	ValRndPnt(&(_cP[0]));
	ValRndPnt(&(_sP[0]));
	ValRndPnt(&(_eP[0]));
	
	//----------  Set Result_Object_Name  ----------//
	char buffer[20];
	_itoa( _2DArcCtrEndsCnt ++, buffer, 10 );
	SetName("arc2DCtrEnds" + (string)buffer);
}

void FSKETCHCreate2DArcCenterEnds::ToTransCAD()
{
	// Get SketchEditorPtr
	TransCAD::ISketchEditorPtr spSketchEditor = GetFSketch()->GetSketchEditorPtr();
	// Create sketch lines
	spSketchEditor->Create2DArcCenterStartEnd(GetName().c_str(),
		_cP.X(), _cP.Y(), _sP.X(), _sP.Y(), _eP.X(), _eP.Y() );	

	//DEBUG
	cout << "  " << GetName() << " : " << _cP.X() << " " << _cP.Y() << " " << _sP.X() << " " << _sP.Y() << " " << _eP.X() << " " << _eP.Y() << endl;
}