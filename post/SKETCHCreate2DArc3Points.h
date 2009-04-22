#pragma once

#include "Feature.h"

class Part;
class FeatureSketch;

//!	FeatureSKETCHcreate2DArc3Points class
/*!
	2D Arc class with 3 Points
*/

class FeatureSKETCHcreate2DArc3Points :
	public Feature
{
public:

	//! A constructor
	/*! \param part Part class pointer
		\param featureTag Object Tag tag_t
		\param featureSketch FeatureSketch class pointer
	*/
	FeatureSKETCHcreate2DArc3Points(Part * part, TransCAD::IFeaturePtr spFeature, FeatureSketch * featureSketch);
	
	virtual ~FeatureSKETCHcreate2DArc3Points(void);		//!< A destructor

	void SetCenterPoint(const CartesianPoint & centerPoint);	/*!< \param centerPoint center of Arc */
	void SetRadius(const double radius);	/*!< \param radius circle radius */
	void SetStartAngle(const double start_angle);	/*!< \param start_angle start angle of Arc */
	void SetEndAngle(const double end_angle);		/*!< \param end_angle end angle of Arc */
	void SetStartPoint(const CartesianPoint& startPoint);	/*!< \param startPoint start point of Arc*/
	void SetEndPoint(const CartesianPoint& endPoint);	/*!< \param endPoint end point of Arc */
	void SetPickingPoint();		//<! Set picking Point from Start and End Point
	
	FeatureSketch * GetFeatureSketch();			/*!< \return Sketch Feature class pointer */

	void GetCenterPoint(CartesianPoint & centerPoint);	//!< Get center of Arc */
	double GetRadius() const;		/*!< \return radius */
	double GetStartAngle() const;	/*!< \return start angle */
	double GetEndAngle() const;		/*!< \return end angle */
	void GetStartPoint(CartesianPoint & startPoint);	//!< Get Start point of Arc
	void GetEndPoint(CartesianPoint & endPoint);		//!< Get End point of Arc
	void GetPickingPoint(CartesianPoint & pickingPoint);//!< Get 

	virtual void GetInformation();	//!< Translate UG feature into needed infomation
	virtual void TransCAD2UG();		//!< Write feature infomation into TransCAD

private:
	static int _arc2D3PCount;	//!< Sketch 2D Arc 3Points count for result object name

	CartesianPoint _centerPoint;	//!< Center Point struct
    double _radius;					//!< Radius
	double _startAngle;				//!< Start Angle
	double _endAngle;				//!< End Angle
	CartesianPoint _startPoint;		//!< Start Point Struct
	CartesianPoint _endPoint;		//!< End Point Struct
	CartesianPoint _pickingPoint;	//!< Picking Point Struct

	FeatureSketch * _featureSketch;	//!< FeatureSketch class pointer

};
