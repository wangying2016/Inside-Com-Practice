CB::CB(IUnknown* pUnknowOuter)
: m_cRef(1)
{
    ::InterlockedIncrement(&g_cComponents);

    if (pUnknowOuter == NULL) {
        // Not beging aggregated: use nondelegating unknown.
        m_pUnknowOuter = reinterpret_cast<IUnknown*>
                         (static_cast<INondelegatingUnknown*>
                          (this));
    }
    else {
        // Being aggregated; use outer unknown.
        m_pUnknowOuter = pUnknowOuter;
    }
}
