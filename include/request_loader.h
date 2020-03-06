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
using CollidingPairs = vector<array<string, 2>>;

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

struct TestResult
{
    bool collision;
    CollidingPairs colliding_objects;
};

struct TestData
{
    vector<TestResult> results;
    AllowedObjects allowed_objects;
    FreezedObjects freezed_objects;
    AllowedCollisions allowed_collisions;
    vector<CollisionObject> collision_objects;
    vector<Scene> test_scenes;
};

json readJson(const string &conf_path);

void from_json(const json & j, TestResult &result);

void from_json(const json &j, TestData &test_data);

void from_json(const json &j, Quaternion &quaternion);

void from_json(const json &j, Point &point);

void from_json(const json &j, SceneObjectInstance &scene_object);

void from_json(const json &j, Scene &scene);

void from_json(const json &j, CollisionObject &collision_object);

#endif //JSON_DESERIALIZER_REQUEST_LOADER_H
