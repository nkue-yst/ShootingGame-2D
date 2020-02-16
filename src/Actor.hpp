#pragma once
#include <cmath>
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
    virtual void updateActor(float dt) {}  // �A�N�^�[���g�̍X�V

    void addComponent(class Component* component);
    void removeComponent(class Component* component);

    void computeWorldTransform();

    const State getState() const { return state_; }
    const mat4 getWorldTransform() const { return world_translation_; }
    void setPosition(const vec2& pos) { position_ = pos; }
    const vec2& getPosition() const { return position_; }
    void setRotation(const float rot) { rotation_ = rot; }
    const float getRotation() const { return rotation_; }
    void setScale(const float scl) { scale_ = scl; }
    const float getScale() const { return scale_; }
    class Game* getGame() { return game_; }

    vec2 getForward() const { return vec2(std::cos(rotation_), std::sin(rotation_)); }

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