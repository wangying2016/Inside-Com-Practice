//
// Cmpnt1.cpp - Component1
//
//
#include <iostream>
#include "Iface.h"
#include "Registry.h"

using namespace std;

void trace(const char* msg) { cout << "Component 1:\t" << msg << endl; }

///////////////////////////////////////////////////////
//
// Global variables
//
// Static variables
static HMODULE g_hModule = NULL;            // DLL module handle
static long g_cComponents = 0;              // Count of active components
static long g_cServerLocks = 0;             // Count of locks

// Friendly name of component
const char g_szFriendlyName[] 
    = "Inside COM, Chapter 8 Example 2, Component 1";

// Version-independent ProgID
const char g_szVerIndProgID[] = "InsideCOM.Chap08.Ex2.Cmpnt1";

// ProgID
const char g_szProgID[] = "InsideCOM.Chap08.Ex2.Cmpnt1.1";

///////////////////////////////////////////////////////
//
// Component A
// 
class CA : public IX
          // public IY
{
public:
    // IUnknown
    virtual HRESULT __stdcall QueryInterface(const IID& iid, void** ppv);
    virtual ULONG   __stdcall AddRef();
    virtual ULONG   __stdcall Release();

    // Interface IX
    virtual void __stdcall Fx() { cout << "Fx" << endl; }

    /* Component aggregates instead of implementation interface IY.
    // Interface IY
    virtual void __stdcall Fy() { m_pIY->Fy(); }
    */

    // Constructor
    CA();

    // Destructor
    ~CA();

    // Initialization function called by the class factory
    // to create contained component
    HRESULT __stdcall Init();

private:
    // Reference count
    long m_cRef;

    // Pointer to the aggregated component's IY Interface
    // (We do not have to retain an IY pointer. However, we
    // can use it in QueryInterface.)
    IY* m_pIY;

    // Pointer to inner component's IUnknown
    IUnknown* m_pUnknownInner;
}          

//
// Constructor
//
CA::CA()
: m_cRef(1),
  m_pUnknownInner(NULL)
{
    InterlockedIncrement(&g_cComponents);
}  

//
// Destructor
//
CA::~CA()
{
    InterlockedDecrement(&g_cComponents);
    trace("Destroy self.");

    // Prevent recursive destruction on next AddRef/Release pair.
    m_cRef = 1;

    // Counter the pUnknownOuter->Release in the Init method.
    IUnknown* pUnknownOuter = this;
    pUnknownOuter->AddRef();

    // Properly release the pointer: there may be per-interface
    // reference counts.
    m_pIY->Release();

    // Release contained component
    if (m_pUnknownInnter != NULL) {
        m_pUnknownInnter->Release();
    }
}

// Initailize the component by creating the contained component.
HRESULT __stdcall CA::Init()
{
    // Get the pointer to the outer unknown.
    // Since this component is not aggregated. the outer unknown
    // is the same as the this pointer.
    IUnknown* pUnknownOuter = this;
    trace("Create inner component.");
    HRESULT hr = 
        ::CoCreateInstance(CLSID_Component2,
                           pUnknownOuter,   // Outer component's IUnknown
                           CLSCTX_INPROC_SERVER,
                           IID_IUnknown,    // IUnknown when aggregating
                           (void**)&m_pUnknownInner);
    if (FAILED(hr)) {
        trace("Could not create contained component.");
        return E_FAIL;
    }

    // This call will increment the reference count on the outer component.
    trace("Get the IY interface from the inner component.");
    hr = m_pUnknownInner->QueryInterface(IID_IY, (void**)&m_pIY);   
    if (FAILED(hr)) {
        trace("Inner component does not support interface IY.");
        m_pUnknownInner->Release();
        return E_FAIL;
    }

    // We need to release the reference count added to the
    // outer component in the above call. So call Release
    // on the pointer you passed to CoCreateInstance.
    pUnknownOuter->Release();
    return S_OK;
}

//
// IUnknown implementation
//
HRESULT __stdcall CA::QueryInterface(const IID& iid, void** ppv)
{
    if (iid == IID_IUnknown) {
        *ppv = static_cast<IUnknown*>(this);
    }
    else if (iid == IID_IX) {
        *ppv = static_cast<IX*>(this);
    }
    else if (iid == IID_IY){
        trace("Return inner component's IY interface.");
#if 1
        // You can query for the interface.
        return m_pUnknownInner->QueryInterface(iid, ppv);
#else 
        // Or you can return a cached pointer.
        *ppv = m_pIY;
        // Fall through so it will get AddRef'ed
#endif
    }
    else {
        *ppv = NULL;
        return E_NOINTERFACE;
    }
    reinterpret_cast<IUnknown*>(*ppv)->AddRef();
    return S_OK;
}

