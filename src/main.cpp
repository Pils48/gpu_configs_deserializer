#include "../include/request_loader.h"

int main() {
    const auto j = readJson("resources/test_request.json");
    TestData data = j.get<TestData>();
    return 0;
}
