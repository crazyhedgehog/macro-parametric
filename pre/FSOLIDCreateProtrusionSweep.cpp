#include ".\FSOLIDCreateProtrusionSweep.h"

#include <iostream>
#include <AtlBase.h>

#include <uf_sket.h>
#include <uf_modl.h>

#include "Part.h"
#include "FSketch.h"

using namespace std;


int FSOLIDCreateProtrusionSweep::_proSweepCount = 0;

FSOLIDCreateProtrusionSweep::FSOLIDCreateProtrusionSweep(Part * part, tag_t fTag) :
	Feature(part,fTag)
{	
}

void FSOLIDCreateProtrusionSweep::GetUGInfo()
{
	int  nParents, nChildren;
	tag_t * parentArray,  * childrenArray;
	tag_t fTag = GetFTag();

	// relative parents feature : two Sketch Feature Tags
	UF_MODL_ask_feat_relatives(fTag, &nParents, &parentArray, &nChildren, &childrenArray);
	// UF_free() : parentArray, childrenArray
	
	// Set FeatureProfileSketch, FeatureGuideSketch
	// parentArray[0] : Profile Sketch Tag
	// parentArray[1] : Guide Sketch Tag
	_pProFSket = (FSketch *)(GetPart()->GetFeatureByTag(parentArray[0]));
	_pGuiFSket	  = (FSketch *)(GetPart()->GetFeatureByTag(parentArray[1]));

	// DEBUG
	cout << "  Profile Sketch Feature Tag : " << parentArray[0] << endl;
	cout << "  Guide   Sketch Feature Tag : " << parentArray[1] << endl;

	//----------  UF_free  ----------//
	UF_free(parentArray);
	UF_free(childrenArray);

	//----------  Set Result_Object_Name  ----------//
	char buffer[20];
	_itoa( _proSweepCount++, buffer, 10 );
	SetName("proSweep" + (string)buffer);
}

void FSOLIDCreateProtrusionSweep::ToTransCAD()
{
	bstr_t profileName( GetProSket()->GetName().c_str());
	bstr_t guideName( GetGuideSketch()->GetName().c_str());

	TransCAD::IReferencePtr spProfile = GetPart()->_spPart->SelectObjectByName(profileName);
	TransCAD::IReferencePtr spGuide = GetPart()->_spPart->SelectObjectByName(guideName);

    
	// Create a Protrusion Sweep
	GetPart()->_spFeatures->AddNewSolidProtrusionSweepFeature(A2BSTR(GetName().c_str()), spProfile, spGuide);
	GetPart()->_spFeatures->AddNewSolidProtrusionSweepFeature("Sweep1", spProfile, spGuide);
}