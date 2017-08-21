HRESULT __stdcall CoGetClassObject(
    const CLSID& clsid,
    DWORD dwClsContext,
    COSERVERINFO* pServerInfo,      // Reserved for DCOM
    const IID& iid,
    void** ppv
);