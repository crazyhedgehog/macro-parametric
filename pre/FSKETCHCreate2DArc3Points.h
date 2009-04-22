#pragma once

#include "Feature.h"

class Part;
class FSketch;

class FSKETCHCreate2DArc3Points :
	public Feature
{
public:

	FSKETCHCreate2DArc3Points(Part * part, tag_t fTag, FSketch * pFSketch);
	
	virtual ~FSKETCHCreate2DArc3Points(void);

	void SetCntPnt(const Point3D & cP) {_cP=cP;}
	void SetRadius(const double r) {_dR = r;}
	void SetStaAng(const double sA) {_dStaAng = sA;}
	void SetEndAng(const double eA) {_dEndAng = eA;}
	void SetStaPnt(const Point3D& sP) {_sP=sP;}
	void SetEndPnt(const Point3D& eP) {_eP=eP;}
	void SetPickPnt();	// under Construction
	
	FSketch * GetFSketch() {return _pFSketch;}

	void GetCntPnt(Point3D & cP) {cP=_cP;}
	double GetRadius() const {return _dR;}
	double GetStaAng() const {return _dStaAng;}
	double GetEndAng() const {return _dEndAng;}
	void GetStaPnt(Point3D & sP) {sP=_sP;}
	void GetEndPnt(Point3D & eP) {eP=_eP;}
	void GetPickPnt(Point3D & pP) {pP=_pP;}

	virtual void GetUGInfo();
	virtual void ToTransCAD();

private:
	static int _2DArc3PntsCnt;

	Point3D _cP;
    double	_dR;
	double	_dStaAng;
	double	_dEndAng;
	Point3D _sP;
	Point3D _eP;
	Point3D _pP;

	FSketch * _pFSketch;
};
