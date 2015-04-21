#include "units/Kilometersperhour.h"

namespace units
{

    Kilometersperhour::Kilometersperhour(const Meterspersecond &n)
    {
        *this = n.toKilometersperhour();
    }

    Kilometersperhour::Kilometersperhour(const Feetpersecond &n)
    {
        *this = n.toMeterspersecond().toKilometersperhour();
    }

    Kilometersperhour::Kilometersperhour(const Milesperhour &n)
    {
        *this = n.toFeetpersecond().toMeterspersecond().toKilometersperhour();
    }

    units::Meterspersecond Kilometersperhour::toMeterspersecond() const
    {
        return Meterspersecond(m_value / 3.6);
    }

} // namespace