ULONG __stdcall CA::AddRef()
{
    retrun InterlockedIncrement(&m_cRef);
}

ULONG __stdcall CA::Release()
{
    if (InterlockedDecrement(&m_cRef) == 0) {
        delete this;
        return 0;
    }
    return m_cRef;
}

///////////////////////////////////////////////////////
// 
// Class Factory
//
class CFactory : public IClassFactory
{
public:
    // IUnknown
    virtual HRESULT __stdcall QueryInterface(cosnt IID& iid, void** ppv);
    virtual ULONG   __stdcall AddRef();
    virtual ULONG   __stdcall Release();

    // Interface IClassFactory
    virtual HRESULT __stdcall CreateInstance(IUnknown* pUnknownOuter,
                                             const IID& iid,
                                             void** ppv);
    virtual HRESULT __stdcall LockServer(BOOL bLock);

    // Constructor
    CFactory() : m_cRef(1) {}

    // Destructor
    ~CFactory() {}
                  
private:
    long m_cRef;
}

// 
// Class factory IUnknown implemenation
//
HRESULT __stdcall CFactory::QueryInstance(REFIID iid, void** ppv)
{
    IUnknown* pI;
    if ((iid == IID_IUnknown) || (iid == IID_IClassFactory)) {
        pI = static_cast<IClassFactory*>(this);
    }
    else {
        *ppv = NULL;
        return E_NOINTERFACE;
    }
    pI->AddRef();
    *ppv = pI;
    return S_OK;
}

ULONG CFactory::AddRef()
{
    return InterlockedIncrement(&m_cRef);
}

ULONG CFactory::Release()
{
    if (InterlockedDecrement(&m_cRef)) {
        delete this;
        return 0;
    }
    return m_cRef;
}

// 
// IClassFactory implementation
//
HRESULT __stdcall CFactory::CreateInstance(IUnknown* pUnknownOuter,
                                           const IID& iid,
                                           void** ppv)
{
    HRESULT hr = E_FAIL;
    // Cannot aggregate
    if (pUnknownOuter != NULL) {
        return CLASS_E_NOAGGREGATION;
    }

    // Create component.
    CA* pA = new CA;
    if (pA == NULL) {
        return E_OUTOFMEMORY;
    }

    // Initialize the component.
    hr = pA->Init();
    if (FAILED(hr)) {
        // Initialization failed. Delete component.
        pA->Release();
        return hr;
    }

    // Get the requested interface.
    hr = pA->QuerInterface(iid, ppv);
    pA->Release();
    return hr;
}

// LockServer
HRESULT __stdcall CFactory::LockServer(BOOL bLock)
{
    if (bLock) {
        InterlockedIncrement(&g_cServerLocks);
    }
    else {
        InterlockedDecrement(&g_cServerLocks);
    }
    return S_OK;
}

///////////////////////////////////////////////////////
// 
// Exported functions
//
STDAPI DllCanUnloadNow()
{
    if (g_cComponents == 0) && (g_cServerLocks == 0)) {
        return S_OK;
    }
    else {
        return S_FALSE;
    }
}

// 
// Get class factory.
//
STDAPI DllGetClassObject(const CLSID& clsid,
                         const IID& iid,
                         void** ppv)
{
    // Can we create this component?
    if (clsid != CLSID_Component1) {
        return CLASS_E_CLASSNOTAVAILABLE;
    }

    // Create class factory.
    CFactory* pFactory = new CFactory;  // No AddRef in constructor
    if (pFactory == NULL) {
        return E_OUTOFMEMORY;
    }

    // Get requested interface.
    HRESULT hr = pFactory->QueryInterface(iid, ppv);
    pFactory->Release();

    return hr;
}                         

// 
// Server registration
//
STDAPI DllRegisterServer()
{
    return RegisterServer(g_hModule,
                          CLSID_Component1,
                          g_szFriendlyName,
                          g_szVerIndProgID,
                          g_szProgID);
}

STDAPI DllUnregisterServer()
{
    return UnregisterServer(CLSID_Component1,
                            g_szVerIndProgID,
                            g_szProgID);
}

///////////////////////////////////////////////////////
// 
// DLL module information
//
BOOL APIENTRY DllMain(HANDLE hModule,
                      DWORD dwReason,
                      void* lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH) {
        g_hModule = hModule;
    }
    return TRUE;
}                      