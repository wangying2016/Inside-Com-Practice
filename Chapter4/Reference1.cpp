// Create a new component.
IUnknown* pIUnknown = CreateInstance();

// Get interface IX.
IX* pIX = NULL;
HRESULT hr = 
pIUnknown->QueryInterface(IID_IX, (void**)&pIX);

if (SUCCEEDED(hr)) {
    pIX->Fx();          // Use interface IX.
    pIX->Release();     // Done with IX.
}
pIUknown->Release();    // Done with IUnknown.

