#include ".\Part.h"

#include <iostream>
#include <uf_part.h>
#include <uf_modl.h>

#include "Feature.h"
#include "FDatumPlane.h"
#include "FSketch.h"
#include "FeatureSOLIDCreateProtrusionExtrude.h"
#include "FeatureSOLIDCreateCutExtrude.h"
#include "FeatureSOLIDOperateFilletingFilletConstant.h"
#include "FeatureSOLIDCreateProtrusionSweep.h"
#include "FeatureSOLIDCreateProtrusionRevolve.h"
#include "FeatureSOLIDCreateFilletingChamfer.h"
#include "FeatureSOLIDCreateCutRevolve.h"
#include "FeatureSOLIDCreatePatternRect.h"
#include "FeatureSOLIDCreatePatternCirc.h"
using namespace std;

Part::Part(string fileName)
{
	// Set TransCAD Document Ptr
	TransCAD::IDocumentsPtr spDocuments = g_spApplication->Documents;
	//under constructionn : _spDocument = spDocuments->Open(CString(fileName.c_str()));
	
	_spPart = _spDocument->Part;		// Set TransCAD Part Ptr
	_spFeatures = _spPart->Features;	// Set TransCAD Features Ptr
	_strPartName = _spDocument->FullName;	// Set Part file name
	cout << "FileName : " << _strPartName << endl;	//DEBUG
}

Part::Part()
{
	// Set TransCAD Active Document Ptr
	_spDocument = g_spApplication->ActiveDocument;
	if(_spDocument == NULL) {
		cout << " spDocument is Null " << endl;
		return;
	}

	_spPart = _spDocument->Part;		// Set TransCAD Part ptr
	_spFeatures = _spPart->Features;	// Set TransCAD Features ptr
	_strPartName = _spDocument->FullName;	// Set Part file name
	cout << "FileName : " << _strPartName << endl;	//DEBUG
}

Part::~Part(void)
{
	Clear();
}

void Part::Clear()
{
	std::vector<Feature *>::iterator i = _featureList.begin();
	while ( i != _featureList.end() ) {
		delete *i;
		i++;
	}
	_featureList.clear();
}

Feature * Part::GetFeatureByName(string name)
{
	for ( size_t i=0 ; (unsigned int)i < GetSize() ; ++i )	{
		Feature * pFeature = GetFeature((int)i);
		if ( name == pFeature->GetFeatureName()) return pFeature;
	}	
	return NULL;
}

void Part::CreateUGPart()
{
	// set UG file name for Save
	char ugFileName[256];
	if (_strPartName==string(""))
		_strUGName = string("C:\\Part");	// Default UG file name
	else
		_strUGName = _strPartName;
	strcpy(ugFileName, _strUGName.c_str());

	// create UG pPart file & set UG pPart tag
	int unit = 1;	// 1 : Metric, 2 : English
	int status = 0;
	int fileNum = 0;
	string fileName("");
	while (status=UF_PART_new(ugFileName, unit, &_pTag)) {
		char buffer[3];
		_itoa(fileNum ++ , buffer, 10 );
		fileName = _strUGName + string(buffer);
		strcpy(ugFileName, fileName.c_str());
		if (fileNum >20) { cerr << "Cannot Open UG File!!!" << endl; exit(-1);}
	}
	_strUGName = fileName;

	//DEBUG
	cout << endl <<  "UG PartFile : " << _strUGName << ".prt (" << _pTag << ") Created" << endl << endl;
}

void Part::SaveUGPart()
{
	int status = UF_PART_save();
	if (status) {
		cerr << "Cannot save UG file" << endl;
		exit(-1);
	}
	//DEBUG
	cout << endl << " -> " << " Save UG Part File \"" << GetUGFileName() << ".prt\"" << endl;
}

