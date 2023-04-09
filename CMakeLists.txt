include(FetchContent)

### Abseil
FetchContent_Declare(abseil URL https://github.com/abseil/abseil-cpp/archive/refs/tags/20230125.2.tar.gz)
FetchContent_MakeAvailable(abseil)

### Json
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

add_executable(foo main.cpp)

target_include_directories(foo INTERFACE /data/data/com.termux/files/home/PRJ/nlohmann_json_test/__build/_deps/json-src/include/nlohmann)

target_link_libraries(foo PRIVATE
  nlohmann_json::nlohmann_json
  absl::strings
  )


### Google Test
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(
  hello_test
  hello_test.cpp
)
target_link_libraries(
  hello_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)