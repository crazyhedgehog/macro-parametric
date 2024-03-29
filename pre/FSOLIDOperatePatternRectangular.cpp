#include ".\FSOLIDOperatePatternRectangular.h"

#include <iostream>

#include <uf_vec.h>
#include <uf_modl.h>
#include <uf_sket.h>
#include <uf_obj.h>
#include <uf_object_types.h>
#include <uf_assem.h>

#include "UGPre.h"
#include "Part.h"
#include "Feature.h"
#include "FSketch.h"
#include "FSOLIDCreateProtrusionExtrude.h"

using namespace std;

int FSOLIDOperatePatternRectangular::_patternCnt = 0;

FSOLIDOperatePatternRectangular::FSOLIDOperatePatternRectangular(Part * part, tag_t fTag) :
	Feature(part, fTag)
{
	_fType=SOLID_Operate_Pattern_Rectangular;
}

void FSOLIDOperatePatternRectangular::GetUGInfo()
{
	tag_t fTag = GetFTag();
	
	char* numx;
	char* numy;
	char* distx;
	char* disty;
	char* featname;

	uf_list_p_t features;
	
	UF_MODL_create_list(&features);
	UF_MODL_ask_linear_iset_parms(fTag,1,&numx,&numy,&distx,&disty); 

	UF_MODL_ask_instance (fTag,&features);
	UF_MODL_ask_feat_name(features[0].eid,&featname);

	tag_t temptag;
	UF_MODL_ask_instance_iset (features[0].eid,&temptag);
	//temptag = UF_ASSEM_ask_child_of_instance(features[0].eid); 

	//UF_ASSEM_ask_parent_component (		features[0].eid, 		&temptag );
	cout<<numx;
	
	//temptag = features[0].eid;
	tag_t *p;
	tag_t *c;
	int nump,numc;
	UF_CALL(UF_MODL_ask_feat_relatives (features->eid,&nump,&p,&numc,&c));
	tag_t eachTag = NULL_TAG;
	tag_t fSketTag = NULL_TAG;
	

	for(int i =0; i<GetPart()->GetFeatureTagSize();i++)
	{	eachTag=GetPart()->GetFeatureTag(i);
		
		UF_CALL(UF_MODL_ask_sketch_of_sweep(eachTag, &fSketTag));
	
		if(*p == fSketTag) {
			cout<< "GoTYA~~~~~~~~~~~~";
			break;}
		
	}
	_targetFeature = GetPart()->GetFeatureByTag(eachTag);
	//_targetName = "proExtrude2";
	
	_targetName = _targetFeature->GetName();
	//_targetFeature->SetFType(ExplicitModelObject);
// 	UF_OBJ_cycle_objs_in_part(GetPart()->GetPartTag(), UF_feature_type, &eachTag);
// 	while(eachTag != NULL_TAG)
// 	{
// 		UF_CALL(UF_MODL_ask_sketch_of_sweep(fTag, &fSketTag));
// 		//_pProFSket = (FSketch *)(GetPart()->GetFeatureByTag(fSketTag) );
// 		
// 		// get a feature tag
// 		UF_OBJ_cycle_objs_in_part(GetPart()->GetPartTag(), UF_feature_type, &eachTag);
// 	}	
	

	
	
// 	tag_t *p;
// 	char** n;
// 	int nr;
//  	UF_MODL_ask_references_of_features (&temptag,1,&p,&n,&nr);
//  		

// 	Feature * pFeature = new FSOLIDCreateProtrusionExtrude(GetPart(),features[0].eid);
// 	pFeature->GetUGInfo();
// 	pFeature->ToTransCAD();
	/*
	//---------	 get the blended edge geometry information  ---------//

	UF_MODL_edge_blend_data_t	ugBlendEdge;
	UF_CALL(UF_MODL_ask_edge_blend(_fTag,&ugBlendEdge) ); // output to be freeed : later
	tag_t blendedEdgeTag = ugBlendEdge.edge_data->edge;
	cout << "  " << "Num of Points : " << ugBlendEdge.edge_data->number_points << endl;
		
	// Set fillet dR and Propagation Type
	_dR = atof(ugBlendEdge.blend_radius);
	_PropType = Minimal;
	//DEBUG
	cout << "  " << "Num of Blended edges : " << ugBlendEdge.number_edges << endl;
	cout << "  " << "Edge Tag : " << blendedEdgeTag << endl;
	int						edge_type;
	double*					edge_data;
	UF_CURVE_struct_p_t		edge_struct_p_t;
	UF_CALL( UF_CURVE_ask_curve_struct(blendedEdgeTag, &edge_struct_p_t) );	
	UF_CALL( UF_CURVE_ask_curve_struct_data(edge_struct_p_t, &edge_type, &edge_data) );

	if( edge_type == UF_line_type)	// UF_line_type : 3
	{
		cout << "  " << " Edge_Type " << edge_type << endl;
		cout << "  " << edge_data[3] << " " << edge_data[4] << " " << edge_data[5] << endl;
		cout << "  " << edge_data[6] << " " << edge_data[7] << " " << edge_data[8] << endl;
		ValRndPnt(edge_data+3);
		ValRndPnt(edge_data+6);
		// UF_CURVE_ask_curve_struct_data 부정확하므로 소수 6자리 이하 Rounding!!
		_sP = Point3D(edge_data+3);	
		_eP = Point3D(edge_data+6); 
		_pP = (_sP+_eP) * 0.5 ;
	}
	else {
		cout << "  " << "Cannot support Blended Edge Type!!" << endl;
		cout << "  " << "Only support Linear Edge!!" << endl;
	}
	UF_CALL(UF_CURVE_free_curve_struct(edge_struct_p_t));
	UF_free(edge_data);

	//---------	 Get the Related Skech Info  ---------//
	int num_parents, num_children;
	tag_t *parent_array, *children_array;
	UF_MODL_ask_feat_relatives(GetFTag(),&num_parents,&parent_array,
		&num_children,&children_array);
	cout << "  " << "No. of Parents  : " << num_parents << endl;
	for(int i=0; i<num_parents ; i++)
	{
		char* feat_type;
		UF_MODL_ask_feat_type(parent_array[i],&feat_type);
		cout << "    " << "Parent[" << i << "] : " << feat_type << " Type" << endl;
		Feature* pFeature = GetPart()->GetFeatureByTag(parent_array[0]);
		if (pFeature)
		{
			double sketInfo[12];
			bool bInfo = 0;
			switch (pFeature->GetFType())
			{
			case SOLID_Create_Protrusion_Extrude :
                ((FSOLIDCreateProtrusionExtrude*)pFeature)->GetProSket()->GetSketInfo(sketInfo);
				bInfo = 1;
				break;
			default :
				break;
			}
			if (bInfo)
			{
				Map(sketInfo,&(_sP[0]));
				Map(sketInfo,&(_eP[0]));
				Map(sketInfo,&(_pP[0]));
				break;
			}
		}
	}


	ValRndPnt(&(_sP[0]));
	ValRndPnt(&(_eP[0]));
	ValRndPnt(&(_pP[0]));	

	UF_free(parent_array);
	UF_free(children_array);
	*/

	//----------------  Set Result_Object_Name  -----------------//
	char buffer[20];
	_itoa( _patternCnt++, buffer, 10 );
	SetName("pattern" + (string)buffer);
}

