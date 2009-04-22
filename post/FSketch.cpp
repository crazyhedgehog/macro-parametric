#include ".\FSketch.h"

#include <iostream>

#include <uf_sket.h>
#include <uf_modl.h>
#include <uf_csys.h>
#include <uf_mtx.h>

#include "Part.h"
#include "SKETCHItem.h"
#include "SKETCHCreate2DPoint.h"
#include "SKETCHCreate2DLine2Points.h"
#include "SKETCHCreate2DCircleCenterPoint.h"
#include "SKETCHCreate2DArcCenterEnds.h"
#include "SKETCHCreate2DCenterline.h"
//#include "SKETCHcreate2DArc3Points.h"

using namespace std;

FSketch::FSketch(Part * pPart, TransCAD::IFeaturePtr spFeature) :
	Feature(pPart,spFeature)
{
	// set the Coordinate System
	((TransCAD::IStdSketchFeaturePtr)(_spFeature))->GetCoordinateSystem(_CSYS+6, _CSYS+7, _CSYS+8, _CSYS+0, _CSYS+1, _CSYS+2, _CSYS+3, _CSYS+4, _CSYS+5);

	// set sketch plane reference
	_spReference = ((TransCAD::IStdSketchFeaturePtr)(_spFeature))->SketchPlane;

	// set sketch objects group, Geometries
	_spGeometries = ((TransCAD::IStdSketchFeaturePtr) _spFeature)->Geometries;

	// other init.
	_ugObjectsList = NULL;
	//_pCenterline = NULL;
}

FSketch::~FSketch(void)
{
	Clear();
	if (_ugObjectsList) UF_MODL_delete_list(&_ugObjectsList);
}

void FSketch::Clear()
{
	std::vector<SKETCHItem*>::iterator i = _sketchItemList.begin();
	while ( i != _sketchItemList.end() ) {
		delete *i;
		i++;
	}
	_sketchItemList.clear();
}

SKETCHItem * FSketch::CreateSketchItem(TransCAD::IStdSketchGeometryPtr spItem)
{
	SKETCHItem * pSketchItem = 0;
	
	cout << "  SketchGeometry Type : " << spItem->Type << endl;
	switch(spItem->Type)
	{
	case TransCAD::Line :
		pSketchItem = new SKETCHCreate2DLine2Points(this, spItem);
		cout <<  " -> " << "SKETCHCreate2DLIne2Points created" << endl;
		break;
	case TransCAD::Centerline :
		pSketchItem = new SKETCHCreate2DCenterline(this, spItem);
		cout <<  " -> " << "SKETCHCreate2DCenterline created" << endl;
		break;
	case TransCAD::Circle :
		pSketchItem = new SKETCHCreate2DCircleCenterPoint(this, spItem);
		cout << " -> " << "SKETCHCreate2DCircleCenterPoint created" << endl;
		break;
	case TransCAD::CircularArc :
		pSketchItem = new SKETCHCreate2DArcCenterEnds(this, spItem);
		cout << " -> " << "SKETCHCreate2DArcCenterEnds created" << endl;
		break;
	case TransCAD::ControlPoint :
		pSketchItem = new SKETCHCreate2DPoint(this, spItem);
		cout << " -> " << "SKETCHCreate2DPoint created" << endl;
		break;
	}
	if(pSketchItem) _sketchItemList.push_back(pSketchItem);
	return pSketchItem;
}

SKETCHItem* FSketch::GetCenterline()
{
	for (size_t i=0; i<GetSketchItemsSize();i++)
		if (GetSketchItem((int)i)->GetType() == TransCAD::Centerline)
			return GetSketchItem((int)i);
	return NULL;
}

void FSketch::GetInfo()
{
	string refName = _spReference->ReferenceeName;
	cout << "  Ref name:" << _spReference->Name <<  " Type= " << _spReference->Type << endl;
	cout << "  RefFullName: " << refName << endl;


	cout << "  " << "***** Constructing Sketch Items..." << _spGeometries->Count << " *****" << endl;	//DEBUG

	//-------  create sketch item list in Geometries --------//
	SKETCHItem *  pSketchItem;

	for(int i = 1; i <= _spGeometries->Count; ++ i)	{
		TransCAD::IStdSketchGeometryPtr spItem = _spGeometries->Item[i];
		string name = spItem->Name;

		pSketchItem = CreateSketchItem(spItem);
		if(!pSketchItem) cerr << "  " << "****** Cannot support the sketch object! ******" << endl;
	}

	cout << "  " << "***** Translating Sketch Items... *****" << endl;	//DEBUG

	//-------  translate SketchItems in list  --------//
	for ( size_t i=0 ; i < GetSketchItemsSize(); ++i )	{
		SKETCHItem * pItem = GetSketchItem((unsigned int)i);
		pItem->GetInfo();
		//DEBUG
		cout << "  " << (unsigned int)i << " : " << GetSketchItem((unsigned int)i)->GetSketchItemName() << " translated" << endl;

	}
}

void FSketch::ToUG()
{
	// UG Sketch Initialization
	char name[30];
	strcpy(name, GetFeatureName().c_str());
	UF_CALL(UF_SKET_initialize_sketch(name,&_ugTag));
	UF_CALL(UF_SKET_create_sketch(name,2,_CSYS,NULL,NULL,NULL,&_ugTag));
	cout << "  FSketch " << name << " : sketchTag- " << _ugTag << endl;
	
	// Create sketch objects list
	UF_CALL(UF_MODL_create_list(&_ugObjectsList));
	
	//-------  Loop to get sketch items information into UG sketch --------//
	for(int i = 0; (unsigned int)i < GetSketchItemsSize(); ++i)
		GetSketchItem(i)->ToUG();

	// Terminate current sketch
	UF_SKET_terminate_sketch ( );
}