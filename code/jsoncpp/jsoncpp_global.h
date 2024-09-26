#ifndef JSONCPP_GLOBAL_H
#define JSONCPP_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(JSONCPP_LIBRARY)
#  define JSONCPP_EXPORT Q_DECL_EXPORT
#else
#  define JSONCPP_EXPORT Q_DECL_IMPORT
#endif

#endif // JSONCPP_GLOBAL_H
