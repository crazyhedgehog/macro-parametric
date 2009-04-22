// StdSolidChamferFeatureAuto.cpp : CStdSolidChamferFeatureAuto의 구현입니다.

#include "stdafx.h"
#include "StdSolidChamferFeatureAuto.h"


// CStdSolidChamferFeatureAuto

STDMETHODIMP CStdSolidChamferFeatureAuto::get_ChamferType(ChamferType *pVal)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	PmeChamferType chamferType;
	PmeStdSolidChamferFeatureAPI::GetChamferType(m_hFeature, chamferType);

	*pVal = (ChamferType)chamferType;

	return S_OK;
}

STDMETHODIMP CStdSolidChamferFeatureAuto::get_SelectedEdge(IReference **ppVal)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	PmeHReference hSelectedEdge;
	PmeStdSolidChamferFeatureAPI::GetSelectedEdge(m_hFeature, hSelectedEdge);

	return CPartAuto::GetIReferenceFromHReference(hSelectedEdge, ppVal);
	//return S_OK;
}

STDMETHODIMP CStdSolidChamferFeatureAuto::get_SelectedFace(IReference **ppVal)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	PmeHReference hSelectedFace;
	PmeStdSolidChamferFeatureAPI::GetSelectedFace(m_hFeature, hSelectedFace);

	return CPartAuto::GetIReferenceFromHReference(hSelectedFace, ppVal);
	//return S_OK;
}

STDMETHODIMP CStdSolidChamferFeatureAuto::get_Length(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	double length;
	PmeStdSolidChamferFeatureAPI::GetLength(m_hFeature, length);

	*pVal = length;

	return S_OK;
}

STDMETHODIMP CStdSolidChamferFeatureAuto::get_Value(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	double value;
	PmeStdSolidChamferFeatureAPI::GetValue(m_hFeature, value);

	*pVal = value;

	return S_OK;
}

STDMETHODIMP CStdSolidChamferFeatureAuto::get_StartPosX(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	SPAposition pos;
	double coord;

	PmeStdSolidChamferFeatureAPI::GetStartPoint(m_hFeature, pos);

	coord = pos.x();

	*pVal = coord;

	return S_OK;
}

STDMETHODIMP CStdSolidChamferFeatureAuto::get_StartPosY(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	SPAposition pos;
	double coord;

	PmeStdSolidChamferFeatureAPI::GetStartPoint(m_hFeature, pos);

	coord = pos.y();

	*pVal = coord;

	return S_OK;
}

STDMETHODIMP CStdSolidChamferFeatureAuto::get_StartPosZ(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	SPAposition pos;
	double coord;

	PmeStdSolidChamferFeatureAPI::GetStartPoint(m_hFeature, pos);

	coord = pos.z();

	*pVal = coord;

	return S_OK;
}

STDMETHODIMP CStdSolidChamferFeatureAuto::get_EndPosX(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	SPAposition pos;
	double coord;

	PmeStdSolidChamferFeatureAPI::GetEndPoint(m_hFeature, pos);

	coord = pos.x();

	*pVal = coord;

	return S_OK;
}

STDMETHODIMP CStdSolidChamferFeatureAuto::get_EndPosY(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	SPAposition pos;
	double coord;

	PmeStdSolidChamferFeatureAPI::GetEndPoint(m_hFeature, pos);

	coord = pos.y();

	*pVal = coord;

	return S_OK;
}

STDMETHODIMP CStdSolidChamferFeatureAuto::get_EndPosZ(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	SPAposition pos;
	double coord;

	PmeStdSolidChamferFeatureAPI::GetEndPoint(m_hFeature, pos);

	coord = pos.z();

	*pVal = coord;

	return S_OK;
}