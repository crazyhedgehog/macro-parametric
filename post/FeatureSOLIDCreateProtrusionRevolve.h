#pragma once

#include "Feature.h"

class Part;
class FSketch;

class FeatureSOLIDCreateProtrusionRevolve :
	public Feature
{
public:
	FeatureSOLIDCreateProtrusionRevolve(Part * pPart, TransCAD::IFeaturePtr spFeature);
	virtual ~FeatureSOLIDCreateProtrusionRevolve(void);

	FSketch * GetFeatureProfileSketch() {return _featureProfileSketch;}

	virtual void GetInfo();
	virtual void ToUG();

public:
	bool	_flip;
	EndType	_startCondition;
	double	_startAngle;
	char	_sA[MAX_CHAR_LIMIT];
	EndType	_endCondition;
	double	_endAngle;
	char	_eA[MAX_CHAR_LIMIT];
	
protected:
	FSketch * _featureProfileSketch;
};
