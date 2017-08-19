interface IX : IUnknown { /*...*/ };
interface IY : IUnknown { /*...*/ };
class CA : public IX, public IY { /*...*/ };

HRESULT __stdcall CA::QueryInterface(const IID& iid, void** ppv)
{
    if (iid == IID_IUnknown) {
        // The client wants the IUnknown interface.
        *ppv = static_cast<IX*>(this);
    }
    else if (iid == IID_IX) {
        // The client wants the IX interface.
        *ppv = static_cast<IX*>(this);
    }
    else if (iid == IID_IY) {
        *ppv = static_cast<IY*>(this);
    }
    else {
        // We don't support the interface the client
        // wants. Be sure to set the resulting pointer
        // to NULL.
        *ppv = NULL;
        return E_NOINTERFACE;
    }
    static_cast<IUnknown*>(*ppv)->AddRef(); // See Chapter 4.
    return S_OK;
}

static_cast<IX*>(this) != static_cast<IY*>(this);
static_cast<void*>(this) != static_cast<IY*>(this);

class CA : public IX, public IY { ... }

void foo(IX* pIX);
void bar(IY* pIY);

int main()
{
    CA * pA = new CA;
    foo(pA);
    bar(pA);
    delete pA;
    return 0;
}