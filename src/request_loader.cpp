//
// Created by nikita on 27.02.2020.
//

#include <fstream>
#include "../include/request_loader.h"

AllowedCollisions loadAllowedCollisions(const std::string &basicString);

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
            scene.collision_result = scene.collision_result = obj.at("collision_result").get<bool>();
            result.push_back(scene);
        }
    }
    return result;
}

std::vector<collision_object> loadObjects(const std::string &conf_path)
{
    std::vector<collision_object> result;
    const auto json_config = readJson(conf_path);
    if (json_config.find("collision_objects") != json_config.end())
    {
        const auto request_objs = json_config.at("collision_objects");
        collision_object collision_object;
        for (const auto &obj : request_objs)
        {
            collision_object.object_id = obj.at("id").get<std::string>();
            collision_object.path_to_mesh = obj.at("mesh_file").get<std::string>();
            collision_object.is_ignored = obj.at("allow_collision").get<bool>();
            const std::string type_str = obj.at("type").get<std::string>();
            if (type_str == "static")
            {
                collision_object.type = STATIC;
            }
            else if (type_str == "active")
            {
                collision_object.type = ACTIVE;
            }
            else
            {
                throw std::invalid_argument{"Undefined argument for field type could be active or static only!"};
            }
            result.push_back(collision_object);
        }
    }
    return result;
}

AllowedCollisions loadAllowedCollisionPairs(const std::string &conf_path)
{
    AllowedCollisions result;
    const auto json_config = readJson(conf_path);
    if (json_config.find("allowed_pairs") != json_config.end()) {
        const auto pairs = json_config.at("allowed_pairs");
        for (const auto &pair : pairs)
        {
            auto str_pair = pair.get<std::array<std::string, 2>>();
            result.push_back(std::make_pair(str_pair[0], str_pair[1]));
        }
    }
    return result;
}

Request loadRequestFromJson(const std::string &conf_path)
{
    Request res_request;
    res_request.collision_objects = loadObjects(conf_path);
    res_request.test_scenes = loadScenes(conf_path);
    res_request.allowedCollisions = loadAllowedCollisionPairs(conf_path);
    return res_request;
}
