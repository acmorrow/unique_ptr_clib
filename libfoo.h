#ifndef LIBFOO_H_INCLUDED
#define LIBFOO_H_INCLUDED

#pragma once

#include "libfoo_export.h"

#if defined(__cplusplus)
#define LIBFOO_NOEXCEPT noexcept
extern "C" {
#else
#define LIBFOO_NOEXCEPT
#endif

typedef struct foo_thing1 {
    int val;
} foo_thing1_t;

LIBFOO_API foo_thing1_t* foo_thing1_create() LIBFOO_NOEXCEPT;
LIBFOO_API void foo_thing1_destroy(foo_thing1_t* thing1) LIBFOO_NOEXCEPT;

typedef struct foo_thing2 {
    double val;
} foo_thing2_t;

LIBFOO_API foo_thing2_t* foo_thing2_create(double value1) LIBFOO_NOEXCEPT;
LIBFOO_API void foo_thing2_destroy(foo_thing2_t* thing2) LIBFOO_NOEXCEPT;

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // LIBFOO_H_INCLUDED
