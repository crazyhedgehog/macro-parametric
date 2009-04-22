// StdSolidFilletConstantFeatureAuto.h : CStdSolidFilletConstantFeatureAuto의 선언입니다.

#pragma once
#include "resource.h"       // 주 기호입니다.

#include "TransCAD.h"
#include ".\DispatchImplEx.h"
#include ".\FeatureImpl.h"

typedef IDispatchImplEx<IStdSolidFilletConstantFeature, &IID_IStdSolidFilletConstantFeature, &LIBID_TransCAD, /*wMajor =*/ 1, /*wMinor =*/ 0> IStdSolidFilletConstantFeatureType;

// CStdSolidFilletConstantFeatureAuto

class ATL_NO_VTABLE CStdSolidFilletConstantFeatureAuto : 
	public CComObjectRootEx<CComSingleThreadModel>,
	// public CComCoClass<CStdSolidFilletConstantFeatureAuto, &CLSID_StdSolidFilletConstantFeature>,
	public IFeatureImpl<IStdSolidFilletConstantFeatureType>
{
public:
	CStdSolidFilletConstantFeatureAuto()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_STDSOLIDFILLETCONSTANTFEATURE)


BEGIN_COM_MAP(CStdSolidFilletConstantFeatureAuto)
	COM_INTERFACE_ENTRY(IStdSolidFilletConstantFeature)
	COM_INTERFACE_ENTRY(IFeature)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
		ReleaseDispatchImplEx();
	}

public:
	STDMETHOD(get_FilletEdges)(IReferences **ppVal);
	STDMETHOD(get_Radius)(double *pVal);
	STDMETHOD(get_Propagation)(PropagationType *pVal);
	STDMETHOD(get_StartPosX)(double *pVal);
	STDMETHOD(get_StartPosY)(double *pVal);
	STDMETHOD(get_StartPosZ)(double *pVal);
	STDMETHOD(get_EndPosX)(double *pVal);
	STDMETHOD(get_EndPosY)(double *pVal);
	STDMETHOD(get_EndPosZ)(double *pVal);

};

// OBJECT_ENTRY_AUTO(__uuidof(StdSolidFilletConstantFeature), CStdSolidFilletConstantFeatureAuto)
