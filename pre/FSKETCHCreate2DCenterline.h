#pragma once

#include "Feature.h"

class Part;
class FSketch;

class FSKETCHCreate2DCenterline :
	public Feature
{
public:

	FSKETCHCreate2DCenterline(Part * part, tag_t fTag, FSketch * pFSketch);
	
	virtual ~FSKETCHCreate2DCenterline(void);

	void SetStaPnt(const Point3D & sP) {_sP = sP;}
	void SetEndPnt(const Point3D & eP) {_eP = eP;}

	FSketch * GetFSketch() {return _pFSketch;}
	void GetStaPnt(Point3D & sP) {sP = _sP;}
	void GetEndPnt(Point3D & eP) {eP = _eP;}
	void GetPickPnt(Point3D & pickP) {pickP = (_sP+_eP)*0.5;}

	virtual void GetUGInfo(double pos[3], double dir[3]);
	virtual void ToTransCAD();
	
private:
	static int _nCLineCnt;

	Point3D		_sP;
	Point3D		_eP;
	FSketch *	_pFSketch;
};
