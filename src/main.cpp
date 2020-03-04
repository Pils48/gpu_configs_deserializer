#include "../include/request_loader.h"

int main() {
    TestData request = loadTestDataFromJson("/home/nikita/CLionProjects/json_deserializer/resources/test_request.json");
    return 0;
}
