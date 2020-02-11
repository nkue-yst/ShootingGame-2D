#pragma once
#include <cmath>
#include <vector>
#include "Math.hpp"

class Actor
{
public:
    enum State
    {
        EPause,
        EActive,
        EDead,
    };

    Actor(class Game* game);
    virtual ~Actor();

    void update(float dt);  // システムから呼び出す更新関数
    //void updateComponents(float dt);  // アクターの持つコンポーネントの更新
    //virtual void updateActor(float dt);  // アクター自身の更新

    //void addComponent(class Component* component);
    void removeComponent(class Component* component);

    const State getState() const { return state_; }
    void setPosition(const Vec2& pos) { position_ = pos; }
    const Vec2& getPosition() const { return position_; }
    void setRotation(const float rot) { rotation_ = rot; }
    const float getRotation() const { return rotation_; }
    void setScale(const float scl) { scale_ = scl; }
    const float getScale() const { return scale_; }

    Vec2 getForward() const { return Vec2(std::cos(rotation_), std::sin(rotation_)); }

private:
    State state_;
    Vec2 position_;
    float rotation_;
    float scale_;
    
    std::vector<class Component*> components_;
    class Game* game_;
};