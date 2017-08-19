// First interface
class IX 
{
    virtual void Fx1() = 0;
    virtual void Fx2() = 0;
};

// Second interface
class IY 
{
    virtual void Fy1() = 0;
    virtual void Fy2() = 0;
};


// Component
class CA : public IX,
           public IY 
{
public:
    // Implementation of abstract base class IX
    virtual void Fx1() { cout << "Fx1" << endl; }
    virtual void Fx2() { cout << "Fx2" << endl; }

    // Implementation of abstract base class IY
    virtual void Fy1() { cout << "Fy1" << endl; }
    virtual void Fy2() { cout << "Fy2" << endl; }
};