Feature * Part::CreateFeature(TransCAD::IFeaturePtr spFeature)
{
	Feature * pFeature = 0;
	
	switch(spFeature->Type)
	{
	case TransCAD::StdDefaultDatumPlaneFeature :
		pFeature = new FDatumPlane(this, spFeature);
		cout << " -> " << "FDatumPlane created" << endl;
		break;
	case TransCAD::StdSketchFeature:
		pFeature = new FSketch(this,spFeature);
		cout << " -> " << "FSketch created" << endl;
		break;
	case TransCAD::StdSolidProtrusionExtrudeFeature:
		pFeature = new FeatureSOLIDCreateProtrusionExtrude(this,spFeature);
		cout << " -> " << "FeatureSOLIDCreateProtrusionExtrude created" << endl;
		break;
	case TransCAD::StdSolidCutExtrudeFeature:
		pFeature = new FeatureSOLIDCreateCutExtrude(this,spFeature);
		cout << " -> " << "FeatureSOLIDCreateCutExtrude created" << endl;
		break;
	case TransCAD::StdSolidFilletConstantFeature:
		pFeature = new FeatureSOLIDOperateFilletingFilletConstant(this, spFeature);
		cout << " -> " << "FeatureSOLIDOperateFilletingFilletConstant created" << endl;
		break;
	case TransCAD::StdSolidProtrusionSweepFeature:
		pFeature = new FeatureSOLIDCreateProtrusionSweep(this, spFeature);
		cout << " -> " << "FeatureSOLIDCreateProtrusionSweep created" << endl;
		break;
	case TransCAD::StdSolidProtrusionRevolveFeature:
		pFeature = new FeatureSOLIDCreateProtrusionRevolve(this, spFeature);
		cout << " -> " << "FeatureSOLIDCreateProtrusionRevolve created" << endl;
		break;
	case TransCAD::StdSolidChamferFeature:
		pFeature = new FeatureSOLIDCreateFilletingChamfer(this, spFeature);
		cout << " -> " << "FeatureSOLIDCreateFilletingChamfer created" << endl;
		break;
	case TransCAD::StdSolidCutRevolveFeature:
		pFeature = new FeatureSOLIDCreateCutRevolve(this,spFeature);
		cout << " -> " << "FeatureSOLIDCreateCutRevolve created" << endl;
		break;
	case TransCAD::StdSolidOperatePatternRectangularFeature:
		pFeature = new FeatureSOLIDCreatePatternRect(this,spFeature);
		cout << " -> " << "FeatureSOLIDCreatePatternRect created" << endl;
		break;
	case TransCAD::StdSolidOperatePatternCircularFeature:
		pFeature = new FeatureSOLIDCreatePatternCirc(this,spFeature);
		cout << " -> " << "FeatureSOLIDCreatePatternCirc created" << endl;
		break;

	}	

	if(pFeature) _featureList.push_back(pFeature);
	
	return pFeature;	// return ptr of the feature class
}

void Part::GetInfo()
{
	cout << "[[ Constructing Features ]]" << endl; //DEBUG
	
	for ( int i=1 ; i <= _spFeatures->Count ; ++i )	{
		
		Feature * pFeature = CreateFeature(_spFeatures->Item[i]);
		
		if(!pFeature) {cerr << "** Cannot support this feature type yet! **" << endl;}
	}

	cout << endl << "Press enter to Translate...(under Construction)";
	char c1;	
	scanf("%c", &c1);

	//-------  Get TransCAD Features information into _featureList  --------//
	for ( i=0 ; (unsigned int)i < GetSize() ; ++i )	{
	//for ( i=0 ; (unsigned int)i < 5 ; ++i )	{
		cout << "Index(" << i << ") " << GetFeature(i)->GetFeatureName() << " feature is being translated." << endl;	//DEBUG
		GetFeature(i)->GetInfo();
	}
}

void Part::ToUG()
{
	cout << endl << "Press enter to write into \"TransCAD\"...(under Construction)" ;
	char c2;
	scanf("%c", &c2);

	CreateUGPart();		// create UG Part File & set _pTag

	//-------  Loop to get features information into UG  --------//
	for(int i = 0; (unsigned int)i < GetSize(); ++i)	GetFeature(i)->ToUG();
	//for(int i = 0; (unsigned int)i < 5; ++i)	GetFeature(i)->ToUG();

	SaveUGPart();		// save UG Part File
}