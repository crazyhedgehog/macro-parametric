/////////////////////////////////////////////////////////
//
//	FSketch Class

#pragma once

#include <vector>

#include <uf_sket.h>

#include "UGPre.h"
#include "feature.h"

class Part;

class FSketch : public Feature
{

public:

	FSketch(Part * part, tag_t fTag);
	virtual ~FSketch(void);
	void Clear();

	Feature * GetSketObj(int index) const {return _sketObjList.at(index);}
	size_t	GetSketObjSize() const {return _sketObjList.size();}
	tag_t	GetSketTag() {return _sketTag;}
	
	void	GetSketInfo(double csys[12]) {for(int i=0; i<12 ; i++) csys[i] = _sketInfo[i];}
	Point3D	GetOrigin(void) {return Point3D(_sketInfo[9], _sketInfo[10], _sketInfo[11]);}
	Direct3D GetX(void){return Direct3D(_sketInfo[0], _sketInfo[1], _sketInfo[2]);}
	Direct3D GetY(void){return Direct3D( _sketInfo[3], _sketInfo[4], _sketInfo[5]);}
	Direct3D GetZ(void){return Direct3D(_sketInfo[6], _sketInfo[7], _sketInfo[8]);}

	Feature * GetCLine(void);
	void SetCLine(Feature* pFeature);

	TransCAD::ISketchEditorPtr GetSketchEditorPtr();

	virtual void GetUGInfo();
	virtual void ToTransCAD();

private:
	Feature * CreateSketObj(tag_t sketObjTag);

private:
	static int _nSketCnt;	// FSketch count

	std::vector<Feature*>	_sketObjList;
	tag_t _sketTag;
	double _sketInfo[12];	// sketch Info Array 0~2 : Xdir, 3~5 : Ydir, 6~8 : Zdir, 9~11 : Origin
	UF_SKET_info_t	_ugSketInfo;

	TransCAD::ISketchEditorPtr _spSketEditor;	// TransCAD SketchEditorPtr
};
