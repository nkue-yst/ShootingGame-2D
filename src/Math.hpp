#pragma once
#include <cmath>
#include <glm/glm.hpp>

namespace mat {
    // �X�P�[���s��쐬
    glm::mat4 createScale(float x_scale, float y_scale, float z_scale);
    glm::mat4 createScale(float scale);

    // ��]�s��쐬
    glm::mat4 createRotationX(float theta);
    glm::mat4 createRotationY(float theta);
    glm::mat4 createRotationZ(float theta);

    // ���s�ړ��s��쐬
    glm::mat4 createTranslation(glm::vec3 trans);

    // 2D�̃r���[�ˉe
    glm::mat4 createSimpleView(float width, float height);
}