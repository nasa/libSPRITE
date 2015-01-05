#include "units/Feetpersecond.h"

namespace units
{

    Feetpersecond::Feetpersecond(const Kilometersperhour& n)
    {
        *this = n.toMeterspersecond().toFeetpersecond();
    }

    Feetpersecond::Feetpersecond(const Meterspersecond& n)
    {
        *this = n.toFeetpersecond();
    }

    Feetpersecond::Feetpersecond(const Milesperhour& n)
    {
        *this = n.toFeetpersecond();
    }

    units::Milesperhour  Feetpersecond::toMilesperhour() const
    {
        return Milesperhour(m_value * 45.0 / 66);
    }

    units::Meterspersecond  Feetpersecond::toMeterspersecond() const
    {
        return Meterspersecond(m_value * 381.0 / 1250);
    }


} // namespace
