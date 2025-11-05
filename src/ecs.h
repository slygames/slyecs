#pragma once

#include <godot_cpp/classes/wrapped.hpp>
//#include "godot_cpp/variant/variant.hpp"
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/resource.hpp>
//#include <godot_cpp/classes/array.hpp> // Includes the definition for TypedArray
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/classes/resource_loader.hpp> // for load_system_script
#include <godot_cpp/classes/script.hpp> // for load_system_script
#include <godot_cpp/variant/string_name.hpp>
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
//#include <godot_cpp/classes/expression.hpp> // evaluate

using namespace godot;

namespace sly {


// forward declare classes
class ResourceEcs;
class Entity;
class System;
class Component;

struct Tag {
	StringName label;
};

class TagContainer {
	map<Tag> container;
};

class EcsSpec {
	bool is_enabled;

	EcsSpec() : is_enabled(true) {};
};

class ComponentSpec {

};

class EntitySpec {

};

class SystemSpec {
	map<Tag> tags_required;
	map<Tag> tags_forbidden;
	map<Tag> tags_add;
	map<Tag> tags_remove;
};

















/**
 * Ecs runs as a singleton and calls update on each system in physics process.
 */
class Ecs : public Node {
	GDCLASS(Ecs, Node)

public:
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

class ResourceEcs : public Resource {
GDCLASS(ResourceEcs, Resource);

protected:
	static void _bind_methods();

public:
	ResourceEcs() = default;
	~ResourceEcs() override = default;
	
	int id;

	ResourceEcs(int new_id) : id(new_id) {}

	StringName name_var;

	// getters and setters
    const StringName& get_name_var() const { return name_var; };
    void set_name_var(const StringName& p_name_var) { name_var = p_name_var; };


	// to enable hashing in unordered map
	bool operator==(const ResourceEcs& other) const {
        return id == other.id;
    }
};
/*
class Tag : public Object {
	GDCLASS(Tag, Object);
	
protected:
	static void _bind_methods() {};

public:
	Tag() = default;
	~Tag() override = default;

	map<StringName*> tags;
};*/

class RefCountedEcs : public RefCounted {
GDCLASS(RefCountedEcs, RefCounted);

protected:
	static void _bind_methods() {};

public:
	RefCountedEcs() = default;
	~RefCountedEcs() override = default;
	
	int id;

	RefCountedEcs(int new_id) : id(new_id) {}

	// to enable hashing in unordered map
	bool operator==(const RefCountedEcs& other) const {
        return id == other.id;
    }
};

class Entity : public ResourceEcs {
GDCLASS(Entity, ResourceEcs);

protected:
	static void _bind_methods();

public:
	Entity() {};
	~Entity() override = default;
	Entity(Object* new_object) : object(new_object) {}

	//array<int> systems;
	
	array<int> components;
	
	Object* object; // actual godot game object
};

/*
class Tags : public Object {
GDCLASS(Tags, Object);

	static const TypedArray<Callable>& callables;
	static const TypedArray<int>& get_affected_entities();
	
protected:
	static void _bind_methods() {};

public:
	static map<StringName> tag_label;
	static TypedArray<int> tag_map;

};
*/

Class SystemUpdater : public Object {
GDCLASS(SystemUpdater, Object);

/*
//todo: enums should be components so this value can be read from the component instead, then system_combat can handle all these states, and have a gdscript equivalent in systems.gd
enum : unsigned char {
	COMBAT_PUNCH_RIGHT,
	COMBAT_PUNCH_LEFT,
	COMBAT_KICK_LEFT,
	COMBAT_KICK_RIGHT,
	COMBAT_KICK_LEFT,
	COMBAT_KICK_RIGHT,
	COMBAT_KICK_RIGHT,
};
*/

	static const TypedArray<Callable>& callables;
	static const void get_affected_entities(TypedArray<int>& entities) {};
	
protected:
	static void _bind_methods() {};

public:
	//static TypedArray<Callable> callables;

	static void system_movement() {};
	/*
	static system_damage();
	static system_render();
	static system_combat();
	*/
};


class System : public RefCountedEcs {
GDCLASS(System, RefCounted);

protected:
	static void _bind_methods();

	// load callable functions into Ecs
	void load_callable();
	void load_callable_script();

public:
	System() = default;
	~System() override = default;

	Callable system_callable; // callable called by update()

	static bool run_query(String query) { return false; } // returns true if query was successful }; // bulk queries to update components e.g., to multiply all values by scalaras and same index values in other components by using queries like (movement_component = velocity_component * position_component * direction_component * delta)

	//TypedArray<int> effects;

	//array<int> components_required;

	virtual void update();
	GDVIRTUAL0(_update);
};


//template <typename T>
class Component : public ResourceEcs {
GDCLASS(Component, ResourceEcs);

protected:
	static void _bind_methods();

public:
	Component() = default;
	~Component() override = default;

	const Variant& get_var(int entity_id) const { return 0; }; // get value (does conversion to_var())
	void set_var(int entity_id, Variant& value) {}; // sets value from variant (does conversion from_var())

	template <typename T>
	Variant to_var(T val) {}; // convert actual type to variant for editor

	template <typename T>
	T from_var(Variant var) {};	// convert variant from editor to actual type

	template <typename T>
	void set_value(int entity_id, T& value) {}; // sets value directly (no conversion)

	template <typename T>
	const T& get_value(int entity_id) { return 0; }; // get value directly (no conversion)


	//todo:overload * operator and maybe = operator in sly::map so that two components can be multiplied together which will be useful to multiply all values by scalaras and same index values in other components by using queries like (movement_component = velocity_component * position_component * direction_component * delta)
	map<Variant*> data_var;
	map<bool> data_bool;
	map<int> data_int;
	map<float> data_float;
	map<Vector2*> data_vector2;
	map<Vector3*> data_vector3;
	map<Transform2D*> data_transform2d;
	map<Transform3D*> data_transform3d;
	map<String*> data_string;
	map<StringName*> data_string_name;

/*
	void set_name(StringName new_name) 
	StringName get_name() {return name_var;}
*/
};


} // namespace sly


/**
 * Hash function for reverse lookup hash table, used by sly::map so it can store pointers to any ResourceEcs objects i.e. Entity, Component, System resources
 */
 namespace std {
	template <>
	struct hash<sly::ResourceEcs> {
		size_t operator()(const sly::ResourceEcs* ptr) const {
			// Hash the id member of the object pointed to by ptr
			return hash<int>()(ptr->id); 
		}
	};
} // namespace std
