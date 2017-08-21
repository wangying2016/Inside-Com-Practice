HRESULT hr = CoCreateInstance(...);
if (FAILED(hr))
    return;
hr = pI->QueryIntance(...);
if (SUCCEEDED(hr)) {
    pIX->Fx();
    pIX->Release();
}
pI->Release();