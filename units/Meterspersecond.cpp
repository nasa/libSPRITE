#include "units/Feetpersecond.h"
#include "units/Milesperhour.h"
#include "units/Kilometersperhour.h"
#include "units/Meterspersecond.h"

namespace units
{

    Meterspersecond::Meterspersecond(const Kilometersperhour &n)
    {
        *this = n.toMeterspersecond();
    }

    Meterspersecond::Meterspersecond(const Feetpersecond &n)
    {
        *this = n.toMeterspersecond();
    }

    Meterspersecond::Meterspersecond(const Milesperhour &n)
    {
        *this = n.toFeetpersecond().toMeterspersecond();
    }

    units::Kilometersperhour Meterspersecond::toKilometersperhour() const
    {
        return Kilometersperhour(m_value * 3.6);
    }

    units::Feetpersecond Meterspersecond::toFeetpersecond() const
    {
        return Feetpersecond(m_value * 1250.0 / 381);
    }

} // namespace
