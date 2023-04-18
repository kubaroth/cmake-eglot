cmake_minimum_required(VERSION 3.25)

include(FetchContent)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

### Abseil - disable since protobuf v22.* fetches abseil internally
# FetchContent_Declare(abseil URL https://github.com/abseil/abseil-cpp/archive/refs/tags/20230125.2.tar.gz)
#FetchContent_MakeAvailable(abseil)

### Json
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

FetchContent_Declare(spdlog URL https://github.com/gabime/spdlog/archive/refs/tags/v1.11.0.tar.gz)
FetchContent_MakeAvailable(spdlog)

# Protobffer
set(FETCHCONTENT_UPDATES_DISCONNECTED ON CACHE BOOL "Do not update I run cmake")

# Since we are using FetchContent to download another CMake project,
# it is possible to configure CMake files at the root level
# Disable building protobuf tests.
set(protobuf_BUILD_TESTS OFF)

FetchContent_Declare(internal_protobuf
  GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
  GIT_TAG        v22.1
  FIND_PACKAGE_ARGS NAMES internal_protobuf
)
FetchContent_MakeAvailable(internal_protobuf)

set(PROTO_SRCS message.pb.cc)
set(PROTO_HDRS message.pb.h)
set(PROTOC ${protobuf_BINARY_DIR}/protoc)
set(PROTO_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_command(
    OUTPUT ${PROTO_SRCS} ${PROTO_HDRS}
    COMMAND ${PROTOC} --proto_path ${PROTO_DIR} message.proto --cpp_out ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${PROTOC} ${PROTO_DIR}/message.proto main.cpp
    )


add_executable(foo
  main.cpp
  ${PROTO_SRCS}
)
  
# Add build dirctory in order to find generated protobuf files
target_include_directories(foo PRIVATE ${CMAKE_CURRENT_BINARY_DIR})


target_link_libraries(foo PRIVATE
  nlohmann_json::nlohmann_json
  absl::strings
  spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>
  protobuf::libprotobuf
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
