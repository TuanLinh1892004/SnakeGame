#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID getComponentTypeID()
{
    static ComponentID lastID = 0;
    return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
    static ComponentID typeID = getComponentTypeID();
    return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset <maxComponents>;
using ComponentArray = std::array <Component*, maxComponents>;

class Component
{
public:
    Entity* entity;

    virtual void init() {}
    virtual void update() {}
    virtual void render() {}

    virtual ~Component() {}
};

class Entity
{
private:
    bool active = true;
    std::vector <std::unique_ptr <Component> > components;

    ComponentArray componentArray;
    ComponentBitSet componentBitSet;

public:
    void update()
    {
        for (auto &c : components) c->update();
    }
    void render()
    {
        for (auto &c : components) c->render();
    }

    bool isActive() const { return active; }
    void destroy() { active = 0; }

    template <typename T> bool hasComponent() const
    {
        return componentBitSet[getComponentTypeID<T>];
    }

    template <typename T, typename... TArgs>
    T &addComponent(TArgs&&... mArgs)
    {
        T *c(new T(std::forward <TArgs> (mArgs)...));
        c->entity = this;
        std::unique_ptr <Component> uPtr{ c };
        components.emplace_back(std::move(uPtr));

        componentArray[getComponentTypeID<T>()] = c;
        componentBitSet[getComponentTypeID<T>()] = 1;

        c->init();
        return *c;
    }

    template <typename T> T& getComponent() const
    {
        auto ptr(componentArray[getComponentTypeID<T>()]);
        return *static_cast<T*>(ptr);
    }
};

class Manager
{
private:
    std::vector <std::unique_ptr <Entity> > entities;

public:
    void update()
    {
        for (auto &e : entities) e->update();
    }
    void render()
    {
        for (auto &e : entities) e->render();
    }
    void refresh()
    {
        entities.erase(std::remove_if(std::begin(entities), std::end(entities),
            [](const std::unique_ptr <Entity> &mEntity)
            {
                return !(mEntity->isActive());
            }),
            std::end(entities));
    }

    Entity &addEntity()
    {
        Entity *e = new Entity();
        std::unique_ptr <Entity> uPtr{ e };
        entities.emplace_back(std::move(uPtr));
        return *e;
    }
};

