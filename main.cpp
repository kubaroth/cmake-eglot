// NOTE: clangd does not recognize __build directory - we need to symlink or just use build
// cmake -B build -S .
// cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -S .
// cmake --build build --target foo
// ./build/foo
// ./build/
// lldb ./build/foo

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "nlohmann/json.hpp"
#include "absl/strings/str_join.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

#include "message.pb.h"  // protobuffer

int main(){

// SPDlog    
spdlog::info("Welcome to spdlog!");

std::vector<int> vv{1,2,3,4};
spdlog::info("vv: {0}", fmt::join(vv, ", "));

// JSON
using json = nlohmann::json;

// Parsing from file
// std::ifstream f("example.json");
// json data = json::parse(f);

json ex1 = json::parse(R"(
  {
    "pi": 3.141,
    "happy": true
  }
)");

std::cout << ex1.dump(4) <<'\n';

// Abseil
std::vector<std::string> v = {"foo", "bar", "baz"};
std::string s = absl::StrJoin(v, "-");
std::cout << "Abseil StrJoin: " << s <<'\n';

// Protobuffer
message::Message m;
m.add_id(12);
m.set_name("my name");
std::cout << "Hello Proto! " << m.DebugString() << std::endl;

std::cout << "DONE" <<'\n';

}
