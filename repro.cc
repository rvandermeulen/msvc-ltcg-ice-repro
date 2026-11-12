#include "absl/time/clock.h"

extern "C" __declspec(dllexport) void ReproSleep(int ms) {
  absl::SleepFor(absl::Milliseconds(ms));
}
