#include ".\FeatureSOLIDCreateProtrusionSweep.h"

#include <iostream>

#include <uf_modl.h>

#include "Part.h"
#include "FSketch.h"

using namespace std;

FeatureSOLIDCreateProtrusionSweep::FeatureSOLIDCreateProtrusionSweep(Part * pPart, TransCAD::IFeaturePtr spFeature)
	: Feature(pPart,spFeature)
{
	_profileSketch = 0;
	_guideSketch = 0;
}

FeatureSOLIDCreateProtrusionSweep::~FeatureSOLIDCreateProtrusionSweep(void)
{
}

void FeatureSOLIDCreateProtrusionSweep::GetInfo()
{
	TransCAD::IStdSolidProtrusionSweepFeaturePtr spFeature = GetTransCADFeature();
	TransCAD::IReferencePtr spProfile = spFeature->ProfileSketch;
	TransCAD::IReferencePtr spGuide = spFeature->GuideCurve;
	string profileName = spProfile->ReferenceeName;
	string guideName = spGuide->ReferenceeName;
	_profileSketch = (FSketch*)(GetPart()->GetFeatureByName(profileName));
	_guideSketch = (FSketch*)(GetPart()->GetFeatureByName(guideName));
}

void FeatureSOLIDCreateProtrusionSweep::ToUG()
{
	double point[3];
	UF_MODL_create_extruded_path(_profileSketch->_ugObjectsList, _guideSketch->_ugObjectsList,
		point, NULL, UF_NULLSIGN, &_ugFeatList);
	
	cout << "  FeatureSOLIDCreateProtrusionSweep " << GetFeatureName();
	cout << "  " << GetProfileSketch()->GetFeatureName();
	cout << "  " << GetGuideSketch()->GetFeatureName() << endl;
}