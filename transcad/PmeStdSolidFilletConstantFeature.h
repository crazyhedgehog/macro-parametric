#pragma once
#include "pmestdsolidfeature.h"
#include ".\PmeReferences.h"
#include ".\PmePropagationType.h"

class PmeReference;

class PmeStdSolidFilletConstantFeature :
	public PmeStdSolidFeature
{
	PME_DECLARE_RUNTIME_TYPE(PmeStdSolidFilletConstantFeature)
public:
	PmeStdSolidFilletConstantFeature(PmePart * pPart);
	PmeStdSolidFilletConstantFeature(PmePart * pPart,
								PmeReferences * pFilletEdges,
								double radius,
                                PmePropagationType propagation);
	virtual ~PmeStdSolidFilletConstantFeature(void);

	PmeReferences * GetFilletEdges(void) const {return m_pFilletEdges;}
	double GetRadius(void) const {return m_radius;}
	PmePropagationType GetPropagation(void) const {return m_propagation;}

	SPAposition GetStartPoint(void) const {return m_EdgePoint[0];}
	SPAposition GetEndPoint(void) const {return m_EdgePoint[1];}


	void SetFilletEdges(PmeReferences * pFilletEdges) {m_pFilletEdges = pFilletEdges;}
	void SetRadius(double radius) {m_radius = radius;}
	void SetPropagation(PmePropagationType propagation) {m_propagation = propagation;}

	// PmeFeature
	virtual PmeFeatureType GetFeatureType(void) const { return PmeFeatureType_StdSolidFilletConstantFeature;}
	virtual void Update(void);	

protected:
	void AttachName(BODY *& pBody);

private:
	PmeReferences * m_pFilletEdges;
	double m_radius;
	PmePropagationType m_propagation;
	SPAposition m_EdgePoint[2];
};