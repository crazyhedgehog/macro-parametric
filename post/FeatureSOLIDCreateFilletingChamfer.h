#pragma once
#include "feature.h"
#include <iostream>

class Part;

class FeatureSOLIDCreateFilletingChamfer :
	public Feature
{
public:
	FeatureSOLIDCreateFilletingChamfer(Part * pPart, TransCAD::IFeaturePtr spFeature);

	virtual ~FeatureSOLIDCreateFilletingChamfer(void);

	

	virtual void GetInfo(void);
	virtual void ToUG(void);
	
	

protected:
	uf_list_p_t _ugChamferEdgeList;
	
	double  _point1[ 3 ];
	double  _point2[ 3 ]; 
	
	double	_value;
	double	_length;

	char _basefeaturename[100];
   
public:
	void ExtractBaseFeature(string Refename);
};
