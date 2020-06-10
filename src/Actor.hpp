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

    void update(float dt);  // システムから呼び出す更新関数
    void updateComponents(float dt);  // アクターの持つコンポーネントの更新
    virtual void updateActor(float dt);  // アクター自身の更新

    void inputKeys(const uint8_t* key_state);  // Gameから呼び出し
    virtual void actorInput(const uint8_t* key_state);  // オーバーライド可

    void addComponent(class Component* component);
    void removeComponent(class Component* component);

    void computeWorldTransform();

    const State getState() const { return state_; }
    const Mat4& getWorldTransform() const { return world_translation_; }
    const Vec2& getPosition() const { return position_; }
    const float getRotation() const { return rotation_; }
    const float getScale() const { return scale_; }
    class Game* getGame() { return game_; }

    Vec2 getForward() const { return Vec2(std::cos(rotation_), std::sin(rotation_)); }

    void setState(State state) { state_ = state; }
    void setPosition(const Vec2& pos) { position_ = pos; need_recompute_world_transform_ = true; }
    void setRotation(const float rot) { rotation_ = rot; need_recompute_world_transform_ = true; }
    void setScale(const float scl) { scale_ = scl; need_recompute_world_transform_ = true; }

    bool getIsPlayer() const { return is_player_; }
    void setIsPlayer(const bool is_player) { is_player_ = is_player; }

private:
    State state_;

    Mat4 world_translation_;
    bool need_recompute_world_transform_;
    Vec2 position_;
    float rotation_;
    float scale_;
    
    std::vector<class Component*> components_;
    class Game* game_;
    bool is_player_;
};