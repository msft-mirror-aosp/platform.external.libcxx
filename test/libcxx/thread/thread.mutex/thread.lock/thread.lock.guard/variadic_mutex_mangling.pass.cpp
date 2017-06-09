//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// UNSUPPORTED: libcpp-has-no-threads

// TODO(EricWF) Investigate why typeid(...).name() returns a different string
// on GCC 4.9 but not newer GCCs.
// XFAIL: gcc-4.9
// XFAIL: windows

// THIS TESTS C++03 EXTENSIONS.

// <mutex>

// template <class ...Mutex> class lock_guard;

// Test that the the variadic lock guard implementation mangles the same in
// C++11 and C++03. This is important since the mangling of `lock_guard` depends
// on it being declared as a variadic template, even in C++03.

// MODULES_DEFINES: _LIBCPP_ABI_VARIADIC_LOCK_GUARD
#define _LIBCPP_ABI_VARIADIC_LOCK_GUARD
#include <mutex>
#include <string>
#include <typeinfo>
#include <cassert>
#include <sstream>

#define _STRINGIFY(x) #x
#define STRINGIFY(x) _STRINGIFY(x)

int main() {
    const std::string ns_name = STRINGIFY(_LIBCPP_NAMESPACE);
    std::ostringstream string_builder;
    string_builder << "NSt" << ns_name.size() << ns_name
                   << "10lock_guardIJNS_5mutexEEEE";
    const std::string expect = string_builder.str();
    assert(typeid(std::lock_guard<std::mutex>).name() == expect);
}
