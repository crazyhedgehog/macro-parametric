#include "StdAfx.h"
#include <algorithm>
#include ".\PmeStdSolidFilletConstantFeature.h"
#include ".\PmeReference.h"
#include ".\PmeExceptionTest.h"
#include ".\PmeIlligalOperationException.h"
#include ".\attr_pme_facename.h"
#include ".\PmeQuery.h"
#include ".\PmePart.h"
#include ".\PmeExplicitModel.h"
#include ".\PmeSolid.h"

PME_IMPLEMENT_RUNTIME_TYPE(PmeStdSolidFilletConstantFeature, PmeStdSolidFeature)

PmeStdSolidFilletConstantFeature::PmeStdSolidFilletConstantFeature(PmePart * pPart)
: PmeStdSolidFeature(pPart)
{
}

PmeStdSolidFilletConstantFeature::PmeStdSolidFilletConstantFeature(
	PmePart * pPart,
    PmeReferences * pFilletEdges,
	double radius,
    PmePropagationType propagation) 
: PmeStdSolidFeature(pPart)
, m_radius(radius)
, m_propagation(propagation)
{
	m_pFilletEdges = pFilletEdges->Clone();
	ENTITY_LIST filletEdges = m_pFilletEdges->CreateEntityList();

	EDGE* fedge = (EDGE*)filletEdges.first();
	
		m_EdgePoint[0] = fedge->start_pos();
	
		m_EdgePoint[1] = fedge->end_pos();
}

PmeStdSolidFilletConstantFeature::~PmeStdSolidFilletConstantFeature(void)
{
	if(m_pFilletEdges)
		delete m_pFilletEdges;
	m_pFilletEdges = 0;
}

void PmeStdSolidFilletConstantFeature::Update(void)
{
	ENTITY_LIST filletEdges = m_pFilletEdges->CreateEntityList();
	double radius = GetRadius();

	PmeThrowExceptionIf<PmeIlligalOperationException>(filletEdges.count() == 0);
	PmeThrowExceptionIf<PmeIlligalOperationException>(radius <= 0);	
	
	PmePart * pPart = GetPart();

	API_BEGIN

		// api_set_int_option("annotations", TRUE);

		result = api_blend_edges(filletEdges, radius);
		check_outcome(result);
	
		if(result.ok())
		{
			PmeSolid * pSolid = pPart->GetExplicitModel()->GetSolid();
			SetSolid(pSolid);
		}

		// api_clear_annotations();

	API_END		
}

void PmeStdSolidFilletConstantFeature::AttachName(BODY *& pBody)
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