#pragma once
#include"json.hpp"
//À•W‚ğæ“¾‚·‚é‚½‚ß‚Ì\‘¢‘Ì
struct VECTOR2
{
    float x, y;
};

//json‚É•ÏŠ·‚·‚é‚½‚ß‚ÌŠÖ”
void to_json(nlohmann::json& j, const VECTOR2& v)
{
	j = nlohmann::json{ {"x",v.x},{"y",v.y} };
}

//json‚©‚ç•ÏŠ·‚·‚é‚½‚ß‚ÌŠÖ”
void from_json(const nlohmann::json& j, VECTOR2& v)
{
	j.at("x").get_to(v.x);
	j.at("y").get_to(v.y);
}