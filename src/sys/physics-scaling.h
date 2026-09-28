#ifndef PDG_PHYSICS_SCALING_H
#define PDG_PHYSICS_SCALING_H
#include <cmath>
namespace pdg {
// Positive finite inputs. Avoid intermediate overflow/underflow when the final
// scaled mass or inertia is representable (long double is also 64-bit on ARM).
inline double scaledPhysicalValue(double value, double numerator, double denominator) {
    int v, n, d;
    const double vm=std::frexp(value,&v), nm=std::frexp(numerator,&n), dm=std::frexp(denominator,&d);
    return std::ldexp(vm*nm/dm,v+n-d);
}
}
#endif
