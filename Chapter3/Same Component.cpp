BOOL SameComponents(IX* pIX, IY* pIY)
{
    IUnknown* pI1 = NULL;
    IUnknown* pI2 = NULL;

    // Get IUnknown pointer from pIX.
    pIX->QueryInterface(IID_IUnknown, (void**)&pI1);

    // Get IUnknown pointer from pIY.
    pIY->QueryInterface(IID_IUnknown, (void**)*pI2);

    // Are the two IUnknown pointers equal?
    return pI1 == pi2;
}
