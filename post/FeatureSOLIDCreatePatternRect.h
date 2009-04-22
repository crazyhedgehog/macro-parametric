#pragma once
#include "feature.h"
#include "FSketch.h"
#include <iostream>

class Part;
class FSketch;

class FeatureSOLIDCreatePatternRect :
	public Feature
{
public:
	FeatureSOLIDCreatePatternRect(Part * pPart, TransCAD::IFeaturePtr spFeature);
	virtual ~FeatureSOLIDCreatePatternRect(void);

	string _featurename;

	double _colspacing;
	double _rowspacing;
	int _colnumber;
	int _rownumber;
	double _coldir[3];
	double _rowdir[3];

	char _colnumberc[MAX_CHAR_LIMIT];
	char _rownumberc[MAX_CHAR_LIMIT];
	char _colspacingc[MAX_CHAR_LIMIT];
	char _rowspacingc[MAX_CHAR_LIMIT];

	virtual void GetInfo(void);
	virtual void ToUG(void);
};
