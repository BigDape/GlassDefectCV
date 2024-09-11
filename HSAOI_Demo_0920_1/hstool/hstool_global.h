#ifndef HSTOOL_GLOBAL_H
#define HSTOOL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HSTOOL_LIBRARY)
#  define HSTOOL_EXPORT Q_DECL_EXPORT
#else
#  define HSTOOL_EXPORT Q_DECL_IMPORT
#endif

#endif // HSTOOL_GLOBAL_H
