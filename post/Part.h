#pragma once

#include ".\postug.h"

#include <fstream>
#include <string>
#include <vector>

#include <uf.h>

class Feature;

using namespace std;

class Part
{
public:

	Part();
	Part(string fileName);
	~Part(void);
	void Clear();

    string GetPartName() const {return _strPartName;}
	string GetUGFileName() {return _strUGName;}
	Feature * GetFeature(int i) const {return _featureList.at(i);}
	Feature * GetFeatureByName(string name);
	size_t GetSize() const {return _featureList.size();}
	tag_t GetPartTag() {return _pTag;}
	void GetInfo();
	void ToUG();

protected:
	void CreateUGPart();
	void SaveUGPart();
	Feature * CreateFeature(TransCAD::IFeaturePtr spFeature);
	
public:
	TransCAD::IPartDocumentPtr	_spDocument;
	TransCAD::IPartPtr			_spPart;
	TransCAD::IFeaturesPtr		_spFeatures;

private:
	tag_t	_pTag;
	string	_strPartName;	// TransCAD Part full path name
	string	_strUGName;		// UG Partfile full path Name
	vector<Feature*> _featureList;
};