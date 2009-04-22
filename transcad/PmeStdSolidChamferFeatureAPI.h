#pragma once

#include ".\PmeMacro.h"
#include ".\PmeHandle.h"
#include ".\PmeChamferType.h"

class PME_API PmeStdSolidChamferFeatureAPI
{
public:
    static void Create
		(
			PmeHPart hPart,
			const CString & name,
			PmeChamferType chamferType,
			PmeHReference hSelectedEdge,
			PmeHReference hSelectedFace,
			double length,
			double value,
			PmeHFeature & hFeature
		);

	static void Create
		(
			PmeHPart hPart,
			const CString & name,
			PmeHReference hSelectedEdge,
			double length,
			PmeHFeature & hFeature
		);

	static void GetChamferType(PmeHFeature hFeature, PmeChamferType & chamferType);
	static void GetSelectedEdge(PmeHFeature hFeature, PmeHReference & hSelectedEdge);
	static void GetSelectedFace(PmeHFeature hFeature, PmeHReference & hSelectedFace);
	static void GetLength(PmeHFeature hFeature, double & length);
	static void GetValue(PmeHFeature hFeature, double & value);

	static void GetStartPoint(PmeHFeature hFeature, SPAposition & position);
	static void GetEndPoint(PmeHFeature hFeature, SPAposition & position);

};