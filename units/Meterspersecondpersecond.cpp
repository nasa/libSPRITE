#include "units/Meterspersecondpersecond.h"

namespace units
{

    Meterspersecondpersecond::Meterspersecondpersecond(
        const Feetpersecondpersecond &n)
    {
        *this = n.toMeterspersecondpersecond();
    }

    units::Feetpersecondpersecond
    Meterspersecondpersecond::toFeetpersecondpersecond() const
    {
        return Feetpersecondpersecond(m_value * 1250 / 381.0);
    }

} // namespace
