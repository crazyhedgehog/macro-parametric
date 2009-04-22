#pragma once

#include "Feature.h"

class Part;
class FSketch;

class FSOLIDCreateCutExtrude :
	public Feature
{
public:
	FSOLIDCreateCutExtrude(Part * part, tag_t fTag);
	virtual ~FSOLIDCreateCutExtrude(void);
	
	FSketch * GetProSket() {return _pProFSket;}

	virtual void GetUGInfo();
	virtual void ToTransCAD();


private :
	static int _cutExtrudeCount;	//!< Solid Create Cut Extrude count

protected:
	//string _profileSketch;
	bool	_bFlip;
	EndType	_StaType;
	double	_dStart;
	EndType	_EndType;
	double	_dEnd;
	
	FSketch * _pProFSket;
};
