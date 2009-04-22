#include ".\FDatumPlane.h"

#include <iostream>
#include <uf_modl.h>

#include "Part.h"

using namespace std;

FDatumPlane::FDatumPlane(Part * pPart, Point3D& origin, Direct3D& normal) :
	Feature(pPart, NULL)
{
	_origin = origin;
	_normal = normal;
}

FDatumPlane::FDatumPlane(Part * pPart, TransCAD::IFeaturePtr spFeature) :
	Feature(pPart, spFeature)
{
}


FDatumPlane::~FDatumPlane(void)
{
}

void FDatumPlane::GetInfo()
{
	string featureName = GetFeatureName();

	if (featureName==string("XYPlane"))	{
		_origin = Point3D(0,0,0);
		_normal = Direct3D(0,0,1);
	}
	else if (featureName==string("YZPlane")) {
		_origin = Point3D(0,0,0);
		_normal = Direct3D(1,0,0);
	}
	else if (featureName==string("ZXPlane")) {
		_origin = Point3D(0,0,0);
		_normal = Direct3D(0,1,0);
	}
}

void FDatumPlane::ToUG()
{
	//tag_t oTag;	// UG object tag_t
	UF_CALL(UF_MODL_create_fixed_dplane((double*)&_origin,(double*)&_normal,&_ugTag));
	//UF_CALL(UF_MODL_ask_object_feat(oTag,&_ugTag));		// set _ugTag
	cout << "  FixedDatumPlane " << GetFeatureName() << endl;	
}
