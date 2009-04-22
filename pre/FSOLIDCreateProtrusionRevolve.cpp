#include ".\FSOLIDCreateProtrusionRevolve.h"

#include <iostream>

#include <uf_sket.h>
#include <uf_modl.h>

#include "Part.h"
#include "FSketch.h"
#include "FSKETCHCreate2DCenterline.h"

using namespace std;

int FSOLIDCreateProtrusionRevolve::_nProRevCnt = 0;

FSOLIDCreateProtrusionRevolve::FSOLIDCreateProtrusionRevolve(Part * part, tag_t fTag) :
	Feature(part,fTag)
{	
	_bFlip=0;
	_StaType=End_Dimension;
	_dStaAng=0;
	_EndType=End_Dimension;
	_dEndAng=0;
}


FSOLIDCreateProtrusionRevolve::~FSOLIDCreateProtrusionRevolve(void)
{
}

void FSOLIDCreateProtrusionRevolve::GetUGInfo()
{
	// Get the feature tag
	tag_t fTag = GetFTag();
	
	//----------  Start Condition, End Condition  ----------//
	int		edit=0;
	char *	taper_angle;
	char *	limit1;
	char *	limit2;
	UF_CALL( UF_MODL_ask_sweep_parms (fTag, edit, &taper_angle, &limit1, &limit2) );
	// UF_free() for taper_angle, limit1, limit2

	//----------  Start angle, End angle  ----------//
	for(unsigned int i=0; i<strlen(limit1) ; i++)	{ if(limit1[i] == '=') break; }
	for(unsigned int j=0; i<strlen(limit2) ; j++)	{ if(limit2[j] == '=') break; }
	SetStaAng( atof((const char*)(limit1+i+1)) );
	SetEndAng( atof((const char*)(limit2+j+1)) );

	// UF_free()
	UF_free(taper_angle);
	UF_free(limit1);
	UF_free(limit2);

	// Get the profile sketch feature
	tag_t fSketTag;
	UF_CALL(UF_MODL_ask_sketch_of_sweep(fTag, &fSketTag)); 
	_pProFSket = (FSketch *)(GetPart()->GetFeatureByTag(fSketTag));

	//DEBUG
	cout << "  " << "Profile Sketch Feature Tag : " << fSketTag << endl ;

	// get revolve origin and axis
	double pos[3], dir[3];
	UF_MODL_ask_sweep_direction(fTag, pos, dir);	// Don't use UF_CALL()
	
	// create 2DCenterline and GetUGInfo()
	FSKETCHCreate2DCenterline* pCLine = new FSKETCHCreate2DCenterline(GetPart(),0,_pProFSket);
	pCLine->GetUGInfo(pos,dir);

	// Set Centerline in the SketObjList of profile sketch
	_pProFSket->SetCLine(pCLine);

	//----------  Set Result_Object_Name  ----------//
	char buffer[20];
	_itoa( _nProRevCnt++, buffer, 10 );
	SetName("proRevolve" + (string)buffer);
}


void FSOLIDCreateProtrusionRevolve::ToTransCAD()
{
	bstr_t proSketName( GetProSket()->GetName().c_str() );
	TransCAD::IReferencePtr spProSket = GetPart()->_spPart->SelectObjectByName(proSketName);
    
	// Create a protrusion revolve feature with the sketch
	GetPart()->_spFeatures->AddNewSolidProtrusionRevolveFeature(GetName().c_str(),spProSket,
		_dStaAng, TransCAD::StdRevolveEndType_Blind,
		_dEndAng, TransCAD::StdRevolveEndType_Blind, false);
}
