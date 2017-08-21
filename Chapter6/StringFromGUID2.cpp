wchar_t szCLSID[39];
int r = ::StringFromCLSID(CLSID_Component1, szCLSID, 39);

#ifnef _UNICODE
    // Convert from widechar to non-wide...
    char szCLSID_single[39];
    wcstombs(szCLSID_single, szCLSID, 39);
#end if

wchar_t* string;
// Get String from CLSID
::StringFromCLSID(CLSID_Component1, &string);
// Use String
.
.
.
// Free String
::CoTaskMemFree(string);

interface IX : IUnknown
{
    virtual void __stdcall Fx() = 0;
}

DECLARE_INTERFACE(IX, IUnknown)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_REFIID, PPVOID) PURE;
    STDMETHOD(ULONG, AddRef)(THIS) PURE;
    STDMETHOD(ULONG, Relase)(THIS) PURE;

    // IX
    STDMETHOD(void, Fx)(THIS) PURE;
}