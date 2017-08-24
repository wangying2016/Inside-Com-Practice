void CFactory::StopFactories()
{
    CFactoryData* pStart = &g_FactoryDataArray[0];
    const CFactoryData* pEnd = 
    &g_FactoryDataArray[g_cFactoryDataEntries - 1];

    for (CFactoryData* pData = pStart; pData <= pEnd; pData++) {
        // Get the magic cookie and stop the factory from running.
        DWORD dwRegister = pData->m_dwRegister;
        if (dwRegister != 0) {
            ::CoRevokeClassObject(dwRegister);
        }

        // Release the class factory
        IClassFactory* pIFactory = pData->m_pIClassFactory;
        if (pIFactory != NULL) {
            pIFactory->Release();
        }
    }
}