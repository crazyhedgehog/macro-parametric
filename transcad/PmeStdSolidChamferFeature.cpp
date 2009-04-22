#include "StdAfx.h"
#include <algorithm>
#include ".\PmeStdSolidChamferFeature.h"
#include ".\PmeReference.h"
#include ".\PmeExceptionTest.h"
#include ".\PmeIlligalOperationException.h"
#include ".\attr_pme_facename.h"
#include ".\PmeQuery.h"
#include ".\PmePart.h"
#include ".\PmeExplicitModel.h"
#include ".\PmeSolid.h"
#include ".\PmeSelectionManager.h"

PME_IMPLEMENT_RUNTIME_TYPE(PmeStdSolidChamferFeature, PmeStdSolidFeature)

PmeStdSolidChamferFeature::PmeStdSolidChamferFeature(PmePart * pPart)
: PmeStdSolidFeature(pPart)
{
}

PmeStdSolidChamferFeature::PmeStdSolidChamferFeature(
	PmePart * pPart,
	PmeChamferType chamferType,
	PmeReference * pSelectedEdge,
	PmeReference * pSelectedFace,
	double length,
	double value) 
: PmeStdSolidFeature(pPart)
, m_chamferType(chamferType)
, m_pSelectedEdge(pSelectedEdge)
, m_pSelectedFace(pSelectedFace)
, m_length(length)
, m_value(value)
{

	ENTITY * pEdge = pPart->GetSelectionManager()->GetBrepFromReference(GetSelectedEdge());

	PmeThrowExceptionIf<PmeIlligalOperationException>(strcmp(pEdge->type_name(), "edge") != 0);

	EDGE* cEdge = (EDGE*)pEdge;

	m_EdgePoint[0] = cEdge->start_pos();
	m_EdgePoint[1] = cEdge->end_pos();
}

PmeStdSolidChamferFeature::~PmeStdSolidChamferFeature(void)
{
}

void PmeStdSolidChamferFeature::Update(void)
{
	PmeThrowExceptionIf<PmeIlligalOperationException>(GetChamferType() != PmeChamferType_Length);
	
	PmeThrowExceptionIf<PmeIlligalOperationException>(m_pSelectedEdge == 0);
	
	PmeThrowExceptionIf<PmeIlligalOperationException>(m_length != m_value);
	PmeThrowExceptionIf<PmeIlligalOperationException>(m_length <= 0);
	PmeThrowExceptionIf<PmeIlligalOperationException>(m_value <= 0);
	
	PmeThrowExceptionIf<PmeIlligalOperationException>(GetSelectedEdge()->GetReferenceType() != PmeReferenceType_Brep);

	PmePart * pPart = GetPart();
	ENTITY * pEdge = pPart->GetSelectionManager()->GetBrepFromReference(GetSelectedEdge());

	PmeThrowExceptionIf<PmeIlligalOperationException>(strcmp(pEdge->type_name(), "edge") != 0);

	ENTITY_LIST selectedEdges;
    selectedEdges.add(pEdge);

	double leftRange = m_length;
	
	API_BEGIN

		// api_set_int_option("annotations", TRUE);

		result = api_chamfer_edges(selectedEdges, leftRange);
		check_outcome(result);
	
		if(result.ok())
		{
			PmeSolid * pSolid = pPart->GetExplicitModel()->GetSolid();
			SetSolid(pSolid);
		}

		// api_clear_annotations();

	API_END		
}

void PmeStdSolidChamferFeature::AttachName(BODY *& pBody)
{
	/*
	ENTITY_LIST annotationListLateral;

	api_find_annotations(annotationListLateral, is_SWEEP_ANNO_EDGE_LAT);

	annotationListLateral.init();

	SWEEP_ANNO_EDGE_LAT * pAnnotationEdgeLat;

	CString sketchName = PmeSketchUtility::GetSketch(GetProfileSketch())->GetName();

	while((pAnnotationEdgeLat = (SWEEP_ANNO_EDGE_LAT *)annotationListLateral.next()) != NULL)
	{
        ENTITY_LIST annotationInputs;

		// pAnnotationEdgeLat->inputs(annotationInputs);

		EDGE * pEdge = pAnnotationEdgeLat->profile_edge();
		FACE * pFace = (FACE *)pAnnotationEdgeLat->lateral_face();
		
		CString edgeName = ((ATTRIB_GEN_STRING *)find_named_attrib(pEdge, sketchName))->value();
		CString faceName = GetName() + "," + sketchName +"," + edgeName +",0,0,0,Extrude_Feature:0,0:0;0";

		new ATTRIB_FACENAME(pFace, faceName);
	}

	ENTITY_LIST annotationListEnd;
	api_find_annotations(annotationListEnd, is_SWEEP_ANNO_END_CAPS);

	MrDirection sketchNormal = PmeSketchUtility::GetCoordinateSystem(GetProfileSketch()).ZDirection();
	MrPosition sketchOrigin = PmeSketchUtility::GetCoordinateSystem(GetProfileSketch()).Location();

	SWEEP_ANNO_END_CAPS	* pAnnotationEndCaps;
	
	annotationListEnd.init();

	while((pAnnotationEndCaps = (SWEEP_ANNO_END_CAPS *)annotationListEnd.next()) != NULL)
	{
		ENTITY_LIST annotationInputs;

		//pAnnotationEdgeLat->inputs(annotationInputs);		

		FACE * pStartFace = pAnnotationEndCaps->start_face();
		FACE * pEndFace = pAnnotationEndCaps->end_face();

		MrDirection startNormal = PmeQueryFaceNormal(pStartFace, sketchOrigin);
		MrDirection endNormal = PmeQueryFaceNormal(pEndFace, sketchOrigin);

		if(MrMath::IsEqual(startNormal, sketchNormal))
		{
			std::swap(pStartFace, pEndFace);
		}

		CString startFaceName = GetName() + ",0,-1,0,0,0,Extrude_Feature:0,0:0;0";
		CString endFaceName = GetName() + ",0,-2,0,0,0,Extrude_Feature:0,0:0;0";

		new ATTRIB_FACENAME(pStartFace, startFaceName);
		new ATTRIB_FACENAME(pEndFace, endFaceName);        
	}
	*/
}