void FSOLIDOperatePatternRectangular::ToTransCAD()
{
 
// 	bstr_t proSketName( GetProSket()->GetName().c_str() );
// 	TransCAD::IReferencePtr spProSket = GetPart()->_spPart->SelectObjectByName(proSketName);
// 
// 	// Create a protrusion revolve feature with the sketch
// 	GetPart()->_spFeatures->AddNewSolidProtrusionRevolveFeature(GetName().c_str(),spProSket,
// 		_dStaAng, TransCAD::StdRevolveEndType_Blind,
// 		_dEndAng, TransCAD::StdRevolveEndType_Blind, false);
//GetPart()->_spPart->SelectObjectByName()
	
	bstr_t name(_targetName.c_str());
	
	TransCAD::IReferencePtr spTarget;

	//cout << GetPart()->_spPart->SelectObjectByName(name)->GetType();
	
	
	spTarget = GetPart()->_spPart->SelectFeatureByName(name);
	
	
	//TransCAD::IFeaturePtr dd = GetPart()->_spFeatures->GetItem(7);
	
	//bstr_t ddd = dd->GetName();

	GetPart()->_spFeatures->AddNewSolidOperatePatternRectangularFeature(
		GetName().c_str()
		,spTarget
		,2.5,0,-1,0,3
		,1,1,0,0,1
		);

}