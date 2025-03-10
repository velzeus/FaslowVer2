#pragma once
#include"json.hpp"
//座標を取得するための構造体
struct VECTOR2
{
    float x, y;
};

//jsonに変換するための関数
void to_json(nlohmann::json& j, const VECTOR2& v)
{
	j = nlohmann::json{ {"x",v.x},{"y",v.y} };
}

//jsonから変換するための関数
void from_json(const nlohmann::json& j, VECTOR2& v)
{
	j.at("x").get_to(v.x);
	j.at("y").get_to(v.y);
}