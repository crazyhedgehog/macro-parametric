#pragma once

#include "Feature.h"

class Part;

class FeatureSOLIDOperateFilletingFilletConstant :
	public Feature
{
public:
	FeatureSOLIDOperateFilletingFilletConstant(Part * pPart, TransCAD::IFeaturePtr spFeature);
	virtual ~FeatureSOLIDOperateFilletingFilletConstant(void);
	
	//double GetRadius() const {return _radius;}
	//PropagationType GetPropagationType() {return _propagationType;}
	void GetStartPoint(Point3D & startPoint) {startPoint = _startPoint;}
	void GetEndPoint(Point3D & endPoint) {endPoint = _endPoint;}
	void GetPickingPoint(Point3D & pickPnt) {pickPnt = (_startPoint+_endPoint)*0.5;}

	virtual void GetInfo();
	virtual void ToUG();



public:
	double	_radius;					// Fillet Radius
	PropagationType	_propagationType;	// Propagation Type

	void ExtractBaseFeature(string Refename);

protected:
	Point3D _startPoint;			// Start Point
	Point3D _endPoint;			// End Point
	Point3D _pickingPoint;		// 3rd Point
	
	string _featurename;
	char _basefeaturename[100];
	
	double  _point1[ 3 ];
	double  _point2[ 3 ]; 
	
	uf_list_p_t _ugBlendEdgeList;
};

