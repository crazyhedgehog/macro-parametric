#pragma once

#include "Feature.h"

class Part;
class FSketch;

class FSOLIDCreateProtrusionExtrude :
	public Feature
{
public:

	FSOLIDCreateProtrusionExtrude(Part * part, tag_t fTag);
	virtual ~FSOLIDCreateProtrusionExtrude(void);

	FSketch * GetProSket() {return _pProFSket;}

	virtual void GetUGInfo();
	virtual void ToTransCAD();

private :
	static int _proExtCnt;	//!< Solid Create Protrusion Extrude count

protected:
	bool	_bFlip;
	EndType	_StaType;
	double	_dStart;
	EndType	_EndType;
	double	_dEnd;

	FSketch * _pProFSket;
};
