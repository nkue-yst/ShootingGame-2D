#pragma once
#include <cmath>
#include <cstdint>
#include <vector>
#include "Math.hpp"

class Actor
{
public:
    enum class State
    {
        EPause,
        EActive,
        EDead,
    };

    Actor(class Game* game);
    virtual ~Actor();

    void update(float dt);  // �V�X�e������Ăяo���X�V�֐�
    void updateComponents(float dt);  // �A�N�^�[�̎��R���|�[�l���g�̍X�V
    virtual void updateActor(float dt);  // �A�N�^�[���g�̍X�V

    void inputKeys(const uint8_t* key_state);  // Game����Ăяo��
    virtual void actorInput(const uint8_t* key_state);  // �I�[�o�[���C�h��

    void addComponent(class Component* component);
    void removeComponent(class Component* component);

    void computeWorldTransform();

    const State getState() const { return state_; }
    const mat4& getWorldTransform() const { return world_translation_; }
    const vec2& getPosition() const { return position_; }
    const float getRotation() const { return rotation_; }
    const float getScale() const { return scale_; }
    class Game* getGame() { return game_; }

    vec2 getForward() const { return vec2(std::cos(rotation_), std::sin(rotation_)); }

    void setPosition(const vec2& pos) { position_ = pos; need_recompute_world_transform_ = true; }
    void setRotation(const float rot) { rotation_ = rot; need_recompute_world_transform_ = true; }
    void setScale(const float scl) { scale_ = scl; need_recompute_world_transform_ = true; }

private:
    State state_;

    mat4 world_translation_;
    bool need_recompute_world_transform_;
    vec2 position_;
    float rotation_;
    float scale_;
    
    std::vector<class Component*> components_;
    class Game* game_;
};