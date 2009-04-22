#pragma once

#include "Feature.h"

class Part;

class FSOLIDOperatePatternRectangular :
	public Feature
{
public:
	FSOLIDOperatePatternRectangular(Part * part, tag_t fTag);
	virtual ~FSOLIDOperatePatternRectangular(void) {}

	/*
	string GetFilletObject() {return _strFillObj;}
	string GetFilletEdges() {return NULL;}
	double GetRadius() const {return _dR;}
	PropagationType GetPropType() {return _PropType;}
	void GetStaPnt(Point3D & sP) {sP=_sP;}
	void GetEndPnt(Point3D & eP) {eP=_eP;}
	void GetPickPnt(Point3D & pP) {pP=_pP;}
	*/

	virtual void GetUGInfo();
	virtual void ToTransCAD();

private:
	static int _patternCnt;		// Pattern Instance Count

protected:
	string			_strPatternObj;	// Object name to be patterned
	Direct3D		_dirCol;
	double			_dColSpace;
	int				_nCol;
	double			_dRowSpace;
	int				_nRow;
	Direct3D		_dirRow;
};

