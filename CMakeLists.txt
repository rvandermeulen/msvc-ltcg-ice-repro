cmake_minimum_required(VERSION 3.24)
project(msvc_ltcg_ice CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT Embedded)
option(REPRO_LTO "Build with /GL and link with /LTCG" ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ${REPRO_LTO})

add_compile_options(/guard:cf /EHs-c- /GR-)
add_compile_definitions(_HAS_EXCEPTIONS=0)
add_link_options(/guard:cf /DEBUG /OPT:REF /OPT:ICF /OPT:LBR /INCREMENTAL:NO /CETCOMPAT)

set(ABSL_PROPAGATE_CXX_STD ON)
set(ABSL_ENABLE_INSTALL OFF)
set(BUILD_TESTING OFF)
include(FetchContent)
FetchContent_Declare(abseil
  URL https://github.com/abseil/abseil-cpp/archive/refs/tags/20250814.0.zip)
FetchContent_MakeAvailable(abseil)

add_library(repro SHARED repro.cc)
target_link_libraries(repro PRIVATE absl::time)
