#include "units/Milesperhour.h"

namespace units
{

    Milesperhour::Milesperhour(const Kilometersperhour &n)
    {
        *this = n.toMeterspersecond().toFeetpersecond().toMilesperhour();
    }

    Milesperhour::Milesperhour(const Meterspersecond &n)
    {
        *this = n.toFeetpersecond().toMilesperhour();
    }

    Milesperhour::Milesperhour(const Feetpersecond &n)
    {
        *this = n.toMilesperhour();
    }

    units::Feetpersecond Milesperhour::toFeetpersecond() const
    {
        return Feetpersecond(m_value * 66.0 / 45);
    }

} // namespace
