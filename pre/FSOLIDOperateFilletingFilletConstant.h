#pragma once

#include "Feature.h"

class Part;

class FSOLIDOperateFilletingFilletConstant :
	public Feature
{
public:
	FSOLIDOperateFilletingFilletConstant(Part * part, tag_t fTag);
	virtual ~FSOLIDOperateFilletingFilletConstant(void) {}

	string GetFilletObject() {return _strFillObj;}
	string GetFilletEdges() {return NULL;}
	double GetRadius() const {return _dR;}
	PropagationType GetPropType() {return _PropType;}
	void GetStaPnt(Point3D & sP) {sP=_sP;}
	void GetEndPnt(Point3D & eP) {eP=_eP;}
	void GetPickPnt(Point3D & pP) {pP=_pP;}

	virtual void GetUGInfo();
	virtual void ToTransCAD();

private:
	static int _fillCnt;		// Fillet Count

protected:
	string			_strFillObj;	// Fillet Object name
	//string*		_filletEdges;	// Fillet Edges string array
	double			_dR;			// Fillet Radius
	PropagationType	_PropType;		// Optional : Propagation Type


	Point3D _sP;
	Point3D _eP;
	Point3D _pP;	// picking point
};

