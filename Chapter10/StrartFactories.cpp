BOOL CFactory::StartFactories()
{
    CFactoryData* pStart = &g_FactoryDataArray[0];
    const CFactoryData* pEnd =
        g_FactoryDataArray[g_cFactoryDataEntries - 1];
    
    for (CFactoryData* pData = pStart; pData <= pEnd; pData++) {
        // Initialize the class factory pointer and cookie.
        pData->m_pIClassFactory = NULL;
        pData->m_dwRegister = NULL;

        // Create the class factory for this component.
        IClassFactory* pIFactory = new CFactory(pData);

        // Register the class factory.
        DWORD dwRegister.
        HRESULT hr = ::CoRegisterClassObject(
            *(pData->m_pCLSID),
            static_cast<IUnknown*>(pIFactory),
            CLSCTX_LOCAL_SERVER,
            REGCLS_MULTIPLEUSE,
            &dwRegister);
        if (FAILED(hr)) {
            pIFactory->Release();
            return FALSE;
        }

        // Set the data
        pData->m_pIClassFactory = pIFactory;
        pData->m_dwRegister = dwRegister;
    }
    return TRUE;
}