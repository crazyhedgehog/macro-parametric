#include ".\UGPre.h"
#include ".\feature.h"

#include <iostream>

#include <uf_modl.h>

#include "part.h"

Feature::Feature(Part * part, tag_t fTag)
{
	_pPart = part;
	_fTag = fTag;
	_index = part->GetFeaturesSize();
	_fType = FEATURE;
}

Feature::~Feature(void)
{
}

void Feature::GetUGInfo()
{
}

void Feature::ToTransCAD()
{
}
