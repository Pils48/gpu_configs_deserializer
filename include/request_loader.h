//
// Created by nikita on 27.02.2020.
//

#include <iostream>
#include <unordered_map>
#include "../json/single_include/nlohmann/json.hpp"

#ifndef JSON_DESERIALIZER_REQUEST_LOADER_H
#define JSON_DESERIALIZER_REQUEST_LOADER_H

using json = nlohmann::basic_json<>;

enum ObjectType
{
    FREEZED,
    ACTIVE
};

using AllowedCollisions = std::unordered_map<std::string, std::string>;

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

struct collision_object
{
    std::string object_id;
    std::string path_to_mesh;
    bool is_ignored;
    ObjectType type;
};

struct Scene
{
    std::unordered_map<std::string, Pose> object_poses;
    bool collision_result;
};

struct Request
{
    AllowedCollisions allowedCollisions;
    std::vector<collision_object> collision_objects;
    std::vector<Scene> test_scenes;
};

Request loadRequestFromJson(const std::string &conf_path);

#endif //JSON_DESERIALIZER_REQUEST_LOADER_H
