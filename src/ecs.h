#pragma once

#include <godot_cpp/classes/wrapped.hpp>
//#include "godot_cpp/variant/variant.hpp"
#include <godot_cpp/classes/node2d.hpp>
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
class Tags;

/*
struct Tag {
	StringName label;
};
*/

/*
class EcsSpec {
	bool is_enabled;

	EcsSpec() : is_enabled(true) {};
};

class ComponentSpec {
	map<Variant*> data_var;
};

class EntitySpec {
	StringName name_var;

	// getters and setters
    const StringName& get_name_var() const { return name_var; };
    void set_name_var(const StringName& p_name_var) { name_var = p_name_var; };
};

class SystemSpec {
};
*/
















/**
 * Ecs runs as a singleton and calls update on each system in physics process.
 */
class Ecs : public Node {
	GDCLASS(Ecs, Node)

public:
	static map<Entity*> entity_map;
	static map<Component*> component_map;
	static map<System*> system_map;
	static map<StringName*> tag_map;

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

	//void register_entity(Object* object, const TypedArray<Component>& components = TypedArray<Component>()); // todo: add
	//void register_entity(Object* object, const TypedArray<Component>& components = TypedArray<Component>());
	
	void register_entity(Entity* entity);
	void unregister_entity(Entity* entity);

	void register_system(System* system);
	void unregister_system(System* system);

	void register_component(Component* system);
	void unregister_component(Component* system);
};

class ResourceEcs : public Resource {
GDCLASS(ResourceEcs, Resource);

	int id;

protected:
	static void _bind_methods();
	
public:
	ResourceEcs() = default;
	~ResourceEcs() override = default;
	
	ResourceEcs(int p_id) : id(p_id) {}

	StringName name_var;

	// getters and setters
    const StringName& get_name_var() const { return name_var; };
    void set_name_var(const StringName& p_name_var) { name_var = p_name_var; };

	// to enable hashing in unordered map
	bool operator==(const ResourceEcs& other) const {
        return id == other.id;
    }

	// setters and getters
	void set_id(int p_id) { id = p_id; }
	int get_id() const { return id; };
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

	RefCountedEcs(int p_id) : id(p_id) {}

	// to enable hashing in unordered map
	bool operator==(const RefCountedEcs& other) const {
        return id == other.id;
    }
};


/*
class NodeECS : public godot::Node2D {
GDCLASS(NodeECS, Node2D);

	int id;

	Ref<Entity> entity;

protected:
	static void _bind_methods();

public:
	NodeECS() = default;
	~NodeECS() override = default;
	
	NodeECS(int p_id) : id(p_id) {}

	// to enable hashing in unordered map
	bool operator==(const NodeECS& other) const {
        return id == other.id;
    }

	void set_entity(const Ref<Entity>& p_entity) { entity = p_entity; }
	Ref<Entity> get_entity() const { return entity; };
};
*/

class Entity : public Resource {
GDCLASS(Entity, Resource);

	int id;

	//todo:these should all be ids really.. not nodes and components, but components are easier in editor picker..
	TypedArray<Node> nodes;	// actual godot nodes of this entity

	//todo: this is unnecessary, should only store ints and those should be in a register in Ecs class or something. Entity just needs it's own id.
	TypedArray<Component> components;

protected:
	static void _bind_methods();

public:
	Entity() = default;
	~Entity() override = default;

	//Entity(int p_id) : id(p_id) {}

	// to enable hashing in unordered map
	bool operator==(const Entity& other) const {
        return id == other.id;
    }

	//Entity(Object* p_object) : object(p_object) {}
	//Object* object; // actual godot game object

	// todo: these should be in EntitySpec or something like this on a per type basis to set the default values
	
	// setters and getters
	void set_id(int p_id) { id = p_id; }
	int get_id() const { return id; };

	void set_components(const TypedArray<Component>& p_components) { components = p_components; }
	TypedArray<Component> get_components() const { return components; };

	/*
	void set_nodes(const TypedArray<Node>& p_nodes) { nodes = p_nodes; }
	TypedArray<Node> get_nodes() const { return nodes; };
	*/
};


/*
// this should be Entity and should be a RefCounted, not in editor.
class Actor : public NodeECS {
GDCLASS(Actor, NodeECS);

	//todo: this is unnecessary, should only store ints and those should be in a register in Ecs class or something. Entity just needs it's own id.
	TypedArray<Component> components;

	Ref<Entity> entity;

protected:
	static void _bind_methods();

public:
	Actor() {};
	~Actor() override = default;
	
	//Entity(Object* p_object) : object(p_object) {}
	//Object* object; // actual godot game object

	// todo: these should be in EntitySpec or something like this on a per type basis to set the default values
	
	// setters and getters
	//void set_components(const TypedArray<Component>& p_components) { components = p_components; }
	//TypedArray<Component> get_components() const { return components; };


	void set_entity(const Ref<Entity>& p_entity) { entity = p_entity; }
	Ref<Entity> get_entity() const { return entity; };
};
*/

//todo: this should be Entity
class NodeECS : public Node {
GDCLASS(NodeECS, Node);

