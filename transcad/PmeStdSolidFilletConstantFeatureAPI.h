#pragma once

#include ".\PmeMacro.h"
#include ".\PmeHandle.h"
#include ".\PmePropagationType.h"

class PME_API PmeStdSolidFilletConstantFeatureAPI
{
public:
	static void Create
	(
		PmeHPart hPart,
		const CString & name,
		PmeHReferences hFilletEdges,
		double radius,
		PmePropagationType propagation,    
		PmeHFeature & hFeature
	);

	static void GetFilletEdges(PmeHFeature hFeature, PmeHReferences & hFilletEdges);
	static void GetRadius(PmeHFeature hFeature, double & radius);
	static void GetPropagationType(PmeHFeature hFeature, PmePropagationType & propagation);
	static void GetStartPoint(PmeHFeature hFeature, SPAposition & position);
	static void GetEndPoint(PmeHFeature hFeature, SPAposition & position);
};