struct INondelegatingUnknown
{
    virtual HRESULT __stdcall 
    NondelegatingQueryInterface(const IID&, void **) = 0;
    virtual ULONG __stdcall NondelegatingAddRef() = 0;
    virtual ULONG __stdcall NondelegatingRelease() = 0;
};

HRESULT __stdcall
CB::NonDelegatingQueryInterface(const IID& iid,
                                void** ppv)
{
    if (iid == IID_IUnknown) {
        *ppv = static_cast<INondelegatingUnknown*>(this);
    }
    else if (iid == IID_IY) {
        *ppv = static_cast<IY*>(this);
    }
    else {
        *ppv = NULL;
        return E_NOINTERFACE;
    }
    reinterpret_cast<IUnknown*>(*ppv)->AddRef();
    return S_OK;
}                                