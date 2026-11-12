# MSVC 14.52 x86 LTCG internal compiler error in abseil's clock.cc

Building onnxruntime 1.30 for x86 with MSVC 14.52.37025 (Visual Studio 2026 18.12) fails while generating code at the final DLL link with `/LTCG`. The same build succeeds with MSVC 14.51.36231, and for x64 and ARM64 with 14.52.

```
...\_deps\abseil_cpp-src\absl\time\clock.cc(593) : fatal error C1001: Internal compiler error.
(compiler file 'F:\1\s\src\vctools\Compiler\Utc\src\p2\main.cpp', line 281)
...
Access violation
```

Line 593 is in abseil 20250814.0's `AbslInternalSleepFor`:

```cpp
absl::Duration to_sleep = std::min(duration, absl::MaxSleep());
```

This project builds a DLL that calls `absl::SleepFor`, using abseil 20250814.0 and the same compiler and linker flags.

## Steps

1. Install Visual Studio 2026 18.12 (or its Build Tools) with the "Desktop development with C++" workload.
2. Open "x64_x86 Cross Tools Command Prompt for VS 2026". `cl` should report version 19.52.
3. Build:

   ```
   cmake -G Ninja -S . -B build -DCMAKE_BUILD_TYPE=MinSizeRel
   cmake --build build
   ```

## Controls

- Without LTCG: configure with `-DREPRO_LTO=OFF` in a fresh build directory.
- With MSVC 14.51: run `vcvarsall.bat x64_x86 -vcvars_ver=14.51` and build in a fresh build directory.
