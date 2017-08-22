HRESULT __stdcall
CA::Init()
{
    IUnknown* pUnknownOuter = this;
    HRESULT hr = CoCreateInstance(CLSID_Component2,
                                  pUnknownOuter,
                                  CLSCTX_INPROC_SERVER,
                                  IID_IUnknown,
                                  (void**)&m_pUnknownInnter);
    if (FAILED(hr)) {
        return E_FAIL;
    }       
    
    // QI increments the reference count ont the outer component.
    // Get the IY interface from the inner component.
    hr = m_pUnknownInner->QueryInterface(IID_IY, (void**)&m_pIY);

    if (FAILED(hr)) {
        // Inner component dose not support interface IY.
        m_pUnknownInner->Release();
        return E_FAIL;
    }

    // We need to release the reference count added
    // to the outer component in the above call.
    pUnknownOuter->Release();
    
    return S_OK;                 
}