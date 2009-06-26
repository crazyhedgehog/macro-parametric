#include ".\FSOLIDCreateProtrusionExtrude.h"

#include <iostream>

#include <uf_sket.h>
#include <uf_modl.h>
#include <uf_assem.h>
#include "Part.h"
#include "FSketch.h"


using namespace std;

int FSOLIDCreateProtrusionExtrude::_proExtCnt = 0;

FSOLIDCreateProtrusionExtrude::FSOLIDCreateProtrusionExtrude(Part * part, tag_t fTag)
	: Feature(part,fTag)
{
	_fType = SOLID_Create_Protrusion_Extrude;
}

FSOLIDCreateProtrusionExtrude::~FSOLIDCreateProtrusionExtrude(void)
{
}

void FSOLIDCreateProtrusionExtrude::GetUGInfo()
{
	tag_t	fTag = GetFTag();
	int 	line_num;								// num_objects
	tag_t *	line_tag;								// objects
	UF_MODL_SWEEP_TRIM_object_p_t	trim_ptr;		// NULL if no trimming object
	char *	taper_angle;
	char *	limits[2];
	char *	offsets[2];
	double	region_point[3];
	logical	region_specified;
	logical solid_creation;
	double	direction[3];
	
	UF_CALL( UF_MODL_ask_extrusion(fTag, &line_num, &line_tag, &trim_ptr, &taper_angle, 
		limits, offsets, region_point, &region_specified, &solid_creation, direction) );
		// UF_free(line_tag);
		// UF_MODL_SWEEP_TRIM_object_p_t *  trim_ptr  NEEDS A FREE ROUTINE ??
		// UF_free(taper_angle);
		// UF_free(limits[i]); i=0,1
		// UF_free(offsets[i]); i=0,1

	// Get FeatureProfileSketch Class Ptr
	tag_t	fSketTag;
	
	UF_CALL(UF_MODL_ask_sketch_of_sweep(fTag, &fSketTag));


	_pProFSket = (FSketch *)(GetPart()->GetFeatureByTag(fSketTag) );
	
	_dStart = atof(limits[0]);	// set _dStart
	_dEnd = atof(limits[1]);	// set _dEnd

	_bFlip = false;					// set _ flip

	//DEBUG
	cout << "  " << "fSketTag : " << fSketTag << endl ;
	cout << "  " << "Sketch Feature Index = " << (unsigned int)(_pProFSket->GetFIndex()) << endl;
	cout << "  " << "StartDeth " << _dStart << " EndDepth " << _dEnd << endl;

	//-------------------  UF_free  -------------------//
	UF_free(line_tag);
	// UF_MODL_SWEEP_TRIM_object_p_t *  trim_ptr  NEEDS A FREE ROUTINE
	UF_free(taper_angle);
	UF_free(limits[0]);
	UF_free(limits[1]);
	UF_free(offsets[0]);
	UF_free(offsets[1]);

	//-------------------  Set Result_Object_Name  -------------------//
	char buffer[20];
	_itoa( _proExtCnt++, buffer, 10 );
	SetName("proExtrude" + (string)buffer);
}


void FSOLIDCreateProtrusionExtrude::ToTransCAD()
{
	bstr_t baseSketchName( GetProSket()->GetName().c_str() );

	TransCAD::IReferencePtr spBaseSketch = GetPart()->_spPart->SelectObjectByName(baseSketchName);
    
	// Create a protrusion extrude feature with the sketch
	GetPart()->_spFeatures->AddNewSolidProtrusionExtrudeFeature(GetName().c_str(), spBaseSketch, _dStart, TransCAD::Blind, _dEnd, TransCAD::Blind, _bFlip);
}