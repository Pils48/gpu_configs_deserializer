//
// Created by nikita on 27.02.2020.
//

#include <fstream>
#include "../include/request_loader.h"

json readJson(const std::string &conf_path)
{
    try
    {
        std::ifstream f(conf_path);
        if (f)
        {
            json j;
            f >> j;
            return j;
        }
        else
        {
            throw std::runtime_error(std::string("Failed to open file ") + conf_path + " for reading");
        }
    }
    catch (const json::exception &exception)
    {
        std::throw_with_nested(std::invalid_argument{ "json path: " + conf_path });
    }
}

TestResults loadResults(const std::string &conf_path)
{
    TestResults result;
    const auto json_config = readJson(conf_path);
    if (json_config.find("results") != json_config.end()) {
        const auto test_results = json_config.at("results");
        for (const auto &test_result : test_results)
        {
            result.push_back(test_result.get<bool>());
        }
    }
    return result;
}

std::vector<Scene> loadScenes(const std::string &conf_path)
{
    std::vector<Scene> result;
    const auto json_config = readJson(conf_path);
    if (json_config.find("scenes") != json_config.end())
    {
        const auto request_scenes = json_config.at("scenes");
        for (const auto &obj : request_scenes)
        {
            Scene scene;
            std::string id;
            const auto scene_objects = obj.at("scene_objects");
            for (const auto &obj : scene_objects)
            {
                const auto point_coef = obj.at("origin").get<std::array<double, 3>>();
                const auto quaternion_coef = obj.at("quaternion").get<std::array<double, 4>>();
                Point point = {point_coef[0], point_coef[1], point_coef[3]};
                Quaternion quaternion = {quaternion_coef[0], quaternion_coef[1], quaternion_coef[2], quaternion_coef[3]};
                Pose pose = {point, quaternion};
                id = obj.at("id").get<std::string>();
                scene.object_poses.emplace(std::make_pair(id, pose));
            }
            result.push_back(scene);
        }
    }
    return result;
}

std::vector<CollisionObject> loadObjects(const std::string &conf_path)
{
    std::vector<CollisionObject> result;
    const auto json_config = readJson(conf_path);
    if (json_config.find("collision_objects") != json_config.end())
    {
        const auto request_objs = json_config.at("collision_objects");
        CollisionObject CollisionObject;
        for (const auto &obj : request_objs)
        {
            CollisionObject.object_id = obj.at("id").get<std::string>();
            CollisionObject.path_to_mesh = obj.at("mesh_file").get<std::string>();
            result.push_back(CollisionObject);
        }
    }
    return result;
}

FreezedObjects loadFreezedObjects(const std::string &conf_path)
{
    FreezedObjects result;
    const auto json_config = readJson(conf_path);
    if (json_config.find("freezed_objects") != json_config.end())
    {
        const auto objects = json_config.at("freezed_objects");
        for (const auto &obj : objects)
        {
            result.push_back(obj.get<std::string>());
        }
    }
    return result;
}

AllowedObjects loadAllowedCollisionObjects(const std::string &conf_path)
{
    AllowedObjects result;
    const auto json_config = readJson(conf_path);
    if (json_config.find("allowed_objects") != json_config.end())
    {
        const auto objects = json_config.at("allowed_objects");
        for (const auto &obj : objects)
        {
            result.push_back(obj.get<std::string>());
        }
    }
    return result;
}

AllowedCollisions loadAllowedCollisionPairs(const std::string &conf_path)
{
    AllowedCollisions result;
    const auto json_config = readJson(conf_path);
    if (json_config.find("allowed_pairs") != json_config.end())
    {
        const auto pairs = json_config.at("allowed_pairs");
        for (const auto &pair : pairs)
        {
            result.push_back(pair.get<std::array<std::string, 2>>());
        }
    }
    return result;
}

TestData loadTestDataFromJson(const std::string &conf_path)
{
    TestData res_request;
    res_request.allowed_objects = loadAllowedCollisionObjects(conf_path);
    res_request.collision_objects = loadObjects(conf_path);
    res_request.test_scenes = loadScenes(conf_path);
    res_request.allowed_collisions = loadAllowedCollisionPairs(conf_path);
    res_request.results = loadResults(conf_path);
    res_request.freezed_objects = loadFreezedObjects(conf_path);
    return res_request;
}
