#include ".\featuresolidcreatepatterncirc.h"

#include <iostream>
#include <uf_modl.h>
#include <uf_trns.h>
#include <uf_group.h>
#include <uf_assem.h>
#include <uf_patt.h>
#include "Part.h"

#include <uf.h>
#include <uf_defs.h>
#include <uf_curve.h>
#include <uf_part.h>
#include <uf_csys.h>
#include <uf_patt.h>

#include <uf_ui.h>
#include <uf_object_types.h>


FeatureSOLIDCreatePatternCirc::FeatureSOLIDCreatePatternCirc(Part * pPart, TransCAD::IFeaturePtr spFeature)
: Feature(pPart,spFeature)
{
 
}

FeatureSOLIDCreatePatternCirc::~FeatureSOLIDCreatePatternCirc(void)
{
}


void FeatureSOLIDCreatePatternCirc::GetInfo(void)
{
	
	TransCAD::IStdSolidOperatePatternCircularFeaturePtr spFeature = GetTransCADFeature();

	TransCAD::IReferencePtr spTargetFeature = spFeature->TargetFeature;
	
	_featurename = spTargetFeature->ReferenceeName;

	
	_isradial = spFeature->IsRadialAnignment;

	_gcvt(spFeature->NumberOfPatterns, MAX_DIGITS, _patternnumber);
	
	_gcvt(spFeature->AngleIncrement, MAX_DIGITS, _angleincrement);


	spFeature->GetCenterAxis(&_ptorg[0],&_ptorg[1],&_ptorg[2],&_ptvec[0],&_ptvec[1],&_ptvec[2]);

	_ptvec[0]=0;
		_ptvec[1]=0;
			_ptvec[2]=1;
 
	cout<<_featurename<<endl<<_patternnumber<<endl<<_angleincrement<<endl<<_isradial<<endl<<endl<<endl;
	cout<<_ptorg[0]<<endl<<_ptorg[1]<<endl<<_ptorg[2]<<endl<<_ptvec[0]<<endl<<_ptvec[1]<<endl<<_ptvec[2]<<endl;


}

void FeatureSOLIDCreatePatternCirc::ToUG(void)
{
	tag_t 	feature; 
	tag_t
		array;

	Feature * pFeature =(Feature*) (GetPart()->GetFeatureByName(_featurename));

	uf_list_p_t feat_list;
	
	UF_MODL_ask_list_item(pFeature->_ugFeatList,0,&feature);
	
   // UF_CALL(UF_MODL_create_list(&feat_list));
	
	//UF_CALL(UF_MODL_put_list_item(feat_list,feature));

	//UF_CALL(UF_MODL_create_circular_iset(0,_ptorg,_ptvec,_patternnumber,_angleincrement, feat_list,&_ugTag));
	//UF_ASSEM_iset_array_data_s
	//	array_data;

		
	//	array_data.array_name = "asdf";

//	array_data.template_component= feature;
	
//	array_data.array_subtype = UF_ASSEM_circular_array;
//	array_data.master_component = NULL_TAG;

// 
// 	UF_CALL(UF_MODL_create_exp_tag("16", &array_data.dimensions[0]));
// 
// 	UF_CALL(UF_MODL_create_exp_tag("20", &array_data.offsets[0]));
// 	
// 	UF_CALL(UF_ASSEM_create_iset_array(&array_data, &array));

}

