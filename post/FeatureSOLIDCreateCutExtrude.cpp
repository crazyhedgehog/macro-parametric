#include ".\FeatureSOLIDCreateCutExtrude.h"

#include <iostream>

//#include <uf_sket.h>
#include <uf_modl.h>

#include "Part.h"
#include "FSketch.h"


using namespace std;

FeatureSOLIDCreateCutExtrude::FeatureSOLIDCreateCutExtrude(Part * pPart, TransCAD::IFeaturePtr spFeature)
	: Feature(pPart,spFeature)
{
}

FeatureSOLIDCreateCutExtrude::~FeatureSOLIDCreateCutExtrude(void)
{
}

void FeatureSOLIDCreateCutExtrude::GetInfo()
{
	TransCAD::IStdSolidCutExtrudeFeaturePtr spFeature = GetTransCADFeature();
	double sD, eD;
	sD = spFeature->StartDepth;
	eD = spFeature->EndDepth;
	if (sD<eD) {
		_startDepth = sD; _endDepth = eD;
		_startCondition = (EndType)(spFeature->StartCondition);
		_endCondition = (EndType)(spFeature->EndCondition);
	}
	else {
		_endDepth = sD; _startDepth = eD;
		_endCondition = (EndType)(spFeature->StartCondition);
		_startCondition = (EndType)(spFeature->EndCondition);
	}
	_flip = spFeature->IsFlip?true:false;	// VARIANT_BOOL (for TransCAd) -> bool Cast
	if (_startCondition==TransCAD::ThroughAll) 
	_startDepth=-MAX_DEPTH;
	if (_endCondition==TransCAD::ThroughAll) 
	_endDepth=MAX_DEPTH;
	
	if(_flip){_gcvt(_startDepth, MAX_DIGITS, _eD);
				_gcvt(_endDepth, MAX_DIGITS, _sD);}
	else{
		_gcvt(_startDepth, MAX_DIGITS, _sD);
		_gcvt(_endDepth, MAX_DIGITS, _eD);
	}
	TransCAD::IReferencePtr spReference = spFeature->ProfileSketch;
	string sketchName = spReference->ReferenceeName;
	_featureProfileSketch = (FSketch*)(GetPart()->GetFeatureByName(sketchName));

}

void FeatureSOLIDCreateCutExtrude::ToUG()
{
	double point[ 3 ]; 
	// Cut : Normal을 반대로 설정
	Direct3D direction= GetFeatureProfileSketch()->GetNormal();
	if (!_flip) direction = Direct3D(0,0,0)-direction;
	char*  limit[2]; limit[0] = _sD; limit[1] = _eD;

	tag_t feat,body;
	for(size_t i=0; i<_nIndex; i++)	// 모든 Extrude,Revolve,Sweep,...  ACTIVE 하여 CUT
	{
		Feature * pFeature = GetPart()->GetFeature((int)i);
		if (pFeature->_ugFeatList) {
			UF_MODL_ask_list_item(pFeature->_ugFeatList,0,&feat);
			UF_MODL_ask_feat_body(feat,&body);
			UF_MODL_active_part(body,FALSE);
			UF_MODL_create_extruded2(GetFeatureProfileSketch()->_ugObjectsList,"0.0",
				limit, point, (double*)&direction,UF_NEGATIVE, &_ugFeatList );
		}
	}

	// DEBUG : 차후 수정
	cout << "  FeatureSOLIDCreateCutExtrude " << GetFeatureName() << " " << _startCondition << " "<<_endCondition;
	cout << "  " << GetFeatureProfileSketch()->GetFeatureName() << endl;
}