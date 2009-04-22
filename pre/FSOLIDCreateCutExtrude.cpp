#include "FSOLIDCreateCutExtrude.h"

#include <iostream>

#include <uf_sket.h>
#include <uf_modl.h>

#include "Part.h"
#include "FSketch.h"


using namespace std;

int FSOLIDCreateCutExtrude::_cutExtrudeCount = 0;

FSOLIDCreateCutExtrude::FSOLIDCreateCutExtrude(Part * part, tag_t fTag)
	: Feature(part,fTag)
{
}

FSOLIDCreateCutExtrude::~FSOLIDCreateCutExtrude(void)
{
}

void FSOLIDCreateCutExtrude::GetUGInfo()
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

	// extern int UF_MODL_ask_extrusion (
	//						feature_obj_id,			= fTag
	//						&num_objects, 
	//						&objects, 
	//						&trim_ptr, 
	//						*taper_angle, 
	//						limits, 
	//						offsets, 
	//						region_point, 
	//						&region_specified, 
	//						&solid_creation, 
	//						direction);

	UF_CALL( UF_MODL_ask_extrusion(fTag, &line_num, &line_tag, &trim_ptr, &taper_angle, 
		limits, offsets, region_point, &region_specified, &solid_creation, direction) );
		// UF_free(line_tag);
		// UF_MODL_SWEEP_TRIM_object_p_t *  trim_ptr  NEEDS A FREE ROUTINE ??
		// UF_free(taper_angle);
		// UF_free(limits[i]); i=0,1
		// UF_free(offsets[i]); i=0,1

	// find related Sketch's Name
	tag_t	fSketTag;
	UF_CALL(UF_MODL_ask_sketch_of_sweep(fTag, &fSketTag)); 
	_pProFSket = (FSketch *)(GetPart()->GetFeatureByTag(fSketTag) );	

	// Get Start and End Depths
	Direct3D sketNorm(this->GetProSket()->GetZ());
	Direct3D cutDirec(direction);
	bool d = ((sketNorm*cutDirec)>0);	// dot of normal_direction and extrusion_direction

	_dStart = atof(limits[d?1:0]);
	_dEnd = atof(limits[d?0:1]);

	// set the flip
	_bFlip = false;

	//DEBUG
	cout << "  " << "fSketTag : " << fSketTag << endl ;
	cout << "  " << "Sketch Feature Index = " << (unsigned int)(_pProFSket->GetFIndex()) << endl;
	cout << "  " << "StartDeth " << _dStart << " EndDepth " << _dEnd << endl;

	//-------------------  Set Result_Object_Name  -------------------//
	char buffer[20];
	_itoa( _cutExtrudeCount++, buffer, 10 );
	SetName("cutExtrude" + (string)buffer);

	//======================= UF_free =============================//
	UF_free(line_tag);
	// UF_MODL_SWEEP_TRIM_object_p_t *  trim_ptr  NEEDS A FREE ROUTINE
	UF_free(taper_angle);
	UF_free(limits[0]);
	UF_free(limits[1]);
	UF_free(offsets[0]);
	UF_free(offsets[1]);
}

void FSOLIDCreateCutExtrude::ToTransCAD()
{
	bstr_t baseSketchName( _pProFSket->GetName().c_str() );

	TransCAD::IReferencePtr spBaseSketch = GetPart()->_spPart->SelectObjectByName(baseSketchName);
    
	// Create a protrusion extrude feature with the sketch
	GetPart()->_spFeatures->AddNewSolidCutExtrudeFeature(GetName().c_str(), spBaseSketch, _dStart, TransCAD::Blind, _dEnd, TransCAD::Blind, _bFlip);
}



