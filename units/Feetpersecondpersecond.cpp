#include "units/Feetpersecondpersecond.h"

namespace units
{

    Feetpersecondpersecond::Feetpersecondpersecond(
        const Meterspersecondpersecond &n)
    {
        *this = n.toFeetpersecondpersecond();
    }

    units::Meterspersecondpersecond
    Feetpersecondpersecond::toMeterspersecondpersecond() const
    {

        return Meterspersecondpersecond(m_value * 381.0 / 1250);
    }

} // namespace
