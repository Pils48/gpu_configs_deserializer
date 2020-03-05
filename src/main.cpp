#include "../include/request_loader.h"

int main() {
    TestData request = loadTestDataFromJson("/home/pils48/CLionProjects/gpu_configs_deserializer/resources/test_request.json");
    return 0;
}
