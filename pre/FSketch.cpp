#include ".\FSketch.h"


#include <iostream>

#include <uf_modl.h>
#include <uf_sket.h>
#include <uf_obj.h>

#include "Part.h"
#include "FSKETCHCreate2DLIne2Points.h"
#include "FSKETCHCreate2DCircleCenterPoint.h"
#include "FSKETCHcreate2DArcCenterEnds.h"
//#include "FSKETCHCreate2DArc3Points.h"

using namespace std;

int FSketch::_nSketCnt = 0;


FSketch::FSketch(Part * part, tag_t fTag) :
	Feature(part,fTag)
{
	//---------- Get sketchTag of fTag----------//
	uf_list_p_t object_list;

	// Returns all sketchTags associated with fTag
	UF_CALL(UF_SKET_ask_feature_sketches( fTag, &object_list));
	
	// set the first to _sketTag 
	UF_CALL(UF_MODL_ask_list_item (object_list, 0, &_sketTag ));
	UF_MODL_delete_list(&object_list);

	// get Sketch Info from _sketTag
	UF_CALL(UF_SKET_ask_sketch_info (_sketTag, &_ugSketInfo));
	for (int i=0 ; i < 12 ; i++ )
		_sketInfo[i] = ValRnd(_ugSketInfo.csys[i]);
}

FSketch::~FSketch(void)
{
	Clear();
}

void FSketch::Clear()
{
	std::vector<Feature*>::iterator i = _sketObjList.begin();
	while ( i != _sketObjList.end() )	{delete *i; i++;}
	_sketObjList.clear();
}

Feature * FSketch::GetCLine()
{
	for (size_t i=0; i < GetSketObjSize() ; i++)
	{
		Feature * pFeature = GetSketObj((int)i);
		if ( pFeature->GetFType() == SKETCH_Create_2D_Centerline )
			return pFeature;
	}
    return 0;
}

void FSketch::SetCLine(Feature* pFeature)
{
	if (GetCLine()) return;
	_sketObjList.insert(_sketObjList.begin(), pFeature);
}

Feature * FSketch::CreateSketObj(tag_t objectTag)
{
	Feature * pSketchObjectFeature = 0;
	
	int curve_type;
	int curve_subtype;
	UF_CALL(UF_OBJ_ask_type_and_subtype (objectTag, &curve_type, &curve_subtype));
	
	//DEBUG
	cout << "  " << (unsigned int)(this->GetSketObjSize()) << " : CurveType=" << curve_type << ", SubType=" << curve_subtype;
	cout << " --> ";

	switch (curve_type) {
		case 3 : // Line
			pSketchObjectFeature = new FSKETCHCreate2DLine2Points(GetPart(), objectTag, this);
			cout << "SKETCHCreate2DLine2Points Constructed" << endl;
			break;
		case 5 : // Arc, Circle
			UF_CURVE_arc_t ugArc;
			UF_CALL(UF_CURVE_ask_arc_data( objectTag, &ugArc ) );
			
			//----------  Circle : SKETCHCreate2DCircleCenterPoint  ----------//
			if ( (ugArc.end_angle - ugArc.start_angle) >= (2*PI) )
			{
				pSketchObjectFeature = new FSKETCHCreate2DCircleCenterPoint(GetPart(), objectTag, this);
				cout << "SKETCHCreate2DCircleCenterPoint Constructed" << endl;
			}
			//----------  Arc : SKETCHcreate2DArcCenterEnds  ----------//
			else
			{
				pSketchObjectFeature = new FSKETCHCreate2DArcCenterEnds(GetPart(), objectTag, this);
				cout << "FSKETCHcreate2DArcCenterEnds Constructed" << endl;
			}
			break;
		default : // curve_type unknown
			cout << "Unknown Sketch curve type : " << curve_type << endl;
			break;
	}

	if(pSketchObjectFeature) _sketObjList.push_back(pSketchObjectFeature);

	return pSketchObjectFeature;
}

void FSketch::GetUGInfo()
{
	Feature *  pFSketchObject;
	int 	objectsNum;	// sketch objects number
	tag_t *	objectTags;	// sketch objects tags list
	UF_CALL(UF_SKET_ask_geoms_of_sketch( GetSketTag(), &objectsNum, &objectTags));	// UF_free(objectTags)

	//DEBUG
	cout << "  " << "[[[ Constructing Sketch objects... ]]]" << endl;
	
	//-------  Loop to create sketch object features list in objectTag  --------//
	for (int k=0; k < objectsNum ; k++)
	{	
		tag_t objectTag = objectTags[k];

		// Create a sketch object feature class
		pFSketchObject = CreateSketObj(objectTag);

        if(!pFSketchObject)
			cerr << "  " << "****** Cannot support the sketch object! ******" << endl;
	}
	UF_free(objectTags);

	//DEBUG
	cout << "  " << "[[[ Translating Sketch objects... ]]]" << endl;

	//-------  Loop to translate sketch object features in list  --------//
	for ( size_t i=0 ; i < GetSketObjSize(); ++i )
	{
		GetSketObj((unsigned int)i)->GetUGInfo();
		//DEBUG
		cout << "  " << (unsigned int)i << " : " << GetSketObj((unsigned int)i)->GetName() << " translated" << endl;
	}

	//----------  Set Result_Object_Name  ----------//
	char buffer[20];
	_itoa(_nSketCnt ++ , buffer, 10 );
    SetName("sketch" + (string)buffer);
}

TransCAD::ISketchEditorPtr FSketch::GetSketchEditorPtr()
{
	return _spSketEditor;
}

void FSketch::ToTransCAD()
{
	static int k = 0;
	k++;
	Point3D origin = GetOrigin();
	Direct3D xdir = GetX();
	Direct3D ydir = GetY();
	
	//DEBUG
	Direct3D zdir = GetZ();
	cout << "    " << origin.X() << " " << origin.Y() << " " << origin.Z() << endl;
	cout << "    " << xdir.X() << " " << xdir.Y() << " " << xdir.Z() << endl;
	cout << "    " << ydir.X() << " " << ydir.Y() << " " << ydir.Z() << endl;
	cout << "    " << zdir.X() << " " << zdir.Y() << " " << zdir.Z() << endl;

    // Select Reference Plane for sketch
	//TransCAD::IReferencePtr spSelectedPlane;
	//if (k==4) spSelectedPlane = GetPart()->_spPart->SelectObjectByName("proExtrude0,sketch0,line2D2,0,0,0,ExtrudeFeature:0,0:0;0");

	TransCAD::IReferencePtr spSelectedPlane = GetPart()->_spPart->SelectPlaneByAxis(origin.X(), origin.Y(), origin.Z(), 
															xdir.X(), xdir.Y(), xdir.Z(), ydir.X(), ydir.Y(), ydir.Z());

	// Add new StdSketchFeature to TransCAD
	TransCAD::IStdSketchFeaturePtr spSketch = GetPart()->_spFeatures->AddNewSketchFeature(GetName().c_str(), spSelectedPlane);

	// Set Coordinate system of Sketch
	spSketch->SetCoordinateSystem(origin.X(), origin.Y(), origin.Z(), xdir.X(), xdir.Y(), xdir.Z(), ydir.X(), ydir.Y(), ydir.Z());

	// TransCAD Sketch Open
	_spSketEditor = spSketch->OpenEditorEx(VARIANT_FALSE);

		//---------- Sketch Objects : ToTransCAD() ----------//
		for ( size_t i=0 ; i < GetSketObjSize() ; ++i )
			GetSketObj((unsigned int)i)->ToTransCAD();
		
	// TransCAD Sketch Close
	_spSketEditor->Close();
}