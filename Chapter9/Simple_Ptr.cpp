class CFoo
{
public:
    virtual void Bar();
};

class CFooPointer
{
public:
    CFooPointer(CFoo* p) { m_p = p; }
    CFoo* operator->() { return m_p; }

private:
    CFoo* m_p;
};

void Funky(CFoo* pFoo)
{
    // Create and initialize the smart pointer.
    // It doesn't work, since operator = is not
    // been overloaded.
    CFooPointer spFoo(pFoo);

    // The following is the same as pFoo->Bar().
    spFoo->Bar();
}
