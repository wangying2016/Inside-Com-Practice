HRESULT __stdcall
CFactory::CreateInstance(IUnknown* pUnknowOuter,
                         const IID& iid,
                         void** ppv)
{
    // To aggregate, iid must be IID_IUnknown.
    if ((pUnknowOuter != NULL) && (iid != IID_IUnknown)) {
        return CLASS_E_NOAGGREGATION;
    }

    // Create Component.
    CB* pB = new CB(pUnknowOuter);
    if (pB == NULL) {
        return E_OUTOFMEMORY;
    }

    // Get  the requested interface.
    HRESULT hr = pB->NondelegatingQueryInterface(iid, ppv);
    pB->NondelegatingRelease();
    return hr;
}                         