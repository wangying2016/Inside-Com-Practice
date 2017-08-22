class CA : public IX
{
public:
    // IUnknown
    virtual HRESULT __stdcall QueryInstance(const IID& iid, void** ppv);
    virtual ULONG   __stdcall AddRef();
    virtual ULONG   __stdcall Release();

    // Interface IX
    virtual void __stdcall Fx() { cout << "Fx" << endl; }

    // Constructor
    CA();

    // Destructor
    ~CA();

    // Initialization function called by the class factory
    // to create contained component.
    HRESULT Init();

private:
    // Reference Count
    long m_cRef;
    // Pointer to inner component's IUnknown
    IUnknown* m_pInnerUnknown;
}

HRESULT __stdcall CA::QueryInstance(const IID& iid, void** ppv)
{
    if (iid == IID_IUnknown) {
        *ppv = static_cast<IX*>(this);
    }
    else if (iid == IID_IX) {
        *ppv = static_cast<IX*>(this);
    }
    else if (iid == IID_IY) {
        return m_pInnerUnknown->QueryInstance(iid, ppv);
    }
    else {
        *ppv = NULL;
        return E_NOINTERFACE;
    }
    reinterpret_cast<IUnknown*>(*ppv)->AddRef();
    return S_OK;
}