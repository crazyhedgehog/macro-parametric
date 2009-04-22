#pragma once
#include "feature.h"


class Part;
class FSketch;

class FeatureSOLIDCreateCutRevolve :
	public Feature
{
public:
	FeatureSOLIDCreateCutRevolve(Part * pPart, TransCAD::IFeaturePtr spFeature);
	virtual ~FeatureSOLIDCreateCutRevolve(void);
	FSketch * GetFeatureProfileSketch() {return _featureProfileSketch;}

	virtual void GetInfo();
	virtual void ToUG();

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
