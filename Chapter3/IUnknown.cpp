// 
// IUnknown.cpp
// To compile use: cl IUnknown.cpp UUID.lib
//
#include <iostream>
#include <objbase.h>
#include <cstdlib>
using namespace std;

void trace(const char* msg) { cout << msg << endl; }

// Interfaces
interface IX : IUnknown
{
	virtual void __stdcall Fx() = 0;
};

interface IY : IUnknown
{
	virtual void __stdcall Fy() = 0;
};

interface IZ : IUnknown
{
	virtual void __stdcall Fz() = 0;
};

// Forward references for GUIDs
extern const IID IID_IX;
extern const IID IID_IY;
extern const IID IID_IZ;

// 
// Component
// 
class CA : public IX,
	       public IY
{
	// IUnknown implementation
	virtual HRESULT __stdcall QueryInterface(const IID& iid, void** ppv);
	virtual ULONG __stdcall AddRef() { return 0; }
	virtual ULONG __stdcall Release() { return 0; }

	// Interface IX implementation
	virtual void __stdcall Fx() { cout << "Fx" << endl; }

	// Interface IY implementation
	virtual void __stdcall Fy() { cout << "Fy" << endl; }
};

HRESULT __stdcall CA::QueryInterface(const IID& iid, void** ppv)
{
	if (iid == IID_IUnknown) {
		trace("QueryInterface: Return pointer to IUnknown.");
		*ppv = static_cast<IX*>(this);
	}
	else if (iid == IID_IX) {
		trace("QueryInterface: Return pointer to IX.");
		*ppv = static_cast<IX*>(this);
	}
	else if (iid == IID_IY) {
		trace("QueryInterface: Return pointer to IY.");
		*ppv = static_cast<IY*>(this);
	}
	else {
		trace("QueryInterface: Interface not supported.");
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef(); // See Chapter 4.
	return S_OK;
}

// 
// Creation function
//
IUnknown* CreateInstance()
{
	IUnknown* pI = static_cast<IX*>(new CA);
	pI->AddRef();
	return pI;
}

//
// IIDs
//
// <Guid("75A0A6A0-938C-4CD3-9863-3C7B0202184A")>
static const IID IID_IX = { 
	0x75A0A6A0, 0x938C, 0x4CD3,
	{0x98, 0x63, 0x3C, 0xB0, 0x20, 0x02, 0x18, 0x4A}};

// <Guid("2B4F218C-1E0A-408F-B232-2C8A572AB84B")>
static const IID IID_IY = {
	0x2B4F218C, 0x1E0A, 0x408F,
	{0xB2, 0x32, 0x2C, 0x8A, 0x57, 0x2A, 0xB8, 0x4B}};

// <Guid("3014B630-3682-4275-918E-DE1D177A509B")>
static const IID IID_IZ = {
	0x3014B630, 0x3682, 0x4275,
	{0x91, 0x8E, 0xDE, 0x1D, 0x17, 0x7A, 0x50, 0x9B}};

//
// Client
// 
int main()
{
	HRESULT hr;
	trace("Client: Get an IUnknown pointer.");
	IUnknown* pIUnknown = CreateInstance();

	trace("Client: Get interface IX.");

	IX* pIX = NULL;
	hr = pIUnknown->QueryInterface(IID_IX, (void**)&pIX);
	if (SUCCEEDED(hr)) {
		trace("Client: Succeeded getting IX.");
		pIX->Fx();		// Use interface IX.
	}

	trace("Client: Get interface IY.");

	IY* pIY = NULL;
	hr = pIUnknown->QueryInterface(IID_IY, (void**)&pIY);
	if (SUCCEEDED(hr)) {
		trace("Client: Succeeded getting IY.");
		pIY->Fy();		// Use interface IY.
	}

	trace("Client: Ask for an unsupported interface.");
	
	IZ* pIZ = NULL;
	hr = pIUnknown->QueryInterface(IID_IZ, (void**)&pIZ);
	if (SUCCEEDED(hr)) {
		trace("Client: Succeeded in getting interface IZ.");
		pIZ->Fz();
	} else {
		trace("Client: Could not get interface IZ.");
	}
	trace("Client: Get interface IY from interface IX.");

	IY* pIYfromIX = NULL;
	hr = pIX->QueryInterface(IID_IY, (void**)&pIYfromIX);
	if (SUCCEEDED(hr)) {
		trace("Client: Succeeded getting IY.");
		pIYfromIX->Fy();
	}

	trace("Client: Get interface IUnknown from IY.");

	IUnknown* pIUnknownfromIY = NULL;
	hr = pIY->QueryInterface(IID_IUnknown, (void**)&pIUnknownfromIY);
	if (SUCCEEDED(hr)) {
		cout << "Are the IUnknown pointers equal?";
		if (pIUnknownfromIY == pIUnknown) {
			cout << "Yes, pIUnknownfromIy == pIUnknown." << endl;
		} else {
			cout << "No, pIUnknownfromIy != pIUnknown." << endl;
		}
	}

	// Delete the component.
	delete pIUnknown;

	// Wait for close.
	system("pause");
	return 0;
}
