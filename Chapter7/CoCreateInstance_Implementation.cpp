HRESULT CoCreateInstance(const CLSID& clsid,
                         IUnknown* pUnknownDuter,
                         DWORD dwClsContext,
                         const IID& iid,
                         void** ppv)
{
    // Set the out parameter to NULL.
    *ppv = NULL;

    // Create the class factory and
    // get an IClassFactory interface pointer.
    IClassFactory* pIFactory = NULL;
    HRESULT hr = CoGetClassObject(clsid,
                                  dwClsContext,
                                  NULL,
                                  IID_IClassFactory,
                                  (void**)&pIFactory);
    if (SUCCEEDED(hr)) {
        // Create the component.
        hr = pIFactory->CreateInstance(pUnknownOuter, iid, ppv);
        // Release the class factory.
        pIFactory->Relase();
    }

    return hr;
}