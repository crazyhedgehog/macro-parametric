#include ".\FSOLIDOperateFilletingFilletConstant.h"

#include <iostream>

#include <uf_vec.h>
#include <uf_modl.h>
#include <uf_sket.h>
#include <uf_obj.h>
#include <uf_object_types.h>

#include "UGPre.h"
#include "Part.h"
#include "Feature.h"
#include "FSketch.h"
#include "FSOLIDCreateProtrusionExtrude.h"

using namespace std;

int FSOLIDOperateFilletingFilletConstant::_fillCnt = 0;

FSOLIDOperateFilletingFilletConstant::FSOLIDOperateFilletingFilletConstant(Part * part, tag_t fTag) :
	Feature(part, fTag)
{
}

void FSOLIDOperateFilletingFilletConstant::GetUGInfo()
{
	
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
	//----------------  Set Result_Object_Name  -----------------//
	char buffer[20];
	_itoa( _fillCnt++, buffer, 10 );
	SetName("fillet" + (string)buffer);
}

void FSOLIDOperateFilletingFilletConstant::ToTransCAD()
{
	//return;
	//if (_fillCnt==2) {_fillCnt++; return;}
	// Select object
	//TransCAD::IReferencePtr spReference = GetPart()->_spPart->SelectBrepByName(
	//	"proExtrude0,sketch0,line2D2,0,0,0,ExtrudeFeature:0,0:0;0#proExtrude0,sketch0,line2D3,0,0,0,ExtrudeFeature:0,0:0;0");
	TransCAD::IReferencePtr spReference = GetPart()->_spPart->SelectCurveBy3Points(
		_sP[0],_sP[1],_sP[2],_eP[0],_eP[1],_eP[2],_pP[0],_pP[1],_pP[2]);
	//TransCAD::IReferencePtr spReference =0;
	if (spReference) {
		// Fillet Edges
		TransCAD::IReferencesPtr spReferences = GetPart()->_spPart->CreateReferences();
		spReferences->Add(spReference);
		// Create a fillet constant feature
		GetPart()->_spFeatures->AddNewSolideFilletConstantFeature(GetName().c_str(), spReferences, GetRadius(), (TransCAD::PropagationType)GetPropType());
		cout << "  " <<_sP[0]<<" "<<_sP[1]<<" "<<_sP[2]<<endl;
		cout << "  " <<_eP[0]<<" "<<_eP[1]<<" "<<_eP[2]<<endl;
		cout << "  " <<_pP[0]<<" "<<_pP[1]<<" "<<_pP[2]<<endl;
	}
}