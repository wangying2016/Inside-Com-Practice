interface IAirplane : IUnknown
{
    void TakeOff();
    void Fly();
    void Land();
};

interface IFloatPlane : IAirplane
{
    void LandingSurface(UINT iSurfaceType);
    void Float();
    void Sink();
    void Rust();
    void DrainBankAccount();
};

void CMyFloatPlane::Fly()
{
    m_pIAirPlane->Fly();
}

void CMyFloatPlane::Land()
{
    if (m_iLandingSurface == WATER) {
        WaterLanding();
    } else {
        m_pIAirPlane->Land();
    }
}

