#pragma once

#include <godot_cpp/classes/wrapped.hpp>
//#include "godot_cpp/variant/variant.hpp"
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/resource.hpp>
//#include <godot_cpp/classes/array.hpp> // Includes the definition for TypedArray
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/variant/typed_array.hpp>
//#include "godot_cpp/classes/ref_counted.hpp"
//#include <godot_cpp/classes/weak_ref.hpp>
#include <functional> // for std::hash
//#include <cstdint>
#include "slymap.h"
#include "util.h"
#include <godot_cpp/classes/scene_tree.hpp> // for Ecs::connect()
#include <godot_cpp/classes/window.hpp> // for Ecs::connect()
#include <godot_cpp/core/gdvirtual.gen.inc>

using namespace godot;

namespace sly {

class Ecs : public Node {
	GDCLASS(Ecs, Node)

public:
	// forward declare nested classes
	class Base;
	class Entity;
	class System;
	class Component;

	static map<Entity*> entity_map;
	static map<Component*> component_map;
	static map<System*> system_map;

	static Ecs* singleton;

protected:
	static void _bind_methods();

	void _notification(int p_what);

public:
	Ecs() = default;
	~Ecs() override = default;

	// static method to get the singleton instance
	static Ecs* get_singleton();

	// alternate way to connect from _ready in gdscript by calling Ecs.connect(get_tree()) instead of using autoload scene
	void connect(SceneTree* scene_tree);

	void process_ecs();

	void create_entity(Object* object, const TypedArray<Component>& components);
	void remove_entity(Object* object);
};

class Ecs::Base : public Resource {
GDCLASS(Base, Resource);

protected:
	static void _bind_methods() {};

public:
	Base() = default;
	~Base() override = default;
	
	int id;

	Base(int new_id) : id(new_id) {}

	// to enable hashing in unordered map
	bool operator==(const Base& other) const {
        return id == other.id;
    }
};


class Ecs::Entity : public Base {
GDCLASS(Entity, Base);

protected:
	static void _bind_methods();
public:
	Entity() {};
	~Entity() override = default;
	Entity(Object* new_object) : object(new_object) {}
	array<int> components;
	Object* object; // actual godot game object
};


class Ecs::System : public Base {
GDCLASS(System, Base);

protected:
	static void _bind_methods();

public:
	System() = default;
	~System() override = default;

	array<int> components_required;

	virtual void update();
	GDVIRTUAL0(_update);
};


class Ecs::Component : public Base {
GDCLASS(Component, Base);

	StringName name;

protected:
	static void _bind_methods();

public:
	Component() = default;
	~Component() override = default;

	void set_name(StringName& new_name) { name = new_name; }
	StringName& get_name() {return name;}

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
			return hash<int>()(ptr->id); 
		}
	};
} // namespace std
