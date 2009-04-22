#pragma once
#include "feature.h"
#include "FSketch.h"
#include <iostream>


class Part;
class FSketch;

class FeatureSOLIDCreatePatternCirc:
	public Feature
{
public:
	FeatureSOLIDCreatePatternCirc(Part * pPart, TransCAD::IFeaturePtr spFeature);
	virtual ~FeatureSOLIDCreatePatternCirc(void);

	string _featurename;

	char _angleincrement[MAX_CHAR_LIMIT];
	double _rowspacing;
	char  _patternnumber[MAX_CHAR_LIMIT];
	bool _isradial;
	double _ptorg[3];
	double _ptvec[3];


	virtual void GetInfo(void);
	virtual void ToUG(void);
};
