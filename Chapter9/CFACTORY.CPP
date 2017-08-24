//
// GetClassObject
//  -Create a class factory based on a CLSID.
//
HRESULT CFactory::GetClassObject(const CLSID& clsid,
                                 const IID& iid,
                                 void** ppv)
{
    if ((iid != IID_IUnknown) && (iid != IID_IClassFactory)) {
        return E_NOINTERFACE;
    }

    // Traverse the array of data looking for this class ID.
    for (int i = 0; i < g_cFactoryDataEntries; i++) {
        const CFactoryData* pData = &g_FactoryDataArray[i];
        if (pData->IsClassID(clsid)) {
            // Found  the ClassID in the array of components we can 
            // create. So create a class factory for this component.
            // Pass the CFactoryData structure to the class factory
            // so that it knows what kind of componens to create.
            *ppv = (IUnknown*) new CFactory(pData);
            if (*ppv == NULL) {
                return E_OUTOFMEMORY;
            }
            return NOERROR;
        }
    }
    return CLASS_E_CLASSNOTAVAILABLE;
}                                 

//
// CreateInstance
//
HRESULT __stdcall CFactory::CreateInstance(IUknown* pUnknownOuter,
                                           const IID& iid,
                                           void** ppv)
{
    // Aggregate only if the requested IID is IID_IUnknown.
    if ((pUnknownOuter != NULL) && (iid != IID_IUnknown)) {
        return CLASS_E_NOAGGREGATION;
    }
    // Create the component.
    CUnknown* pNewComponent;
    HRESULT hr = m_pFactoryData->CreateInstance(pUnknownOuter,
                                                &pNewComponent);
    if (FAILED(hr)) {
        return hr;
    }             
    
    // Initialize the component.
    hr = pNewComponent->Init();
    if (FAILED(hr)) {
        // Initialization failed. Release the component.
        pNewComponent->NondelegatingRelease();
        return hr;
    }

    // Get the requested interface.
    hr = pNewComponent->NondelegatingQueryInterface(iid, ppv);

    // Release the reference held by the class factory.
    pNewComponent->NondelegatingRelease();
    return hr;
}                                           