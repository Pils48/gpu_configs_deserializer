//
// Created by nikita on 27.02.2020.
//

#include <fstream>
#include "../include/request_loader.h"

void from_json(const json & j, TestResult &result)
{
    result = {
            j.at("collision").get<bool>(),
            j.value<CollidingPairs>("colliding_objects", {}),
    };
}

void from_json(const json &j, TestData &test_data)
{
    test_data = {
            j.at("results").get<vector<TestResult>>(),
            j.value<vector<string>>("allowed_objects", {}),
            j.value<vector<string>>("freezed_objects", {}),
            j.value<vector<array<string, 2>>>("allowed_pairs", {}),
            j.at("collision_objects").get<vector<CollisionObject>>(),
            j.at("scenes").get<vector<Scene>>()};
};

void from_json(const json &j, Quaternion &quaternion) {
    const auto coefs = j.get<array<double, 4>>();
    quaternion = {coefs[0], coefs[1], coefs[2], coefs[3]};
}

void from_json(const json &j, Point &point) {
    const auto coefs = j.get<array<double, 3>>();
    point = {coefs[0], coefs[1], coefs[2]};
}

void from_json(const json &j, SceneObjectInstance &scene_object) {
    scene_object = {
            scene_object.object_id = j.at("id").get<string>(),
            scene_object.pose.origin = j.at("origin").get<Point>(),
            scene_object.pose.orientation = j.at("quaternion").get<Quaternion>()
    };
}

void from_json(const json &j, Scene &scene) {
    scene = {
            j.at("scene_objects").get<vector<SceneObjectInstance>>()
    };
}

void from_json(const json &j, CollisionObject &collision_object) {
    collision_object = {
            j.at("id").get<string>(),
            j.at("mesh_file").get<string>(),
    };
}

json readJson(const string &conf_path) {
    try {
        ifstream f(conf_path);
        if (f) {
            json j;
            f >> j;
            return j;
        } else {
            throw runtime_error(string("Failed to open file ") + conf_path + " for reading");
        }
    }
    catch (const json::exception &exception) {
        throw_with_nested(invalid_argument{"json path: " + conf_path});
    }
}

