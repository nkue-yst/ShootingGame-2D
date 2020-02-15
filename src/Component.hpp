#pragma once

class Component
{
public:
    Component(class Actor* owner, int update_order = 100);
    virtual ~Component();

    virtual void update(float dt);
    virtual void onUpdateWorldTransform() {}

    int getUpdateOrder() const { return update_order_; }

protected:
    class Actor* owner_;  // 所有アクター
    int update_order_;
};