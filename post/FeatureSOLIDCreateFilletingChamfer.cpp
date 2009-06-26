#include ".\featuresolidcreatefilletingchamfer.h"

#include <iostream>
#include <uf_modl.h>
#include <uf_eval.h>
#include <cmath>
#include "Part.h"

using namespace std;

FeatureSOLIDCreateFilletingChamfer::FeatureSOLIDCreateFilletingChamfer(Part * pPart, TransCAD::IFeaturePtr spFeature)
: Feature(pPart,spFeature)
{
	_ugChamferEdgeList=0;
	memset(_basefeaturename,0,100);
}

FeatureSOLIDCreateFilletingChamfer::~FeatureSOLIDCreateFilletingChamfer(void)
{
	if (_ugChamferEdgeList)
		UF_MODL_delete_list(&_ugChamferEdgeList);
}

void FeatureSOLIDCreateFilletingChamfer::GetInfo(void)
{
	TransCAD::IStdSolidChamferFeaturePtr spFeature = GetTransCADFeature();
	
	TransCAD::IReferencePtr spEdge = spFeature->SelectedEdge;
	string _featurename =  spEdge->ReferenceeName;

	_value = spFeature->Value;
	_length = spFeature->Length;

	_point1[0]=spFeature->StartPosX;
	_point1[1]=spFeature->StartPosY;
	_point1[2]=spFeature->StartPosZ;

	_point2[0]=spFeature->EndPosX;
	_point2[1]=spFeature->EndPosY;
	_point2[2]=spFeature->EndPosZ;

	UF_MODL_create_list(&_ugChamferEdgeList);
	ExtractBaseFeature(_featurename);


 }

void FeatureSOLIDCreateFilletingChamfer::ToUG(void)
{
	char value[_CVTBUFSIZE];
	char length[_CVTBUFSIZE];
	_gcvt( _value, 12, value );
	_gcvt( _length, 12, length );

	tag_t mainfeature,mainbody,edge_id;
	uf_list_p_t featList,all_edge_list;

	int vertex,edge_count,edgeNo=-1;	

	UF_MODL_create_list(&featList);
	UF_MODL_create_list(&all_edge_list);
	
	Feature* pFeature = (Feature*) (GetPart()->GetFeatureByName(_basefeaturename));

	UF_MODL_ask_list_item (pFeature->_ugFeatList, 0, &mainfeature);
	UF_MODL_ask_feat_body(mainfeature,&mainbody);

	UF_MODL_ask_body_feats(mainbody, &featList);
	UF_MODL_ask_list_item (featList, 0, &mainfeature);
	UF_MODL_ask_feat_body(mainfeature,&mainbody);
	UF_MODL_ask_body_edges(mainbody, &all_edge_list);
	UF_MODL_ask_list_count(all_edge_list, &edge_count);

	printf("\n%d: edge_count\n",edge_count);
	cout<<endl<<"selected edge"<<" "<<_point1[0]<<" "<<_point1[1]<<" "<<_point1[2]<<endl;
	cout<<endl<<"             "<<" "<<_point2[0]<<" "<<_point2[1]<<" "<<_point2[2]<<endl<<endl;
	for(int index = 0; index < edge_count; index++)
	{
		double p1[3];
		double p2[3];
		
		UF_MODL_ask_list_item(all_edge_list, index, &edge_id);
		
		UF_MODL_ask_edge_verts(edge_id, p1, p2, &vertex);

		printf("\n\nTRACE\n\n");

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

			if (pow(pow(p1[0]-_point1[0],2)+pow(p1[1]-_point1[1],2)+pow(p1[2]-_point1[2],2),.5)<=0.001)
			{
				printf("yes\n");
				edgeNo=index;
			}
			else ;//printf("no\n");
		}
	}

	UF_MODL_ask_list_item(all_edge_list,edgeNo,&edge_id);
	UF_MODL_put_list_item(_ugChamferEdgeList,edge_id);

	UF_MODL_ask_list_count(_ugChamferEdgeList, &edge_count);

	UF_MODL_create_chamfer(2,value,length,"45",_ugChamferEdgeList,&_ugTag);
	
	UF_MODL_delete_list(&_ugChamferEdgeList);
	UF_MODL_delete_list(&all_edge_list);

}

void FeatureSOLIDCreateFilletingChamfer::ExtractBaseFeature(string Refename)
{
	for (int i=0;i<20;i++)
	{
		if(Refename[i]==44) break;
		_basefeaturename[i]=Refename[i];
	}
}
