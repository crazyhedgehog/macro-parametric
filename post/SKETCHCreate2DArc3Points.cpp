#include ".\FeatureSKETCHcreate2DArc3Points.h"

#include <iostream>
#include <math.h>

#include "Part.h"
#include "FeatureSketch.h"

int FeatureSKETCHcreate2DArc3Points::_arc2D3PCount = 0;

FeatureSKETCHcreate2DArc3Points::FeatureSKETCHcreate2DArc3Points(Part * part, TransCAD::IFeaturePtr spFeature, FeatureSketch * featureSketch)
	: Feature (part, spFeature)
{
	_featureSketch = featureSketch;
}

FeatureSKETCHcreate2DArc3Points::~FeatureSKETCHcreate2DArc3Points(void)
{
}

void FeatureSKETCHcreate2DArc3Points::SetCenterPoint(const CartesianPoint & centerPoint)
{
	_centerPoint = centerPoint;}

void FeatureSKETCHcreate2DArc3Points::SetRadius(const double radius)
{
	_radius = radius;
}

void FeatureSKETCHcreate2DArc3Points::SetStartAngle(const double start_angle)
{
	_startAngle  = start_angle;
}

void FeatureSKETCHcreate2DArc3Points::SetEndAngle(const double end_angle)
{
	_endAngle  = end_angle;
}

void FeatureSKETCHcreate2DArc3Points::SetStartPoint(const CartesianPoint& startPoint)
{
	_startPoint = startPoint;
}

void FeatureSKETCHcreate2DArc3Points::SetEndPoint(const CartesianPoint& endPoint)
{
	_endPoint = endPoint;
}

void FeatureSKETCHcreate2DArc3Points::SetPickingPoint()
{

}

FeatureSketch * FeatureSKETCHcreate2DArc3Points::GetFeatureSketch()
{
	return _featureSketch;
}


void FeatureSKETCHcreate2DArc3Points::GetCenterPoint(CartesianPoint& centerPoint)
{
	centerPoint = _centerPoint;
}

double FeatureSKETCHcreate2DArc3Points::GetRadius() const
{
	return _radius;
}

double FeatureSKETCHcreate2DArc3Points::GetStartAngle() const
{
	return _startAngle;
}

double FeatureSKETCHcreate2DArc3Points::GetEndAngle() const
{
	return _endAngle;
}

void FeatureSKETCHcreate2DArc3Points::GetStartPoint(CartesianPoint & startPoint)
{
	startPoint = _startPoint;
}

void FeatureSKETCHcreate2DArc3Points::GetEndPoint(CartesianPoint & endPoint)
{
	endPoint = _endPoint;
}

void FeatureSKETCHcreate2DArc3Points::GetPickingPoint(CartesianPoint & pickingPoint)
{
	pickingPoint = _pickingPoint;
}


void FeatureSKETCHcreate2DArc3Points::GetInformation()
{
	// To get curve arc coordinate infomation from a object feature Tag
	UF_CURVE_arc_t arc_coords;
	UF_CALL(UF_CURVE_ask_arc_data( GetFeatureTag(), &arc_coords ) );

	// To translate center point from world to local coord
	double sketchInfo[12];
	GetFeatureSketch()->GetSketchInfo(sketchInfo);
	Cir_Map(sketchInfo, arc_coords.arc_center);
	
	// set center point, radius, startAngle, endAngle
	SetCenterPoint(arc_coords.arc_center);
	SetRadius(arc_coords.radius);
	SetStartAngle(arc_coords.start_angle);		// Radian
	SetEndAngle(arc_coords.end_angle);			// Radian

	//-------- Set startPoint, endPoint, pickingPoint  -------------//
	double r = GetRadius();
	CartesianPoint sP, eP;
	sP[0] = _centerPoint.X() + r * cos(GetStartAngle());
	sP[1] = _centerPoint.Y() + r * sin(GetStartAngle());
	sP[2] = 0;
	eP[0] = _centerPoint.X() + r * cos(GetEndAngle());
	eP[1] = _centerPoint.Y() + r * sin(GetEndAngle());
	eP[2] = 0;
	SetStartPoint(sP);
	SetEndPoint(eP);
	SetPickingPoint();
	

	//cout << "center : (" << this->_centerPoint.p1 << "," << _centerPoint.p2 << "," << _centerPoint.p3 << ")" << endl;
	//cout << "start angle : " << GetStartAngle() << endl;
	//cout << "end angle : " << GetEndAngle() << endl;
	//cout << "radius" << radius << endl;

	//----------  Set Result_Object_Name  ----------//
	char buffer[20];
	_itoa( _arc2D3PCount ++, buffer, 10 );
	SetResultObjectName("arc2D3P" + (string)buffer);
}

void FeatureSKETCHcreate2DArc3Points::TransCAD2UG()
{
/*
	std::ofstream& os = GetFeatureSketch()->GetPart()->GetOs();

	os << "<SKETCH_Create_2D_Line_2Points>" << endl;
	os << "<result_object_name>" << this->GetResultObjectName() << "</result_object_name>" << endl;
	os << "<start_point>" << endl;
	os << "<coordinates>" << _startPoint.p1 << "</coordinates>" << endl;
	os << "<coordinates>" << _startPoint.p2 << "</coordinates>" << endl;
	os << "<coordinates>" << _startPoint.p3 << "</coordinates>" << endl;
	os << "</start_point>" << endl;
	os << "<end_point>" << endl;
	os << "<coordinates>" << _endPoint.p1 << "</coordinates>" << endl;
	os << "<coordinates>" << _endPoint.p2 << "</coordinates>" << endl;
	os << "<coordinates>" << _endPoint.p3 << "</coordinates>" << endl;
	os << "</end_point>" << endl;
	os << "</SKETCH_Create_2D_Line_2Points>" << endl << endl;
*/
}