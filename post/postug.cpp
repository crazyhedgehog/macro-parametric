#include ".\postug.h"

#include <iostream>
#include <uf.h>
#include "Part.h"
#include "Definition.h"

using namespace std;

TransCAD::IApplicationPtr g_spApplication;	// TransCAD Application Pointer

int main ( int argc, char *argv[] ) 
{
	
	
	// Usage
	if ( argc > 2 ) {
		cout << "Usage: postug [filename]" << endl;
		return -1;
	}

	HRESULT hr = ::CoInitialize(NULL);		// COM Automation API Initialization
	if(FAILED(hr)) {
		cerr << "COM initialization failed." << endl;
		return -1;
	}

	int status = UF_initialize ( );			// UG API Initialization

	if ( !status ) 	{
	
		// create TransCAD
		hr = g_spApplication.CreateInstance(__uuidof(TransCAD::Application));
		if(FAILED(hr)) return FALSE;
 
		// visualize TransCAD
		g_spApplication->Visible = VARIANT_TRUE;

		// Pause
		cout << endl <<  "Press enter to start \"PostUG\"";
		WaitGetEnter();

		// create a Part class
		Part * pPart;
		if (argc < 2)	pPart = new Part ();
		else	pPart = new Part (string(argv[1]));

		pPart->GetInfo();
		pPart->ToUG();

		 //Pause
		cout << endl <<  "Press enter to close \"ToUG\"... ";
		WaitGetEnter();
		
		// delete Part class
		delete pPart;	

		// Clear TransCAD
		g_spApplication.Release();
		
		status = UF_terminate ( );			// UG API Uninitialzation
	}
	::CoUninitialize();						// COM Automation API Uninitialization

	return status;
}
