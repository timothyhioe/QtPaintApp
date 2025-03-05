#include "nonsolidobj.h"

NonSolidObj::NonSolidObj() {}

NonSolidObj::NonSolidObj(QPoint refPnt, QColor color): GraphObj(refPnt, color, false)
{
    this->filled = false;
}

