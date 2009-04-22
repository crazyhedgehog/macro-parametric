#pragma once

#include "Feature.h"

class Part;
class FSketch;

class FeatureSOLIDCreateProtrusionSweep :
	public Feature
{
public:
	FeatureSOLIDCreateProtrusionSweep(Part * pPart, TransCAD::IFeaturePtr spFeature);
	virtual ~FeatureSOLIDCreateProtrusionSweep(void);

	FSketch * GetProfileSketch() {return _profileSketch;}
	FSketch * GetGuideSketch() {return _guideSketch;}

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

private:
	FSketch * _profileSketch;
	FSketch * _guideSketch;
};
