#pragma once

#include <string>

#include <uf.h>

#include "postug.h"

class FSketch;

using namespace std;

class SKETCHItem
{
public:
	SKETCHItem(FSketch * pFSketch, TransCAD::IStdSketchGeometryPtr spItem);
	~SKETCHItem(void);

	FSketch * GetFeatureSketch() {return _pFSketch;}
	size_t	GetGeometryItemIndex() {return _nIndex;}
	string	GetSketchItemName() {return _strName;}
	TransCAD::IStdSketchGeometryPtr GetTransCADGeometryItem() {return _spItem;}
	TransCAD::StdSketchGeometryType GetType() {return _spItem->Type;}

	virtual void GetInfo();
	virtual void ToUG();

public:
	tag_t _ugTag;

protected:
	FSketch *	_pFSketch;
	size_t		_nIndex;
	string		_strName;
	TransCAD::IStdSketchGeometryPtr _spItem;

	//SketchItemType	_SketchItemType;
};
