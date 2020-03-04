//
// Created by nikita on 27.02.2020.
//

#include <iostream>
#include <unordered_map>
#include "../json/single_include/nlohmann/json.hpp"

#ifndef JSON_DESERIALIZER_REQUEST_LOADER_H
#define JSON_DESERIALIZER_REQUEST_LOADER_H

using json = nlohmann::basic_json<>;

using AllowedCollisions = std::vector<std::array<std::string , 2>>;
using AllowedObjects = std::vector<std::string>;
using FreezedObjects = std::vector<std::string>;
using TestResults = std::vector<bool>;

struct Point
{
    double x, y, z;
};

struct Quaternion
{
    double w, x, y, z;
};

struct Pose
{
    Point origin;
    Quaternion orientation;
};

struct CollisionObject
{
    std::string object_id;
    std::string path_to_mesh;
};

struct Scene
{
    std::unordered_map<std::string, Pose> object_poses;
};

struct TestData
{
    TestResults results;
    AllowedObjects allowed_objects;
    FreezedObjects freezed_objects;
    AllowedCollisions allowed_collisions;
    std::vector<CollisionObject> collision_objects;
    std::vector<Scene> test_scenes;
};

AllowedCollisions loadAllowedCollisions(const std::string &conf_path);

TestResults loadResults(const std::string &conf_path);

std::vector<Scene> loadScenes(const std::string &conf_path);

std::vector<CollisionObject> loadObjects(const std::string &conf_path);

FreezedObjects loadFreezedObjects(const std::string &conf_path);

AllowedObjects loadAllowedCollisionObjects(const std::string &conf_path);

AllowedCollisions loadAllowedCollisionPairs(const std::string &conf_path);

TestData loadTestDataFromJson(const std::string &conf_path);

#endif //JSON_DESERIALIZER_REQUEST_LOADER_H