	int id;

	/*
	TypedArray<Component> components;
	*/

	Ref<Entity> entity;
	//Entity entity;

protected:
	static void _bind_methods();

public:
	NodeECS() = default;
	~NodeECS() override = default;
	//Entity(const Entity& other) = default; // default copy constructor (should be generated implicitly by the compiler)
	NodeECS(int p_id) : id(p_id) {}

	// to enable hashing in unordered map
	bool operator==(const NodeECS& other) const {
        return id == other.id;
    }

	//Entity(Object* p_object) : object(p_object) {}
	//Object* object; // actual godot game object

	// todo: these should be in EntitySpec or something like this on a per type basis to set the default values
	
	// setters and getters
	void set_id(int p_id) { id = p_id; }
	int get_id() const { return id; };

	void set_entity(const Ref<Entity>& p_entity) { entity = p_entity; }
	Ref<Entity> get_entity() const { return entity; };

	/*
	void set_entity(const Entity& p_entity) { entity = p_entity; }
	Entity get_entity() const { return entity; };
	*/

	/*
	void set_components(const TypedArray<Component>& p_components) { components = p_components; }
	TypedArray<Component> get_components() const { return components; };
	*/
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


class Tags : public ResourceEcs {
GDCLASS(Tags, ResourceEcs); 

	TypedArray<StringName> tags;

protected:
	static void _bind_methods() {};

public:
	Tags() = default;
	~Tags() override = default;

	void set_tags(const TypedArray<StringName>& p_tags) { tags = p_tags; }
	TypedArray<StringName> get_tags() const { return tags; };
};

//template <typename T>
class Component : public ResourceEcs {
GDCLASS(Component, ResourceEcs);

	Variant data_var;

protected:
	static void _bind_methods();

public:
	Component() = default;
	~Component() override = default;
	Component(Variant p_data_var) { data_var = p_data_var; }

	void set_data_var(const Variant& p_data_var) { data_var = p_data_var; }; // sets value from variant (does conversion from_var())
	Variant get_data_var() const { return data_var; }; // get value (does conversion to_var())

	void set_var(int entity_id, Variant& value) {}; // sets value from variant (does conversion from_var())
	const Variant get_var(int entity_id) const { return 0; }; // get value (does conversion to_var())

	template <typename T>
	Variant to_var(T val) { return Variant(val); }; // convert actual type to variant for editor

	template <typename T>
	T from_var(Variant var) { return cast_to<T>(var); };	// convert variant from editor to actual type

	template <typename T>
	const T get_value(int entity_id) { return T(); }; // get value directly (no conversion)

	template <typename T>
	void set_value(int entity_id, T& value) {}; // sets value directly (no conversion)

	//todo:overload * operator and maybe = operator in sly::map so that two components can be multiplied together which will be useful to multiply all values by scalaras and same index values in other components by using queries like (movement_component = velocity_component * position_component * direction_component * delta)

	/*
	map<bool> data_bool;
	map<int> data_int;
	map<float> data_float;
	map<Vector2*> data_vector2;
	map<Vector3*> data_vector3;
	map<Transform2D*> data_transform2d;
	map<Transform3D*> data_transform3d;
	map<String*> data_string;
	map<StringName*> data_string_name;
*/

/*
	void set_name(StringName p_name) 
	StringName get_name() {return name_var;}
*/
};



class SystemUpdater : public Object {
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


class System : public ResourceEcs {
GDCLASS(System, ResourceEcs);

	TypedArray<Component> components;
	TypedArray<StringName> tags_required;

	//map<Tag*> tags_required;
	Tags tags_forbidden;
	Tags tags_add;
	Tags tags_remove;

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

	// setters and getters
	void set_components(const TypedArray<Component>& p_components) { components = p_components; }
	TypedArray<Component> get_components() const { return components; };

	void set_tags_required(TypedArray<StringName> p_tags_required) { tags_required = p_tags_required; }
    TypedArray<StringName> get_tags_required() const { return tags_required; }

	virtual void update();
	GDVIRTUAL0(_update);
};




} // namespace sly


/**
 * Hash function for reverse lookup hash table, used by sly::map so it can store pointers to any ResourceEcs objects i.e. Entity, Component, System resources
 */
/*
 namespace std {

	template <typename T>
	struct hash<Ref<T>> {
		size_t operator()(const godot::Ref<T>& ref) const {
        // Hash the underlying pointer
        return std::hash<T*>{}(ref.ptr()); 
		}
	};

	template <>
	struct hash<godot::WeakRef> {
		size_t operator()(const godot::WeakRef& wr) const {
			// Get the underlying Object* from the WeakRef
			godot::Object* obj = wr.get_ref(); // get_ref() returns Object*
			return std::hash<godot::Object*>()(obj);
		}
	};

	//todo:remove
	template <>
	struct hash<sly::ResourceEcs> {
		size_t operator()(const sly::ResourceEcs* ptr) const {
			// Hash the id member of the object pointed to by ptr
			return hash<int>()(ptr->get_id()); 
		}
	};
	
} // namespac
 e std
*/
