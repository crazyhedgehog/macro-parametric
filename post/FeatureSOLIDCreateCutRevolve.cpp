#include ".\featuresolidcreatecutrevolve.h"

#include <iostream>

#include <uf_modl.h>

#include "Part.h"
#include "FSketch.h"
#include "SKETCHCreate2DCenterline.h"


using namespace std;


FeatureSOLIDCreateCutRevolve::FeatureSOLIDCreateCutRevolve(Part * pPart, TransCAD::IFeaturePtr spFeature)
: Feature(pPart,spFeature)
{
}

FeatureSOLIDCreateCutRevolve::~FeatureSOLIDCreateCutRevolve(void)
{
}
void FeatureSOLIDCreateCutRevolve::GetInfo()
{
	TransCAD::IStdSolidCutRevolveFeaturePtr spFeature = GetTransCADFeature();
	double sA, eA;
	eA = spFeature->StartAngle;
	sA = spFeature->EndAngle;
	if (abs(sA-eA)>360.0) {sA =0.0; eA=360.0;}
	else {
		while(sA>360.0) {sA-=360.0;}
		while(eA>360.0) {eA-=360.0;}
		if (sA>eA) sA-=360.0;
	}
	_flip = spFeature->IsFlip?true:false;	// VARIANT_BOOL (for TransCAd) -> bool Cast
	_startCondition = (EndType)(spFeature->StartCondition);
	_endCondition = (EndType)(spFeature->EndCondition);

	_gcvt(_startAngle=sA, MAX_DIGITS, _sA);
	_gcvt(_endAngle=eA, MAX_DIGITS, _eA);

	TransCAD::IReferencePtr spReference = spFeature->ProfileSketch;
	string sketchName = spReference->ReferenceeName;


	_featureProfileSketch = (FSketch*)(GetPart()->GetFeatureByName(sketchName));
}

void FeatureSOLIDCreateCutRevolve::ToUG()
{
	SKETCHCreate2DCenterline* pCL = (SKETCHCreate2DCenterline*)(GetFeatureProfileSketch()->GetCenterline());
	Direct3D axis;
	for (int i=0; i<3; i++) axis[i]=pCL->_ugLine.end_point[i]-pCL->_ugLine.start_point[i];
	axis = axis.Norm();
	char*  limit[2]; limit[0]=_sA; limit[1]=_eA;

	int result = UF_MODL_create_revolved(GetFeatureProfileSketch()->_ugObjectsList,
		limit, pCL->_ugLine.start_point, (double*)&axis, UF_NEGATIVE , &_ugFeatList );
	if (result) cout << "  error in Revolve" << endl;

	// DEBUG : 차후 수정
	cout << "  FeatureSOLIDCreateCutRevolve " << GetFeatureName();
	cout << "  " << GetFeatureProfileSketch()->GetFeatureName() << endl;
}