#pragma once

#include ".\UGPre.h"

#include <fstream>
#include <string>
#include <vector>

#include <uf.h>

using namespace std;

class Feature;
class FDatumPlane;

class Part
{
public:
	Part(string fileName);
	~Part(void);
	void Clear();

	void PartFileOpen();
	tag_t GetPartTag() const {return _partTag;}
	string GetFileName() const {return _fileName;}
	bool IsUGFileOpen() const {return _bFileOpened;}

	Feature * GetFeature(int index) const {return _featureList.at(index);}
	tag_t GetFeatureTag(int index) const {return _tagList.at(index);}
	size_t GetFeatureTagSize() const {return _tagList.size();}
	Feature * GetFeatureByTag(tag_t featurTag) const;
	size_t GetFeaturesSize() const {return _featureList.size();}

protected:
	Feature * CreateFeature(tag_t,int);

public:
	void GetUGInfo();
	void ToTransCAD();

public:
	TransCAD::IPartDocumentPtr  _spDocument;	// TransCAD a document pointer
	TransCAD::IPartPtr _spPart;					// TransCAD part class pointer
	TransCAD::IFeaturesPtr _spFeatures;			// TransCAD Featurs pointer

private:
	string		_fileName;					// UG partfile name
	tag_t		_partTag;					// UG partfile tag
	std::vector<Feature*> _featureList;		// UG feature list from partfile
	std::vector<tag_t> _tagList;
	bool		_bFileOpened;
};