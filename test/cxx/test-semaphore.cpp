#include "pdg/sys/semaphore.h"

#include <chrono>
#include <cstdlib>
#include <future>
#include <iostream>
#include <type_traits>

using namespace std::chrono_literals;

namespace {
void expect(bool condition, const char* message) {
    if (!condition) {
        std::cerr << message << '\n';
        std::exit(1);
    }
}

static_assert(!std::is_copy_constructible_v<pdg::Semaphore>);

void wakeupEvent() {
    pdg::Semaphore event;
    expect(!event.awaitSignal(0), "a new event has no pending signal");
    expect(!event.awaitSignal(-1), "an expired wait does not block");
    expect(!event.awaitSignal(5), "an unsignaled timed wait expires");
    for (int i = 0; i < 1000; ++i) event.signal();
    expect(event.awaitSignal(0), "a signal before a wait is remembered");
    expect(!event.awaitSignal(0), "repeated signals coalesce into one wakeup");
    event.signal();
    expect(event.awaitSignal(-1), "a pending signal takes precedence over an expired timeout");

    std::promise<void> ready;
    auto blocked = std::async(std::launch::async, [&] {
        ready.set_value();
        event.awaitSignal();
    });
    ready.get_future().wait();
    expect(blocked.wait_for(20ms) == std::future_status::timeout,
           "an untimed wait blocks until signaled");
    event.signal();
    expect(blocked.wait_for(1s) == std::future_status::ready, "signal releases a blocked waiter");
    blocked.get();
    expect(!event.awaitSignal(0), "a blocked waiter consumes its signal");

    // Either waiter may win, but a single signal must not release both.
    auto first = std::async(std::launch::async, [&] { return event.awaitSignal(1000); });
    auto second = std::async(std::launch::async, [&] { return event.awaitSignal(1000); });
    event.signal();
    bool firstSignaled = first.get(), secondSignaled = second.get();
    expect(firstSignaled != secondSignaled, "only one waiter consumes each signal");

    // Exercise repeated producer/consumer handoffs and visibility of payload data.
    pdg::Semaphore acknowledged;
    int payload = 0;
    auto consumer = std::async(std::launch::async, [&] {
        for (int i = 1; i <= 1000; ++i) {
            if (!event.awaitSignal(1000) || payload != i) return false;
            acknowledged.signal();
        }
        return true;
    });
    for (int i = 1; i <= 1000; ++i) {
        payload = i;
        event.signal();
        expect(acknowledged.awaitSignal(1000), "producer/consumer handoff must not lose a wakeup");
    }
    expect(consumer.get(), "wakeup publishes the producer's writes to the consumer");
}
} // namespace

int main() {
    wakeupEvent();
    std::cout << "Semaphore contracts passed\n";
}
