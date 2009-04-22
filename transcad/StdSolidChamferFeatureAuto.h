// StdSolidChamferFeatureAuto.h : CStdSolidChamferFeatureAuto의 선언입니다.

#pragma once
#include "resource.h"       // 주 기호입니다.

#include "TransCAD.h"
#include ".\DispatchImplEx.h"
#include ".\FeatureImpl.h"

typedef IDispatchImplEx<IStdSolidChamferFeature, &IID_IStdSolidChamferFeature, &LIBID_TransCAD, /*wMajor =*/ 1, /*wMinor =*/ 0> IStdSolidChamferFeatureType;

// CStdSolidChamferFeatureAuto

class ATL_NO_VTABLE CStdSolidChamferFeatureAuto : 
	public CComObjectRootEx<CComSingleThreadModel>,
	// public CComCoClass<CStdSolidChamferFeatureAuto, &CLSID_StdSolidChamferFeature>,
	public IFeatureImpl<IStdSolidChamferFeatureType>
{
public:
	CStdSolidChamferFeatureAuto()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_STDSOLIDCHAMFERFEATURE)


BEGIN_COM_MAP(CStdSolidChamferFeatureAuto)
	COM_INTERFACE_ENTRY(IStdSolidChamferFeature)
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
	STDMETHOD(get_ChamferType)(ChamferType *pVal);
	STDMETHOD(get_SelectedEdge)(IReference **ppVal);
	STDMETHOD(get_SelectedFace)(IReference **ppVal);
	STDMETHOD(get_Length)(double *pVal);
	STDMETHOD(get_Value)(double *pVal);
	STDMETHOD(get_StartPosX)(double *pVal);
	STDMETHOD(get_StartPosY)(double *pVal);
	STDMETHOD(get_StartPosZ)(double *pVal);
	STDMETHOD(get_EndPosX)(double *pVal);
	STDMETHOD(get_EndPosY)(double *pVal);
	STDMETHOD(get_EndPosZ)(double *pVal);

};

// OBJECT_ENTRY_AUTO(__uuidof(StdSolidChamferFeature), CStdSolidChamferFeatureAuto)
