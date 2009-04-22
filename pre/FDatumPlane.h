#pragma once
#include "feature.h"

//!	 FDatumPlane class
/*!
	ABSOLUTE_DATUM_PLANE & ABSOLUTE_DATUM_AXIS features
*/

class FDatumPlane : public Feature
{

public:

	FDatumPlane(Part * part, tag_t fTag);	//!< A constructor
	virtual ~FDatumPlane(void);					//!< A Destructor

	void SetOrigin(const Point3D & origin);	/*!< \param origin Origin Point3D */ 
	void SetNormal(const Direct3D & normal);	/*!< \param normal Normal vector Direct3D */
	void SetPlaneXYZ(const string planeXYZ);	/*!< \param planeXYZ planeXY, planeYZ, planeZX string */

    Point3D	GetOrigin();		/*!< \return Cartesian Point struct */
	Direct3D		GetNormal();		/*!< \return Direct3D Vector struct */
	string			GetPlaneXYZ();		/*!< \return Plane name string */

	virtual void	GetUGInfo();	//!< Translate UG feature into needed infomation
	virtual	void	ToTransCAD();		//!< Write feature infomation into TransCAD


protected:

	Point3D	_origin;		//!< origin Point3D struct
	Direct3D		_normal;		//!< normal vector Direct3D vector struct
	string			_planeXYZ;		//!< plane name string
	
};
