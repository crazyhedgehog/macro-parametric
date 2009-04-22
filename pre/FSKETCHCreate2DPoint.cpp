#include ".\FSKETCHCreate2DPoint.h"

#include "Part.h"
#include "FSketch.h"

FSKETCHCreate2DPoint::FSKETCHCreate2DPoint(Part * part, tag_t fTag, FSketch * pFSketch)
	: Feature(part, fTag)
{
	_pFSketch = pFSketch;
}

FSKETCHCreate2DPoint::~FSKETCHCreate2DPoint(void)
{
}

void FSKETCHCreate2DPoint::SetPoint(const Point3D & point)
{
	_point = point;
}

void FSKETCHCreate2DPoint::GetPoint(Point3D & point)
{
	point = _point;
}

void FSKETCHCreate2DPoint::GetUGInfo()
{
	// not used yet
}

void FSKETCHCreate2DPoint::ToTransCAD()
{
	/*
	Document *pDoc = GetFSketch()->GetPart()->GetDocument();
	std::ofstream& os = GetFSketch()->GetPart()->GetOs();


	// Calculate Information on Point


	// Output XML result
	os << "<SKETCH_Create_2D_Point>" << endl;
	os << "<result_object_name>" << "point2D" << pDoc->point_cnt << "</result_object_name>" << endl;
	os << "<point>" << endl;
	os << "<coordinates>" << _point.p1 << "</coordinates>" << endl;
	os << "<coordinates>" << _point.p2 << "</coordinates>" << endl;
	os << "<coordinates>" << _point.p3 << "</coordinates>" << endl;
	os << "</point>" << endl;
	os << "</SKETCH_Create_2D_Point>" << endl << endl;

	//-------------------  Set Result_Object_Name  -------------------//
	char buffer[20];
	_itoa( pDoc->point_cnt , buffer, 10 );
	SetName("point2D" + (string)buffer);
	pDoc->point_cnt ++;
	*/
}