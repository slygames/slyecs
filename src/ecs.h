#pragma once

#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"

using namespace godot;

namespace sly {

class Ecs : public RefCounted {
	GDCLASS(Ecs, RefCounted)

protected:
	static void _bind_methods();

public:
	Ecs() = default;
	~Ecs() override = default;

	// forward declare nested classes
	class Entity;
	class System;
	class Component;

	void print_type(const Variant &p_variant) const;
};


class Ecs::Entity : public RefCounted {
GDCLASS(Entity, RefCounted);

protected:
	static void _bind_methods() {};

public:
	Entity() = default;
	~Entity() override = default;
};


class Ecs::System : public RefCounted {
GDCLASS(System, RefCounted);

protected:
	static void _bind_methods() {};

public:
	System() = default;
	~System() override = default;
};


class Ecs::Component : public RefCounted {
GDCLASS(Component, RefCounted);

protected:
	static void _bind_methods() {};

public:
	Component() = default;
	~Component() override = default;
};

}