#pragma once

#include "Feature.h"

class Part;
class FSketch;

class FSKETCHCreate2DLine2Points :
	public Feature
{
public:

	FSKETCHCreate2DLine2Points(Part * part, tag_t fTag, FSketch * pFSketch);
	virtual ~FSKETCHCreate2DLine2Points(void);

	FSketch * GetFSketch() {return _pFSketch;}

	void GetStaPnt(Point3D & sP) {sP = _sP;}
	void SetStaPnt(const Point3D & sP) {_sP = sP;}
	void GetEndPnt(Point3D & eP) {eP = _eP;}
	void SetEndPnt(const Point3D & eP) {_eP = eP;}
	void GetPickPnt(Point3D & pickPnt) {pickPnt = (_sP + _eP) * 0.5;}
	
	virtual void GetUGInfo();
	virtual void ToTransCAD();
	
private:
	static int _nLineCnt;

	Point3D		_sP;
	Point3D		_eP;
	FSketch *	_pFSketch;
};
