// SVN

#include ".\part.h"

#include <iostream>
#include <fstream>
#include <uf_part.h>
#include <uf_obj.h>
#include <uf_modl.h>
#include <uf_object_types.h>

#include "Feature.h"
#include "FDatumPlane.h"
#include "FSketch.h"
#include "FSOLIDCreateProtrusionExtrude.h"
#include "FSOLIDCreateCutExtrude.h"
#include "FSOLIDOperateFilletingFilletConstant.h"
#include "FSOLIDCreateProtrusionSweep.h"
#include "FSOLIDCreateProtrusionRevolve.h"
#include "FSOLIDCreateCutRevolve.h"


using namespace std;

Part::Part(string fileName)
{
	// Init TransCAD related members
	_fileName  = fileName;

	TransCAD::IDocumentsPtr spDocuments = g_spApplication->Documents;
	_spDocument = spDocuments->AddPartDocument();
	_spPart = _spDocument->Part;
	_spFeatures = _spPart->Features;

	// Open UG Part File
	_bFileOpened = false;
	PartFileOpen();
}

Part::~Part(void)
{
	Clear();
}

void Part::Clear()
{
	std::vector<Feature *>::iterator i = _featureList.begin();
	while (i != _featureList.end()) {delete *i; i++;}
	_featureList.clear();
}

void Part::PartFileOpen()
{
	char fileName[256];
	strcpy(fileName, _fileName.c_str());
	UF_PART_load_status_t errorStatus;

	// open UG file to get Part Tag int _partTag
    int status = UF_PART_open(fileName, &_partTag, &errorStatus);
	UF_free_string_array( errorStatus.n_parts, errorStatus.file_names );	//UF_PART_open()
	UF_free( errorStatus.statuses );										//UF_PART_open()
	
	if(status)	// cannot open file
	{
		cerr << "Cannot open file '" << _fileName << "'" << endl;
		return;
	}
	else
        cout << endl <<  "UG Macro File : " << _fileName << ":" << _partTag << "  Opened" << endl << endl;

    _bFileOpened = true;
}

Feature * Part::GetFeatureByTag(tag_t fTag) const
{
	for (unsigned int i=0; i < GetFeaturesSize() ; ++i)
		if ( fTag == ( (GetFeature(i))->GetFTag() ) )
			return GetFeature(i);
	return 0;
}

