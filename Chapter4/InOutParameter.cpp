void ExchangeForCachedPtr(int i, IX** ppIX)
{
    (*ppIX)->Fx();          // Do something with in-parameter.
    (*ppIX)->Release();     // Release in parameter.

    *ppIX = g_Cache[i];     // Get cached pointer.
    (*ppIX)->AddRef();      // AddRef pointer.
    (*ppIX)->Fx();          // Do something with out-parameter.
}
