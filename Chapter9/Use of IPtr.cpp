// To use IPtr
IPtr<IX, &IID_IX> spIX;
HRESULT hr = spIX.CreateInstance(CLSID_Component1,
                                 NULL,
                                 CLSCTX_INPROC_SERVER);

if (SUCCEEDED(hr)) {
    spIX->Fx();
}

// Assignment
void Fuzzy(IX* pIX1, IX* pIX2)
{
    IPtr<IX, IID_IX> spIX;
    spIX = pIX1;
    spIX->Fx();

    spIX = pIX2;
    spIX->Fx();
}

typdef IPtr<IX, IID_IX> SPIX;
SPIX g_spIX;
void Wuzzy(SPIX spIX)
{
    g_spIX = spIX;
}

// IUnknown interface assignment
T* operator=(IUnknown* pIUnknown);

void WasABear(IY* pIY)
{
    IPtr<IX, IID_IX> spIX;
    spIX = pIY;
    if (spIX) {
        spIX->Fx();
    }
}

// Interface_cast
template <class I, const GUID* pGUID>
I* interface_cast(IUnknown* pIUnknown)
{
    I* pI = NULL;
    HRESULT hr = pIUnknown->QueryInterface(*pGUID,
                                           (void**)&pI);
    assert(SUCCEEDED(hr));
    return pI;                                        
}

// To use interface_cast
IY* pIY = interface_cast<IY, &IID_IY>(this);

// IUnknownPtr
IPtr<IUnknown & IID_IUnknown> spIUnknown;       // Error

IUnknownPtr spIUnknown;                         // Right

