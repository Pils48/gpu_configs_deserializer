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

std::vector<Scene> loadScenes(const std::string &conf_path)
{
    std::vector<Scene> result;
    auto json_obj = readJson(conf_path);
    if (json_obj.find("scenes") != json_obj.end())
    {
        const auto marked_objs = json_obj.at("scenes");
        for (const auto &obj : marked_objs)
        {
            Scene scene;
            std::string id;
            const auto scene_objects = obj.at("c_objs");
            for (const auto &obj : scene_objects)
            {
                const auto origin = obj.at("origin").get<std::array<double, 3>>();
                const auto quat_coef = obj.at("quaternion").get<std::array<double, 4>>();
                Point point = {origin[0], origin[1], origin[3]};
                Quaternion quaternion = {quat_coef[0], quat_coef[1], quat_coef[2], quat_coef[3]};
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
    auto json_obj = readJson(conf_path);
    if (json_obj.find("collision_objects") != json_obj.end())
    {
        const auto marked_objs = json_obj.at("collision_objects");
        collision_object co;
        for (const auto &obj : marked_objs)
        {
            co.object_id = obj.at("id").get<std::string>();
            co.path_to_mesh = obj.at("mesh_file").get<std::string>();
            co.is_ignored = obj.at("allowed_collision").get<bool>();
            result.push_back(co);
        }
    }
    return result;
}

Request loadRequestFromJson(const std::string &conf_path)
{
    Request res_request;
    res_request.collision_objects = loadObjects(conf_path);
    res_request.test_scenes = loadScenes(conf_path);
    return res_request;
}