Feature * Part::CreateFeature(tag_t fTag)
{
	bool bNoComment = 0;

	// get feature Type and Name
	char * featureType;
	char * featureName;
	UF_MODL_ask_feat_type(fTag, &featureType);	// UF_free() required
    UF_MODL_ask_feat_name(fTag, &featureName);	// UF_free() required
	
	// DEBUG
	cout << (unsigned int)(GetFeaturesSize()) << " [" << fTag << "] " << featureType ;
	cout << " --> ";

	// create a feature
	Feature * pFeature = 0;

	//==========  ABSOLUTE_DATUM_PLANE : <SELECT_Reference_Plane>  ==========//
	if(!strcmp(featureType, "ABSOLUTE_DATUM_PLANE"))
	{
		pFeature = new FDatumPlane(this,fTag);
		cout << "FDatumPlane Constructed" << endl;
	}

	//==========  ABSOLUTE_DATUM_AXIS : No feature  ==========//
	if(!strcmp(featureType, "ABSOLUTE_DATUM_AXIS"))
	{
		cout << "*** Need not translate *** " << endl;
		bNoComment = 1;;
	}

	//==========  "SKETCH" : SketchFeature  ==========//
	else if(!strcmp(featureType, "SKETCH"))
	{
		pFeature = new FSketch(this,fTag);
		cout << "FSketch Constructed" << endl;
	}

	//==========  "SWP104" : Extrude, Sweep, Revolve  ==========//
	else if(!strcmp(featureType, "SWP104"))			
	{
		UF_FEATURE_SIGN sign;						// UF_NULLSIGN = 0, create new target solid
		UF_MODL_ask_feature_sign(fTag, &sign);		// UF_POSITIVE = 1, add to target solid
													// UF_NEGATIVE = 2, subtract from target solid
		
		//==========  Extrude  ==========//
		if(!_strnicmp(featureName, "E", 1))
		{
			if (sign < 2)	{		// Protrusion
				pFeature = new FSOLIDCreateProtrusionExtrude(this,fTag);
				cout << "SOLIDCreateProtrusionExtrude Constructed" << endl;
			}
			
			else if (sign == 2)	{	// Cut
				pFeature = new FSOLIDCreateCutExtrude(this,fTag);
				cout << "SOLIDCreateCutExtrude Constructed" << endl;
			}
		}

		//==========  SWEEP  ==========//
		else if(!_strnicmp(featureName, "S", 1))
		{
			if (sign < 2) {			// Protrusion
				pFeature = new FSOLIDCreateProtrusionSweep(this,fTag);
				cout << "SOLIDCreateProtrusionSweep Constructed" << endl;
				bNoComment = 1;
			}
			else if (sign == 2)	{	// Cut
				//pFeature = new FSOLIDCreateCutSweep(this,fTag);
				cout << "SOLIDCreateCutSweep under construction" << endl;
				bNoComment = 1;
			}
		}
		
		//==========  Revolve  ==========//
		else if(!_strnicmp(featureName, "R", 1)) 
		{
			if((sign == 1) || (sign == 0)) {	// Protrusion
				pFeature = new FSOLIDCreateProtrusionRevolve(this,fTag);
				cout << "SOLIDCreateProtrusionRevolve Constructed" << endl;
			}
			else if(sign == 2)	{				// Cut
				pFeature = new FSOLIDCreateCutRevolve(this,fTag);
				cout << "SOLIDCreateCutRevolve Constructed" << endl;
			}
		}

		//==========  Unknown SWEEP ==========//
		else
		{
			cout << "Unknown SWEEP104 Type, featureName = " << featureName << endl;
			bNoComment = 1;
		}

	}

	//----------  BLEND : <SOLID_Operate_Filleting_Fillet_Constant>  ----------//
	else if(!strcmp(featureType, "BLEND"))
	{
		cout << "SOLIDOperateFilletingFilletConstant constructed" << endl;
		pFeature = new FSOLIDOperateFilletingFilletConstant(this, fTag);
	}

	if (pFeature)
		_featureList.push_back(pFeature);	// put into _featureList
	else if (!bNoComment)
		cerr << "*** Not Supported Yet!!! ***" << endl;

	// delete memory
	UF_free(featureType);	// UF_MODL_ask_feat_type(fTag, &featureType);
	UF_free(featureName);	// UF_MODL_ask_feat_name(fTag, &featureName);

	return pFeature;
}


void Part::GetUGInfo()
{
	tag_t fTag = NULL_TAG;
	Feature * pFeature;
	
	//-------  Loop to create features list in a part tag --------//
	
	// get a feature tag
	UF_OBJ_cycle_objs_in_part(GetPartTag(), UF_feature_type, &fTag);
	
	while(fTag != NULL_TAG)
	{
		pFeature = CreateFeature(fTag);	// Create a Feature Class

		// get a feature tag
		UF_OBJ_cycle_objs_in_part(GetPartTag(), UF_feature_type, &fTag);
	}	
	
	cout << endl << "Press any key to Translate...";
	WaitGetEnter();

	//-------  Loop to translate features in list  --------//
	for ( size_t i=0 ; i < GetFeaturesSize() ; ++i )
	//for ( size_t i=0 ; i < 16 ; ++i )
	{
		//DEBUG
		cout << "Index(" << (unsigned int)i << ") feature[" << this->GetFeature((unsigned int)i)->GetFTag() << "] is being translated." << endl;
		
		GetFeature((unsigned int)i)->GetUGInfo();
	}
	
	cout << endl << "Press any key to write into \"TransCAD\"..." ;
	WaitGetEnter();
}


void Part::ToTransCAD()
{
	//-------  Loop to write features into TransCAD  --------//
	for ( size_t i=0 ; i < GetFeaturesSize() ; ++i )
	//for ( size_t i=0 ; i < 16 ; ++i )
	{
		//DEBUG
		cout << "Feature Index(" << (unsigned int)i << ") feature [" << this->GetFeature((unsigned int)i)->GetFTag() << "]is written into TransCAD" << endl;
		GetFeature((unsigned int)i)->ToTransCAD();
	}
	string str = _fileName;
	str.resize (str.size()-4);
	str = string("c:\\")+str+string(".xml");
	_spDocument->SaveAs(str.c_str());
}