#pragma once

#include "Feature.h"

class Part;
class FSketch;


class FSOLIDCreateProtrusionRevolve :
	public Feature
{
public:

	void SetProSket(FSketch * pProFSket) {_pProFSket = pProFSket;}
	FSketch * GetProSket() {return _pProFSket;}

	void SetStaAng(double sA) {_dStaAng = sA;}
	void SetEndAng(double eA) {_dEndAng = eA;}
	double GetStaAng() {return _dStaAng;}
	double GetEndAng() {return _dEndAng;}

	FSOLIDCreateProtrusionRevolve(Part * part, tag_t fTag);
	virtual ~FSOLIDCreateProtrusionRevolve(void);

	virtual void GetUGInfo ();
	virtual void ToTransCAD();

private :
	static int _nProRevCnt;	//!< Solid Create Protrusion Revolve count

protected:
	FSketch * _pProFSket;
	int		_bFlip;
	EndType	_StaType;
	double	_dStaAng;
	EndType	_EndType;
	double	_dEndAng;
};
