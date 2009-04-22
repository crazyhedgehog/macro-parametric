#include ".\FeatureSOLIDCreateProtrusionRevolve.h"

#include <iostream>

#include <uf_modl.h>

#include "Part.h"
#include "FSketch.h"
#include "SKETCHCreate2DCenterline.h"


using namespace std;

FeatureSOLIDCreateProtrusionRevolve::FeatureSOLIDCreateProtrusionRevolve(Part * pPart, TransCAD::IFeaturePtr spFeature)
	: Feature(pPart,spFeature)
{
}

FeatureSOLIDCreateProtrusionRevolve::~FeatureSOLIDCreateProtrusionRevolve(void)
{
}

void FeatureSOLIDCreateProtrusionRevolve::GetInfo()
{
	TransCAD::IStdSolidProtrusionRevolveFeaturePtr spFeature = GetTransCADFeature();
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

	_gcvt(_startAngle=sA, MAX_DIGITS, _eA);
	_gcvt(_endAngle=eA, MAX_DIGITS, _sA);
	
	TransCAD::IReferencePtr spReference = spFeature->ProfileSketch;
	string sketchName = spReference->ReferenceeName;

	
	_featureProfileSketch = (FSketch*)(GetPart()->GetFeatureByName(sketchName));
}

void FeatureSOLIDCreateProtrusionRevolve::ToUG()
{
	SKETCHCreate2DCenterline* pCL = (SKETCHCreate2DCenterline*)(GetFeatureProfileSketch()->GetCenterline());
	Direct3D axis;
	UF_FEATURE_SIGN mode_sign = UF_NULLSIGN;

	int  obj_count;
	char *offsets[2]= {"0.0", "0.0" };
	double origin[3] = {0.0, 0.0, 0.0};
	double direction[3] = {0.0, 1.0, 0.0};
	tag_t *object;
	for (int i=0; i<3; i++) axis[i]=pCL->_ugLine.end_point[i]-pCL->_ugLine.start_point[i];
	axis = axis.Norm();
	char*  limit[2]; limit[0]=_sA; limit[1]=_eA;

	int result = UF_MODL_create_revolved(GetFeatureProfileSketch()->_ugObjectsList,
   	limit, pCL->_ugLine.start_point, (double*)&axis, UF_NULLSIGN
		, &_ugFeatList );
/*
	int result = UF_CALL(UF_MODL_create_revolution((tag_t*)(GetFeatureProfileSketch()->_ugObjectsList), 8,				NULL,
		limit,
		offsets,
		origin,
		false,
		true,
		origin,
		direction,
		mode_sign,
		&object,
		&obj_count));

	if (result) cout << "  error in Revolve" << endl;



char *body_limit[2] = {"0.0", "360.0"};
char *offsets[2]= {"0.0", "0.0" };
double origin[3] = {-2.0, 0.0, 0.0};
double direction[3] = {0.0, 1.0, 0.0};

UF_MODL_SWEEP_TRIM_object_p_t trim_data = NULL;

UF_CURVE_line_t sline1, sline2, sline3, sline4;

	sline1.start_point[0] = 0.0;
	sline1.start_point[1] = 0.0;
	sline1.start_point[2] = 0.0;
	sline1.end_point[0] = 0.0;
	sline1.end_point[1] = 1.0;
	sline1.end_point[2] = 0.0;
	UF_CALL(UF_CURVE_create_line(&sline1,&line1));
	
	sline2.start_point[0] = 0.0;
	sline2.start_point[1] = 1.0;
	sline2.start_point[2] = 0.0;
	sline2.end_point[0] = 2.5;
	sline2.end_point[1] = 3.5;
	sline2.end_point[2] = 0.0;
	UF_CALL(UF_CURVE_create_line(&sline2,&line2));


	sline3.start_point[0] = 2.5;
	sline3.start_point[1] = 3.5;
	sline3.start_point[2] = 0.0;
	sline3.end_point[0] = 1.0;
	sline3.end_point[1] = 0.0;
	sline3.end_point[2] = 0.0;
	UF_CALL(UF_CURVE_create_line(&sline3,&line3));

	sline4.start_point[0] = 1.0;
	sline4.start_point[1] = 0.0;
	sline4.start_point[2] = 0.0;
	sline4.end_point[0] = 0.0;
	sline4.end_point[1] = 0.0;
	sline4.end_point[2] = 0.0;
	UF_CALL(UF_CURVE_create_line(&sline4,&line4));
	generators[0] = line1;
	generators[1] = line2;
	generators[2] = line3;
	generators[3] = line4;
	UF_CALL(UF_MODL_create_revolution(generators, 4, trim_data,
		body_limit, offsets, origin, false,
		true, origin, direction, mode_sign,
		&objects, &obj_count ));

	extern int UF_MODL_create_revolved1 (
		uf_list_p_t obj_id_list, 
		char ** limit, 
		double point[ 3 ], 
		double direction[ 3 ], 
		UF_FEATURE_SIGN sign, 
		tag_t target_body, 
		uf_list_p_t * feature_list );

*/

	// DEBUG : 차후 수정
	cout << "  FeatureSOLIDCreateProtrusionRevolve " << GetFeatureName();
	cout << "  " << GetFeatureProfileSketch()->GetFeatureName() << endl;
}