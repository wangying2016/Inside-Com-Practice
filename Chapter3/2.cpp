#include <objbase.h>

interface IX
{
    virtual void _stdcall Fx1() = 0;
    virtual void _stdcall Fx2() = 0;
};

interface IY
{
    virtual void _stdcall Fy1() = 0;
    virtual void _stdcall Fy2() = 0;
};

HRESULT __stdcall QueryInterface(const IID& id, void** ppv);

HRESULT __stdcall QueryInterface(const IID& id, void** ppv);

void foo(IUnknown* pI)
{
    // Define a pointer for the interface.
    IX* pIX = NULL;

    // Ask for interface IX.
    HRESULT hr = pI->QueryInterface(IID_IX, (void**)&pIX);

    // Check return value
    if (SUCCEEDED(hr)) 
    {
        // Use interface.
        pIX->Fx();
    }
}

