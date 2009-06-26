#include ".\FeatureSOLIDOperateFilletingFilletConstant.h"

#include <iostream>
#include <uf_eval.h>
#include <uf_modl.h>
#include <cmath>

//#include <uf_obj.h>
//#include <uf_object_types.h>


#include "Part.h"

using namespace std;

FeatureSOLIDOperateFilletingFilletConstant::FeatureSOLIDOperateFilletingFilletConstant(Part * pPart, TransCAD::IFeaturePtr spFeature) :
Feature(pPart, spFeature)
{
	_ugBlendEdgeList = 0;
	memset(_basefeaturename,0,100);
}

FeatureSOLIDOperateFilletingFilletConstant::~FeatureSOLIDOperateFilletingFilletConstant(void)
{
	if (_ugBlendEdgeList)
		UF_MODL_delete_list(&_ugBlendEdgeList);
}

void FeatureSOLIDOperateFilletingFilletConstant::GetInfo()
{
	TransCAD::IStdSolidFilletConstantFeaturePtr spFeature = GetTransCADFeature();
	_radius= spFeature->Radius;
	_propagationType = (PropagationType)(spFeature->Propagation);
	
	TransCAD::IReferencesPtr spReferences = spFeature->FilletEdges;

	_point1[0]=spFeature->StartPosX;
	_point1[1]=spFeature->StartPosY;
	_point1[2]=spFeature->StartPosZ;
	
	_point2[0]=spFeature->EndPosX;
	_point2[1]=spFeature->EndPosY;
	_point2[2]=spFeature->EndPosZ;


	UF_MODL_create_list(&_ugBlendEdgeList);
	
	for (int i=1 ; i<= spReferences->Count; i++){
		TransCAD::IReferencePtr spReference = spReferences->Item[i];
		cout << "	" << "Name           : " << spReference->Name << endl;
		cout << "	" << "ReferenceeName : " << spReference->ReferenceeName << endl;
		cout << "	" << "Type           : " << spReference->Type << endl;	// 1 : Brep
	
	_featurename = spReference->ReferenceeName;
	ExtractBaseFeature(_featurename);
		
		// need the geometry information for an edge item[i]
		//		FSketch * pFeature =(FSketch*) (GetPart()->GetFeatureByName(_featurename));
		//		UF_MODL_put_list_item(_ugBlendEdgeList,pFeature->_ugTag);
	}

}

void FeatureSOLIDOperateFilletingFilletConstant::ToUG()
{
	int vertex,edge_count,edgeNo=-1;	
	

	tag_t edge_id,mainfeature,mainbody;
	uf_list_p_t featList,all_edge_list;

	UF_MODL_create_list(&featList);
	UF_MODL_create_list(&all_edge_list);

	char radius[_CVTBUFSIZE];
	_gcvt( _radius, 12, radius );
	
	Feature* pFeature = (Feature*) (GetPart()->GetFeatureByName(_basefeaturename));
	

		UF_MODL_ask_list_item (pFeature->_ugFeatList, 0, &mainfeature);
		UF_MODL_ask_feat_body(mainfeature,&mainbody);

		UF_MODL_ask_body_feats(mainbody, &featList);
		UF_MODL_ask_list_item (featList, 0, &mainfeature);
		UF_MODL_ask_feat_body(mainfeature,&mainbody);
		UF_MODL_ask_body_edges(mainbody, &all_edge_list);
		UF_MODL_ask_list_count(all_edge_list, &edge_count);

		printf("\n%d: edge_count\n",edge_count);


	for(int index = 0; index < edge_count; index++)
	{
		double p1[3];
		double p2[3];
		UF_MODL_ask_list_item(all_edge_list, index, &edge_id);
		UF_MODL_ask_edge_verts(edge_id, p1, p2, &vertex);
		if (p1[0]==_point1[0]&&p1[1]==_point1[1]&&p1[2]==_point1[2]&&
			p2[0]==_point2[0]&&p2[1]==_point2[1]&&p2[2]==_point2[2])
		{
			printf("yes\n");
			edgeNo=index;
		}
		else ;//printf("no\n");
	}

	if(edgeNo==-1)
	{	
		UF_EVAL_p_t eval;
		double limits[2];
		double paramout[2];
		double p1[3];
		for(int index = 0; index < edge_count; index++)
		{
			UF_MODL_ask_list_item(all_edge_list, index, &edge_id);
			UF_CALL(UF_EVAL_initialize(edge_id, &eval));
			UF_CALL(UF_EVAL_ask_limits(eval, limits));

			UF_CALL(UF_EVAL_evaluate_closest_point(eval,_point1 , paramout, p1));

			//cout << limits[0] << "  "<<limits[1] <<endl;

			cout<<endl<<endl<<" "<<p1[0]<<" "<<p1[1]<<" "<<p1[2]<<endl<<endl;

			if (pow(pow(p1[0]-_point1[0],2)+pow(p1[1]-_point1[1],2)+pow(p1[2]-_point1[2],2),.5)<=0.00000001)
			{
				printf("yes\n");
				edgeNo=index;
			}
			else ;//printf("no\n");
		}
	}

	UF_MODL_ask_list_item(all_edge_list,edgeNo,&edge_id);
	UF_MODL_put_list_item(_ugBlendEdgeList,edge_id);

	int nCount = 0;
	UF_MODL_ask_list_count(_ugBlendEdgeList, &nCount);

	if (!nCount)
	{
		cout << "  " << "-> No Edges to be filleted!" << endl;
		return;
	}

	UF_MODL_create_blend(radius, _ugBlendEdgeList, 0, 0, 0, 0.001, &_ugTag);


	UF_MODL_delete_list(&_ugBlendEdgeList);
	UF_MODL_delete_list(&all_edge_list);


}

void FeatureSOLIDOperateFilletingFilletConstant::ExtractBaseFeature(string Refename)
{
	for (int i=0;i<20;i++)
	{
		if(Refename[i]==44) break;
		_basefeaturename[i]=Refename[i];
	}
}

