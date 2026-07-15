#ifndef ATOMIC_POLYFILL_H_INCLUDED
#define ATOMIC_POLYFILL_H_INCLUDED

#include <atomic>

// Simple polyfill for atomic operations
// This provides basic atomic types and operations for older compilers

namespace atomic_polyfill {
    
    template<typename T>
    using atomic = std::atomic<T>;
    
    using atomic_bool = std::atomic<bool>;
    using atomic_int = std::atomic<int>;
    using atomic_uint = std::atomic<unsigned int>;
    using atomic_long = std::atomic<long>;
    using atomic_ulong = std::atomic<unsigned long>;
    using atomic_size_t = std::atomic<size_t>;
    using atomic_intptr_t = std::atomic<intptr_t>;
    using atomic_uintptr_t = std::atomic<uintptr_t>;
    
    // Memory order constants
    constexpr auto memory_order_relaxed = std::memory_order_relaxed;
    constexpr auto memory_order_consume = std::memory_order_consume;
    constexpr auto memory_order_acquire = std::memory_order_acquire;
    constexpr auto memory_order_release = std::memory_order_release;
    constexpr auto memory_order_acq_rel = std::memory_order_acq_rel;
    constexpr auto memory_order_seq_cst = std::memory_order_seq_cst;
    
} // namespace atomic_polyfill

// Make the namespace available globally
using namespace atomic_polyfill;

#endif // ATOMIC_POLYFILL_H_INCLUDED 