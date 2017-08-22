/////////////////////////////////////////////////////////
//
// Component A
// 
class CA : public IX,
           public IY
{
public:
    // IUnknown
    virtual HRESULT __stdcall QueryInstance(const IID& iid, void** ppv);
    virtual ULONG   __stdcall AddRef();
    virtual ULONG   __stdcall Release();

    // Interface IX
    virtual void __stdcall Fx() { cout << "Fx" << endl; }

    // Interface IY
    virtual void __stdcall Fy() { m_pIY->Fy(); }

    // Constructor
    CA();

    // Destructor
    ~CA();

    // Initialization function on called by the class factory.
    // and used to create the contained component
    HRESULT Init();

private:
    // Reference count
    long m_cRef;

    // Pointer to the contained component's IY interface.
    IY* m_pIY;
}

// 
// Constructor
//
CA::CA() : m_cRef(1), 
           m_pIY(NULL)
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

    // Release contained component.
    if (m_pIY != NULL) {
        m_pIY->Release();
    }
}

// Initialize the component by creating the contained component.
HRESULT CA::Init()
{
    trace("Create Contained component.");
    HRESULT hr = ::CoCreateInstance(CLSID_Component2,
                                    NULL,
                                    CLSCTX_INPROC_SERVER,
                                    IID_IY,
                                    (void**)&m_pIY);
    if (FAILED(hr)) {
        trace("Could not create contained component.");
        return E_FAIL;
    }                 
    else {
        return S_OK;
    }                   
}

// CreateInstance Function Code in CONTAIN\CMPNT1
HRESULT __stdcall CFactory::CreateInstance(IUnknown* pUnknownOuter,
                                           const IID& iid,
                                           void** ppv)
{
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
    HRESULT hr = pA->Init();
    if (FAILED(hr)) {
        // Initialization failed. Delete component.
        pA->Release();
        return hr;
    }

    // Get the requested interface.
    hr = pA->QueryInstance(iid, ppv);
    pA->Release();
    return hr;
}                                           