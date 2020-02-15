#pragma once
#include <cmath>
#include <glm/glm.hpp>

namespace mat {
    // スケール行列作成
    glm::mat4 createScale(float x_scale, float y_scale, float z_scale);
    glm::mat4 createScale(float scale);

    // 回転行列作成
    glm::mat4 createRotationX(float theta);
    glm::mat4 createRotationY(float theta);
    glm::mat4 createRotationZ(float theta);

    // 平行移動行列作成
    glm::mat4 createTranslation(glm::vec3 trans);

    // 2Dのビュー射影
    glm::mat4 createSimpleView(float width, float height);
}