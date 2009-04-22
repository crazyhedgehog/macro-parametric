#pragma once
#include <string>
//#include <uf.h>

#include ".\postug.h"
#include "Definition.h"

using namespace std;

class Part;

class Feature
{
public:
	Feature(Part * pPart, TransCAD::IFeaturePtr spFeature);
	virtual ~Feature(void);

	Part*	GetPart() {return _pPart;}

	void	SetFeatureName(string featureName) {_strName = featureName;}
	size_t	GetFeatureIndex() {return _nIndex;}
	string	GetFeatureName() {return _strName;}
	TransCAD::IFeaturePtr GetTransCADFeature() {return _spFeature;}

	virtual void GetInfo() {};
	virtual void ToUG() {};

public:
	tag_t	_ugTag;
	uf_list_p_t _ugFeatList;

protected:
	Part*	_pPart;
	size_t	_nIndex;
	string	_strName;
	TransCAD::IFeaturePtr _spFeature;

};
