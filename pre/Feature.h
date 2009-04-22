#pragma once
#include <string>
#include <uf.h>

#include "Definition.h"

using namespace std;

class Part;

class Feature
{
public:

	Feature(Part * part, tag_t fTag=0);
	virtual ~Feature(void);

	Part*	GetPart() {return _pPart;}
	tag_t	GetFTag() {return _fTag;}
	size_t	GetFIndex() {return _index;}
	string	GetName() {return _fName;}
	FType	GetFType() const {return _fType;}
		
	void	SetFType(FType fType) {_fType = fType; }
	void	SetName(string name) {_fName=name;}

	virtual void GetUGInfo();	// Get Features' Info. from UG
	virtual void ToTransCAD();		// Put Features' Info. Into TransCAD

protected:
	Part*		_pPart;
	tag_t		_fTag;		// UG Feature Tag
	size_t		_index;				// Index in feature list vector
	string		_fName;		// result object name string
	FType		_fType;
};
