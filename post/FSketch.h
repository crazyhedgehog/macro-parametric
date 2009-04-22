/////////////////////////////////////////////////////////
//
//	FSketch Class

#pragma once

#include <vector>

//#include <uf_sket.h>

#include "postug.h"
#include "feature.h"

class Part;
class SKETCHItem;
class SKETCHCreate2DCenterline;

class FSketch : public Feature
{

public:
	// A constructor
	FSketch(Part * pPart, TransCAD::IFeaturePtr spFeature);
	// A destructor
	virtual ~FSketch(void);

	void Clear();

	tag_t GetSketchTag() {return _ugTag;}

	Direct3D GetNormal() {return Direct3D(_CSYS)^Direct3D(_CSYS+3);}
	SKETCHItem * GetSketchItem(int index) const {return _sketchItemList.at(index);}
	size_t GetSketchItemsSize() const {return _sketchItemList.size();}
	SKETCHItem* GetCenterline();

	virtual void GetInfo();
	virtual void ToUG();
	
protected:
	SKETCHItem * CreateSketchItem(TransCAD::IStdSketchGeometryPtr spItem);	

public:
	TransCAD::IReferencePtr _spReference;
	TransCAD::IStdSketchGeometriesPtr _spGeometries;
	uf_list_p_t	_ugObjectsList;

private:
	std::vector<SKETCHItem*> _sketchItemList;
	double	_CSYS[9];	// 0~2 : Xdir, 3~5 : Ydir, 6~8 : Origin
	//SKETCHCreate2DCenterline* _pCenterline;

};
