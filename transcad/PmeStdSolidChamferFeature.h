#pragma once
#include "pmestdsolidfeature.h"
#include ".\PmeReferences.h"
#include ".\PmeChamferType.h"

class PmeReference;

class PmeStdSolidChamferFeature :
	public PmeStdSolidFeature
{
	PME_DECLARE_RUNTIME_TYPE(PmeStdSolidChamferFeature)
public:
	PmeStdSolidChamferFeature(PmePart * pPart);
	PmeStdSolidChamferFeature(PmePart * pPart,
								PmeChamferType chamferType,
								PmeReference * pSelectedEdge,
								PmeReference * pSelectedFace,
								double length,
								double value
                                );
	virtual ~PmeStdSolidChamferFeature(void);

	PmeChamferType GetChamferType(void) const {return m_chamferType;}
	PmeReference * GetSelectedEdge(void) const {return m_pSelectedEdge;}
	PmeReference * GetSelectedFace(void) const {return m_pSelectedFace;}
	double GetLenght(void) const {return m_length;}
	double GetValue(void) const {return m_value;}

	SPAposition GetStartPoint(void) const {return m_EdgePoint[0];}
	SPAposition GetEndPoint(void) const {return m_EdgePoint[1];}

	void SetChamferType(PmeChamferType chamferType) {m_chamferType = chamferType;}
	void SetSelectedEdge(PmeReference * pSelectedEdge) {m_pSelectedEdge = pSelectedEdge;}
	void SetSelectedFace(PmeReference * pSelectedFace) {m_pSelectedFace = pSelectedFace;}
	void SetLength(double length) {m_length = length;}
	void SetValue(double value) {m_value = value;}	

	// PmeFeature
	virtual PmeFeatureType GetFeatureType(void) const { return PmeFeatureType_StdSolidChamferFeature;}
	virtual void Update(void);	

protected:
	void AttachName(BODY *& pBody);

private:
	PmeChamferType m_chamferType;
	PmeReference * m_pSelectedEdge;
	PmeReference * m_pSelectedFace;
	double m_length;
	double m_value;	
	SPAposition m_EdgePoint[2];
};