HRESULT __stdcall CoCreateInstance(
    const CLSID& clsid,
    IUnknown* pIUnknownOuter,       // outer Component
    DWORD dwClsContext,             // Server Context
    const IID& iid,     
    void** ppv
);

// Create Component.
IX* pIX = NULL;
HRESULT hr = ::CoCreateInstance(
    CLSID_Component1,
    NULL,
    CLSCTX_INPROC_SERVER,
    IID_IX,
    (void**)&pIX));

if (SUCCEEDED(hr)) {
    pIX->Fx();
    pIX->Release();
}