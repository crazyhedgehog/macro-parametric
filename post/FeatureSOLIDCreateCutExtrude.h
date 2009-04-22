#pragma once

#include "Feature.h"

class Part;
class FSketch;

class FeatureSOLIDCreateCutExtrude :
	public Feature
{
public:
	FeatureSOLIDCreateCutExtrude(Part * pPart, TransCAD::IFeaturePtr spFeature);
	virtual ~FeatureSOLIDCreateCutExtrude(void);
	
	FSketch * GetFeatureProfileSketch() {return _featureProfileSketch;}

	virtual void GetInfo();
	virtual void ToUG();

public:
	bool	_flip;
	EndType	_startCondition;
	double	_startDepth;
	char	_sD[MAX_CHAR_LIMIT];
	EndType	_endCondition;
	double	_endDepth;
	char	_eD[MAX_CHAR_LIMIT];

protected:	
	FSketch * _featureProfileSketch;
};
