HRESULT __stdcall CoCreateInstacne(
    const CLSDID& clsid,
    IUnknown* pUnknownOuter,    // Outer Component
    DWORD dwClsContext,         // Server Context
    const IID& iid,
    void** ppv
);

HRESULT __stdcall CreateInstance(
    IUnknown* pUnknownOuter,
    const IID& iid,
    void** ppv
);