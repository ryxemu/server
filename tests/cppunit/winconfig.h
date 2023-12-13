#ifndef TEST_CONFIG_H
#define TEST_CONFIG_H

// Capabilities
//
#define HAVE_GETTICKCOUNT

// Compiler specific stuff
//
#if _MSC_VER == 1200  // MS Visual C++ 6.0
#pragma warning(disable : 4786)
#endif

#if _MSC_VER > 1300  // MS Visual C++ .NET 2002 and above
#pragma warning(disable : 4267)
#endif

#endif  // #ifndef TEST_CONFIG_H
