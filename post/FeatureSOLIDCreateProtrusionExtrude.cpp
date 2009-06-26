#include ".\FeatureSOLIDCreateProtrusionExtrude.h"

#include <iostream>

#include <uf_modl.h>
#include <uf_wave.h>

#include "Part.h"
#include "FSketch.h"


using namespace std;

FeatureSOLIDCreateProtrusionExtrude::FeatureSOLIDCreateProtrusionExtrude(Part * pPart, TransCAD::IFeaturePtr spFeature)
	: Feature(pPart,spFeature)
{
}

FeatureSOLIDCreateProtrusionExtrude::~FeatureSOLIDCreateProtrusionExtrude(void)
{
}

void FeatureSOLIDCreateProtrusionExtrude::GetInfo()
{
	TransCAD::IStdSolidProtrusionExtrudeFeaturePtr spFeature = GetTransCADFeature();
	_startDepth = spFeature->StartDepth;
	_startCondition = (EndType)(spFeature->StartCondition);
	_endDepth = spFeature->EndDepth;
	_endCondition = (EndType)(spFeature->EndCondition);
	_flip = spFeature->IsFlip?true:false;	// VARIANT_BOOL (for TransCAd) -> bool Cast
	
	_gcvt(_startDepth, MAX_DIGITS, _sD);
	_gcvt(_endDepth, MAX_DIGITS, _eD);
	
	TransCAD::IReferencePtr spReference = spFeature->ProfileSketch;
	string sketchName = spReference->ReferenceeName;

	_featureProfileSketch = (FSketch*)(GetPart()->GetFeatureByName(sketchName));
}

void FeatureSOLIDCreateProtrusionExtrude::ToUG()
{
	double point[ 3 ]; 
	Direct3D direction =  GetFeatureProfileSketch()->GetNormal();
	char*  limit[2]; limit[0] = _sD; limit[1] = _eD;
	if(_flip) direction = direction *(-1);
	tag_t *feature,*body;
	uf_list_p_t newlist,templist,featlist;
	int n_counts;
	
	UF_MODL_create_list(&templist);
	if(GetPart()->index)
		UF_MODL_create_extruded2(GetFeatureProfileSketch()->_ugObjectsList,"0.0",limit, point, (double*)&direction, UF_POSITIVE, &templist );
	else
		UF_MODL_create_extruded2(GetFeatureProfileSketch()->_ugObjectsList,"0.0",limit, point, (double*)&direction, UF_NULLSIGN, &templist );
	UF_MODL_ask_list_count(templist,&n_counts);

	if(n_counts>=2){

		feature = new tag_t[n_counts];
		body = new tag_t[n_counts];
		
		UF_MODL_create_list(&newlist);
		UF_MODL_create_list(&featlist);
		
		for(int i=0;i<n_counts;i++){
			UF_MODL_ask_list_item(templist,i,&feature[i]);
			UF_MODL_ask_feat_body(feature[i],&body[i]);
		}

		for(int i=1;i<n_counts;i++){
			UF_MODL_operations(body[0],body[i],UF_NEGATIVE );	
		}

		UF_MODL_ask_body_feats (body[0], &featlist);
		UF_MODL_ask_list_item (featlist, 0, &feature[0]);
		UF_MODL_put_list_item(newlist, feature[0]); 
		
		_ugFeatList=newlist;
	
	}else 
		
		_ugFeatList=templist;
	
	// DEBUG : 차후 수정
	cout << "  FeatureSOLIDCreateProtrusionExtrude " << GetFeatureName();
	cout << "  " << GetFeatureProfileSketch()->GetFeatureName() << endl;

}