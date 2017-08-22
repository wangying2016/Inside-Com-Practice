class CB : pulbic IY,
           pulbic INondelegatingUnknown
{
public:
    // Delegating IUnknown
    virtual HRESULT __stdcall
    QueryInterface(const IID& iid, void** ppv);
    {
        // Delegate QueryInterface.
        return m_pUnknownOuter->QueryInterface(iid, ppv);
    }

    virtual ULONG __stdcall AddRef()
    {
        // Delegate AddRef.
        return m_pUnknownOuter->AddRef();
    }

    virtual ULONG __stdcall Release()
    {
        // Delegate Release.
        return m_pUnknownOuter->Release();
    }

    // Nondelegating IUnknown
    virtual HRESULT __stdcall 
    NondelegatingQueryInterface(const IID&, void **);
    virtual ULONG __stdcall NondelegatingAddRef();
    virtual ULONG __stdcall NondelegatingRelease();

    // Interface IY.
    virtual void __stdcall Fy() { cout << "Fy" << endl; }

    // Constructor
    CB(IUnknown* m_pUnknownOuter);

    // Destructor
    ~CB();

private:
    long m_cRef;
    IUnknown* m_pUnknownOuter;
}           