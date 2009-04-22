#include ".\FDatumPlane.h"

#include <iostream>
#include <uf_modl.h>

#include "Part.h"


using namespace std;

FDatumPlane::FDatumPlane(Part * part, tag_t fTag) :
	Feature(part,fTag)
{
}

FDatumPlane::~FDatumPlane(void)
{
}

void FDatumPlane::SetOrigin(const Point3D & origin)
{
	_origin	= origin;
}

void FDatumPlane::SetNormal(const Direct3D & normal)
{
	_normal = normal;
}

void FDatumPlane::SetPlaneXYZ(const string planeXYZ)
{
	_planeXYZ = planeXYZ;
}

Point3D FDatumPlane::GetOrigin()
{
	return _origin;
}

Direct3D FDatumPlane::GetNormal()
{
	return _normal;
}

string  FDatumPlane::GetPlaneXYZ()
{
	return _planeXYZ;
}

void FDatumPlane::GetUGInfo()
{
	double origin[3];
	double normal[3];
	char * offset;
	char * angle;
	
	//----  Get the Origin(Picking Point) , Normal Vector of the Datum_Plane   ----//
	UF_MODL_ask_datum_plane_parms (GetFTag() , origin, normal, &offset, &angle );
	UF_free(offset);
	UF_free(angle);

	string planeXYZ;
	if (normal[0]) planeXYZ = "PlaneYZ";
	else if (normal[1]) planeXYZ = "PlaneZX";
	else if (normal[2]) planeXYZ = "PlaneXY";
	else 
	{
		cout << "error : The plane has no Normal Direct3D!" << endl;
		return;
	}

	// Set origin, normal vector, Plane
	SetOrigin(origin);
	SetNormal(normal);
	SetPlaneXYZ(planeXYZ);

	//DEBUG
	cout << "  " << planeXYZ << " origin" << origin[0] << origin[1] << origin[2] << " normal" << normal[0] << normal[1] << normal[2] << endl;
}


void FDatumPlane::ToTransCAD()
{
	/*
	ofstream& os = this->GetPart()->GetOs();

	os << "<SELECT_Reference_Plane>" << '\n';
	os << "<result_object_name>" << "reference" << pDoc->reference_cnt << "</result_object_name>" << '\n';
	os << "<plane>" << this->GetPlaneXYZ() << "</plane>" << '\n';
	os << "<picking_point>" << '\n';
	os << "<coordinates>" << this->GetOriginX() << "</coordinates>" << '\n';
	os << "<coordinates>" << this->GetOriginY() << "</coordinates>" << '\n';
	os << "<coordinates>" << this->GetOriginZ() << "</coordinates>" << '\n';
	os << "</picking_point>" << '\n';
	os << "</SELECT_Reference_Plane>" << '\n' << '\n';
	
	pDoc->reference_cnt ++;
	*/
}
