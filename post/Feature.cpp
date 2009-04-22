#include ".\feature.h"

#include <iostream>
#include <uf_modl.h>

#include "Part.h"

using namespace std;

Feature::Feature(Part * pPart, TransCAD::IFeaturePtr spFeature)
{
	_pPart = pPart;											// Set Part ptr
	_spFeature = spFeature;							// Set TransCAD Feature ptr
	_nIndex = pPart->GetSize();						// Set index
	if (spFeature) _strName = spFeature->Name;	// Set A Feature's Name
	cout << "Feature Name : " << _strName;			//DEBUG

	_ugTag = 0;
	_ugFeatList = 0;
}

Feature::~Feature(void)
{
	if (_ugFeatList)
		UF_MODL_delete_list(&_ugFeatList);
}