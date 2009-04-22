// StdSolidFilletConstantFeatureAuto.cpp : CStdSolidFilletConstantFeatureAuto의 구현입니다.

#include "stdafx.h"
#include "StdSolidFilletConstantFeatureAuto.h"
#include ".\PartAuto.h"


// CStdSolidFilletConstantFeatureAuto

STDMETHODIMP CStdSolidFilletConstantFeatureAuto::get_FilletEdges(IReferences **ppVal)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	PmeHReferences hFilletEdges;
	PmeStdSolidFilletConstantFeatureAPI::GetFilletEdges(m_hFeature, hFilletEdges);

	return CPartAuto::GetIReferencesFromHReferences(hFilletEdges, ppVal);
	//return S_OK;
}

STDMETHODIMP CStdSolidFilletConstantFeatureAuto::get_Radius(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	double radius;
	PmeStdSolidFilletConstantFeatureAPI::GetRadius(m_hFeature, radius);

	*pVal = radius;

	return S_OK;
}

STDMETHODIMP CStdSolidFilletConstantFeatureAuto::get_Propagation(PropagationType *pVal)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	PmePropagationType propagation;
	PmeStdSolidFilletConstantFeatureAPI::GetPropagationType(m_hFeature, propagation);

	*pVal = (PropagationType)propagation;

	return S_OK;
}

STDMETHODIMP CStdSolidFilletConstantFeatureAuto::get_StartPosX(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	SPAposition pos;
	double coord;
	
	PmeStdSolidFilletConstantFeatureAPI::GetStartPoint(m_hFeature, pos);
	
	coord = pos.x();

	*pVal = coord;

	return S_OK;
}

STDMETHODIMP CStdSolidFilletConstantFeatureAuto::get_StartPosY(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	SPAposition pos;
	double coord;

	PmeStdSolidFilletConstantFeatureAPI::GetStartPoint(m_hFeature, pos);

	coord = pos.y();

	*pVal = coord;

	return S_OK;
}

STDMETHODIMP CStdSolidFilletConstantFeatureAuto::get_StartPosZ(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	SPAposition pos;
	double coord;

	PmeStdSolidFilletConstantFeatureAPI::GetStartPoint(m_hFeature, pos);

	coord = pos.z();

	*pVal = coord;

	return S_OK;
}

STDMETHODIMP CStdSolidFilletConstantFeatureAuto::get_EndPosX(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	SPAposition pos;
	double coord;

	PmeStdSolidFilletConstantFeatureAPI::GetEndPoint(m_hFeature, pos);

	coord = pos.x();

	*pVal = coord;

	return S_OK;
}

STDMETHODIMP CStdSolidFilletConstantFeatureAuto::get_EndPosY(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	SPAposition pos;
	double coord;

	PmeStdSolidFilletConstantFeatureAPI::GetEndPoint(m_hFeature, pos);

	coord = pos.y();

	*pVal = coord;

	return S_OK;
}

STDMETHODIMP CStdSolidFilletConstantFeatureAuto::get_EndPosZ(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	SPAposition pos;
	double coord;

	PmeStdSolidFilletConstantFeatureAPI::GetEndPoint(m_hFeature, pos);

	coord = pos.z();

	*pVal = coord;

	return S_OK;
}