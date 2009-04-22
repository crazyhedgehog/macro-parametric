#include ".\FeatureSOLIDCreatePatternRect.h"
#include <iostream>
#include <uf_modl.h>
#include <uf_trns.h>
#include <uf_group.h>
#include <uf_assem.h>

#include "Part.h"

FeatureSOLIDCreatePatternRect::FeatureSOLIDCreatePatternRect(Part * pPart, TransCAD::IFeaturePtr spFeature)
: Feature(pPart,spFeature)
{
	
}

FeatureSOLIDCreatePatternRect::~FeatureSOLIDCreatePatternRect(void)
{
}

void FeatureSOLIDCreatePatternRect::GetInfo(void)
{
	TransCAD::IStdSolidOperatePatternRectangularFeaturePtr spFeature = GetTransCADFeature();

	TransCAD::IReferencePtr spTargetFeature = spFeature->TargetFeature;
	_featurename = spTargetFeature->ReferenceeName;
	
	_colnumber = spFeature->ColumnNumber;
	_rownumber = spFeature->RowNumber;

	_colspacing =  spFeature->ColumnSpacing;
	_rowspacing= spFeature->RowSpacing;

	spFeature->GetColumnDirection(&_coldir[0],&_coldir[1],&_coldir[2]);
	spFeature->GetRowDirection(&_rowdir[0],&_rowdir[1],&_rowdir[2]);

}

void FeatureSOLIDCreatePatternRect::ToUG(void)
{
	
	Feature * pFeature =(Feature*) (GetPart()->GetFeatureByName(_featurename));
	
	tag_t 	feature, object, new_object, new_new_object, group, *ref_sets;

	uf_list_p_t feat_list;
	

	if(_featurename[0]!='C'){
		UF_MODL_ask_list_item(pFeature->_ugFeatList,0,&feature);
		int 	zero = 0, one = 1,  two = 2, resp, ii, n_ref_sets;
	
	
		double mx[12],delta[3];
	
		UF_MODL_ask_list_item(pFeature->_ugFeatList,0,&feature);
		UF_MODL_ask_feat_body(feature,&object);

		for (int j=1;j<_colnumber;j++){
			delta[0] = _coldir[0]*_colspacing*j;		delta[1] = _coldir[1]*_colspacing*j;		delta[2] = _coldir[2]*_colspacing*j;
			FTN(uf5943)(delta,mx);
			FTN(uf5947)(mx, &object, &one, &two, &zero, &two, &new_object, NULL, &resp);
		}

		for (int i=1;i<_rownumber;i++){
			delta[0] = _rowdir[0]*_rowspacing*i;		delta[1] = _rowdir[1]*_rowspacing*i;		delta[2] = _rowdir[2]*_rowspacing*i;
			FTN(uf5943)(delta,mx);
			FTN(uf5947)(mx, &object, &one, &two, &zero, &two, &new_object, NULL, &resp);
			
			for (int j=1;j<_colnumber;j++){
				delta[0] = _coldir[0]*_colspacing*j;		delta[1] = _coldir[1]*_colspacing*j;		delta[2] = _coldir[2]*_colspacing*j;
				FTN(uf5943)(delta,mx);
				FTN(uf5947)(mx, &new_object, &one, &two, &zero, &two, &new_new_object, NULL, &resp);
			}
		}
	}
	else {
	//	cout<<_coldir[0]<<_coldir[1]<<_coldir[2]<<_rowdir[0]<<_rowdir[1]<<_rowdir[2];

	_rowspacing = _rowspacing *(_rowdir[0]+_rowdir[1]+_rowdir[2]);
	_colspacing = _colspacing *(_coldir[0]+_coldir[1]+_coldir[2]);


		_gcvt(_colnumber, MAX_DIGITS, _colnumberc);
		_gcvt(_rownumber, MAX_DIGITS, _rownumberc);
		_gcvt(_colspacing, MAX_DIGITS, _colspacingc);
		_gcvt(_rowspacing, MAX_DIGITS, _rowspacingc);

		
		UF_MODL_ask_list_item(pFeature->_ugFeatList,0,&feature);

		UF_CALL(UF_MODL_create_list(&feat_list));

		UF_CALL(UF_MODL_put_list_item(feat_list,feature));

		int r=(UF_MODL_create_linear_iset(0,_rownumberc,"-160",_colnumberc,"-160", feat_list,&_ugTag));

	
	}
	


}

