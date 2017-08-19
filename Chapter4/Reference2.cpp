IUnknown* pIUnknown = CreateInstance();
IX* pIX = NULL;
HRESULT hr =
pIUnknown->QueryInstance(IID_IX, (void**)&pIX);
pIUnknown->Release();
if (SUCCEEDED(hr)) {
    pIX->Fx();              // Use interface IX.
    IX* pIX2 = pIX;         // Make a copy of pIX.
    pIX2->AddRef();         // Increment the reference count.
    pIX2->Fx();             // Do something with pIX2.
    pIX2->Release();        // Done with IX2.
    pIX->Release();         // Done with IX.
}