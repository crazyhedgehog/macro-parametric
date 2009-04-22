#include ".\sketchitem.h"

#include <iostream>

#include "FSketch.h"

SKETCHItem::SKETCHItem(FSketch * pFSketch, TransCAD::IStdSketchGeometryPtr spItem)
{
	_pFSketch = pFSketch;					// Set FSketch Ptr
	_spItem = spItem;								// Set TransCAD SketchItem Ptr;
	_nIndex = pFSketch->GetSketchItemsSize();	// Set index
	_strName = spItem->Name;					// Set Item Name
	cout << "  " << "Geometry Item Name : " << _strName;	//DEBUG
}

SKETCHItem::~SKETCHItem(void)
{
}

void SKETCHItem::GetInfo()
{
}

void SKETCHItem::ToUG()
{
}


