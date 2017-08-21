//
// Client1.cpp
// To compile: cl Client1.cpp Create.cpp GUIDs.cpp UUID.lib
//
#include <iostream>
#include <objbase.h>
#include "Iface.h"
#include "Create.h"
using namespace std;

void trace(const char* msg) { cout << "Client1:\t" << msg << endl; }

//
// Client1
//
int main()
{
	HRESULT hr;
	
	// Get the name of the component to use.
	char name[40];
	cout << "Enter the filename of a component to use [Cmpnt?.dll]";
	cin >> name;
	cout << endl;
	
	// Create component by calling the CreateInstance function in the DLL.
	trace("Get an IUnknown pointer.");
	IUnknown* pIUknown = CallCreateInstance(name);
	if (pIUknown == NULL) {
		trace("CallCreateInstance Failed.");
		return 1;
	}

	trace("Get interface IX.");
	IX* pIX = NULL;
	hr = pIUknown->QueryInterface(IID_IX, (void**)&pIX);

	if (SUCCEEDED(hr)) {
		trace("SUCCEEDED getting IX.");
		pIX->Fx();				// Use interface IX.
		pIX->Release();
	} else {
		trace("Could not get interface IX.");
	}
	trace("Release IUnknown interface.");
	pIUknown->Release();

	return 0;
}