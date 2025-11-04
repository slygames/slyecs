#pragma once

#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/classes/ref_counted.hpp"
//#include <godot_cpp/classes/weak_ref.hpp>
#include <functional> // for std::hash
//#include <cstdint>
#include "slymap.h"

using namespace godot;

namespace sly {

class Ecs : public RefCounted {
	GDCLASS(Ecs, RefCounted)

public:
	// forward declare nested classes
	class Base;
	class Entity;
	class System;
	class Component;

	static map<Entity*> entity_map;
	static map<Component*> component_map;
	static map<System*> system_map;

protected:
	static void _bind_methods();

public:
	Ecs() = default;
	~Ecs() override = default;

	void process_ecs();

	void print_type(const Variant &p_variant) const;
};

class Ecs::Base : public RefCounted {
GDCLASS(Base, RefCounted);

protected:
	static void _bind_methods() {};

public:
	Base() = default;
	~Base() override = default;
	
	uint32_t id;

	Base(int new_id) : id(new_id) {}

	// to enable hashing in unordered map
	bool operator==(const Base& other) const {
        return id == other.id;
    }
};


class Ecs::Entity : public Base {
GDCLASS(Entity, Base);

protected:
	static void _bind_methods() {};

public:
	Entity() = default;
	~Entity() override = default;
	
	array<uint32_t> components;

};


class Ecs::System : public Base {
GDCLASS(System, Base);

protected:
	static void _bind_methods() {};

public:
	System() = default;
	~System() override = default;

	array<uint32_t> components_required;
};


class Ecs::Component : public RefCounted {
GDCLASS(Component, RefCounted);

protected:
	static void _bind_methods() {};

public:
	Component() = default;
	~Component() override = default;
};

} // namespace sly


/**
 * Hash function for reverse lookup hash table, used by sly::map so it can store pointers to Ecs base objects 
 */
 namespace std {
	template <>
	struct hash<sly::Ecs::Base> {
		size_t operator()(const sly::Ecs::Base* ptr) const {
			// Hash the id member of the object pointed to by ptr
			return hash<uint32_t>()(ptr->id); 
		}
	};
} // namespace std
