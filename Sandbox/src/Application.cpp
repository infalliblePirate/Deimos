#include "iostream"

namespace Deimos {
    __declspec(dllimport) void print();
}

int main() {
    Deimos::print();
}
