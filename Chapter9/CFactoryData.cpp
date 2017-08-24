typedef HRESULT (*FPCREATEINSTANCE)(IUnknown*, CUnknown**);

class CFactoryData
{
public:
    // The class ID for the component
    const CLSID* m_pCLSID;

    // Pointer to the function that creates it
    PFCREATEINSTANCE CreateInstance;

    // Name of the component to register in the registry
    const char* m_RegistryName;

    // ProgID
    const char* m_szProgID;

    // Version-independent ProgID
    const char* m_szVerIndProgID;

    // Helper function for finding the class ID
    BOOL IsClassID(const CLSID& clsid) const
        { return (*m_pCLSID == clsid); }
};