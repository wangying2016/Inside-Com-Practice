interface IClassFactory : IUnknown
{
    HRESULT __stdcall
    CreateInstance(IUnknown* pUnknownOuter,
                   const IID& iid,
                   void** ppv);
    HRESULT __stdcall LockServer(BOOL bLock);
};