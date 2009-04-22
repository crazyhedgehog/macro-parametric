#pragma once

#include "feature.h"

class Part;
class FSketch;


class FSOLIDCreateCutRevolve :
	public Feature
{
public:
	FSOLIDCreateCutRevolve(Part * part, tag_t fTag);
	virtual ~FSOLIDCreateCutRevolve(void);

	void SetProSket(FSketch * pProFSket) {_pProFSket = pProFSket;}
	FSketch * GetProSket() {return _pProFSket;}

	void SetStaAng(double sA) {_dStaAng = sA;}
	void SetEndAng(double eA) {_dEndAng = eA;}
	double GetStaAng() {return _dStaAng;}
	double GetEndAng() {return _dEndAng;}

	virtual void GetUGInfo ();
	virtual void ToTransCAD();

private :
	static int _nCutRevCnt;	//!< Solid Create Cut Revolve count

protected:
	FSketch * _pProFSket;
	int		_bFlip;
	EndType	_StaType;
	double	_dStaAng;
	EndType	_EndType;
	double	_dEndAng;
};
