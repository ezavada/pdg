#ifndef PDG_BINDING_GROUPS_H
#define PDG_BINDING_GROUPS_H

// Identify the interface supplying a reusable method group. Normal binding
// generation emits the methods unchanged; metadata extraction records their
// origin. Reusing a group does not itself declare native C++ inheritance.
#define METHODS_FROM(klass, base, ...) __VA_ARGS__

#endif
