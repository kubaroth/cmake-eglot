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

using json = nlohmann::json;

// Parsing from file
// std::ifstream f("example.json");
// json data = json::parse(f);

int main(){

    
json ex1 = json::parse(R"(
  {
    "pi": 3.141,
    "happy": true
  }
)");

std::cout << ex1.dump(4) <<'\n';

std::vector<std::string> v = {"foo", "bar", "baz"};
std::string s = absl::StrJoin(v, "-");
std::cout << "Abseil StrJoin: " << s <<'\n';
std::cout << "DONE" <<'\n';

}
