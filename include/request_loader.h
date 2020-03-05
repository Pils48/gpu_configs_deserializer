//
// Created by nikita on 27.02.2020.
//

#include <iostream>
#include <unordered_map>
#include "../json/single_include/nlohmann/json.hpp"

#ifndef JSON_DESERIALIZER_REQUEST_LOADER_H
#define JSON_DESERIALIZER_REQUEST_LOADER_H

using namespace std;

using json = nlohmann::basic_json<>;

using AllowedCollisions = vector<array<string , 2>>;
using AllowedObjects = vector<string>;
using FreezedObjects = vector<string>;
using TestResults = vector<bool>;

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
    string object_id;
    string path_to_mesh;
};

struct SceneObjectInstance
{
    string object_id;
    Pose pose;
};

struct Scene
{
    vector<SceneObjectInstance> object_poses;
};

struct TestData
{
    TestResults results;
    AllowedObjects allowed_objects;
    FreezedObjects freezed_objects;
    AllowedCollisions allowed_collisions;
    vector<CollisionObject> collision_objects;
    vector<Scene> test_scenes;
};

void from_json(const json &j, Quaternion &quaternion);

void from_json(const json &j, Point &point);

void from_json(const json &j, SceneObjectInstance &scene_object);

void from_json(const json &j, Scene &scene);

void from_json(const json &j, CollisionObject &collision_object);

TestData loadTestDataFromJson(const string &conf_path);

#endif //JSON_DESERIALIZER_REQUEST_LOADER_H
