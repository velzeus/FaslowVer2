#pragma once
#include"json.hpp"
//���W���擾���邽�߂̍\����
struct VECTOR2
{
    float x, y;
};

//json�ɕϊ����邽�߂̊֐�
void to_json(nlohmann::json& j, const VECTOR2& v)
{
	j = nlohmann::json{ {"x",v.x},{"y",v.y} };
}

//json����ϊ����邽�߂̊֐�
void from_json(const nlohmann::json& j, VECTOR2& v)
{
	j.at("x").get_to(v.x);
	j.at("y").get_to(v.y);
}