#include ".\UGPre.h"
#include <iostream>
#include <uf.h>
#include "Part.h"

using namespace std;

TransCAD::IApplicationPtr g_spApplication;	// TransCAD Application Pointer

int main ( int argc, char *argv[] ) 
{
	if ( argc!=2 ) {	// 荤侩过
		cout << "Usage: UGPre <filename>" << endl;
		return -1;
	}

	HRESULT hr = ::CoInitialize(NULL);	// COM Automation API Initialization
	if(FAILED(hr)) {
		cerr << "COM initialization failed." << endl;
		return -1;
	}

	int status = UF_initialize();			// UG API Initialization
	if (!status)
	{
		//------------------------ TransCAD 积己 ------------------------//
		hr = g_spApplication.CreateInstance(__uuidof(TransCAD::Application));
		if( !FAILED(hr) )
		{
			// Visualize a TransCAD
			g_spApplication->Visible = VARIANT_TRUE;

			// Part 努贰胶 积己
			string filename(argv[1]);
			Part * part = new Part ( filename );
			if (part)
			{
				if (part->IsUGFileOpen())
				{

					part->GetUGInfo();	// Get Info. from UG
					part->ToTransCAD();	// Get Info. into TransCAD

					cout <<  "Done!" << endl << endl;
					cout <<  "Press any key to close \"ToTransCAD\"... ";
					WaitGetEnter();
				}
				delete part;		// delete a Part class
			}

			g_spApplication.Release();	// TransCAD Release
		}

		UF_terminate ( );				// UG API Uninitialzation
	}

	
	::CoUninitialize();					// COM Automation API Uninitialization

	return status;
}