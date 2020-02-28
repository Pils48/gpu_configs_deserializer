#include <iostream>
#include "../include/request_loader.h"

using namespace std;

int main() {
    Request request = loadRequestFromJson("/home/nikita/CLionProjects/json_deserializer/resources/test_request.json");
    for (const auto &co : request.collision_objects)
    {
        cout << "ID: " << co.object_id << " filename: " << co.path_to_mesh << " is_ignored: " << co.is_ignored << endl;
    }
    for (const auto &scene : request.test_scenes)
    {
        cout << "Number of collision objects in scene: " << request.test_scenes.size() << endl;
        cout << "There are collision: " << scene.collision_result << endl;
        for (const auto &obj : scene.object_poses)
        {
            cout << obj.first << " " << endl;
        }
        cout << "The number: " << request.allowedCollisions.size();
    }
    return 0;
}
