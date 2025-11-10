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
#include <variant> // for std::variant
#include <godot_cpp/classes/scene_tree.hpp> // for Ecs::connect()
#include <godot_cpp/classes/window.hpp> // for Ecs::connect()
#include <godot_cpp/core/gdvirtual.gen.inc>
//#include <godot_cpp/classes/expression.hpp> // evaluate

using namespace godot;

namespace sly {

// forward declare classes
class Entity;
class System;
class Component;

//MAKE_TYPED_ARRAY(Ref<System>, Variant::OBJECT)
//MAKE_TYPED_ARRAY_INFO(Ref<System>, Variant::OBJECT)

/**
 * Ecs runs as a singleton and calls update on each system in physics process.
 */
class Ecs : public Node {
	GDCLASS(Ecs, Node)

public:
	static map<Object*> object_map;
	static map<Entity*> entity_map;
	static map<Component*> component_map;
	static map<System*> system_map;
	//static map<StringName> tag_map;

	static Ecs* singleton;

	TypedArray<System> systems;

protected:
	static void _bind_methods();

	void _notification(int p_what);

public:
	Ecs() = default;
	~Ecs() override = default;

	// setters and getters
	static Ecs* get_singleton(); // static method to get the singleton instance
	
	// alternate way to connect from _ready in gdscript by calling Ecs.connect(get_tree()) instead of using autoload scene
	void connect(SceneTree* scene_tree);

	void process_ecs();

	//void register_entity(Object* object, const TypedArray<Component>& components = TypedArray<Component>()); // todo: add
	//void register_entity(Object* object, const TypedArray<Component>& components = TypedArray<Component>());

	void register_object(Object* object);
	void unregister_object(Object* object);
/*
	void register_entity(Entity* entity);
	void unregister_entity(Entity* entity);

	void register_system(System* system);
	void unregister_system(System* system);

	void register_component(Component* component);
	void unregister_component(Component* component);
*/
	void set_systems(const TypedArray<System>& p_systems) { systems = p_systems; }
	TypedArray<System> get_systems() const { return systems; };

/*
	void set_systems(const TypedArray<Ref<System>>& p_systems) { systems = p_systems; }
	TypedArray<Ref<System>> get_systems() const { return systems; };
*/
};



//class Tags;

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


//todo:remove
/*
class Resource : public Resource {
GDCLASS(Resource, Resource);

	//int id;

protected:
	static void _bind_methods();
	
public:
	Resource() = default;
	~Resource() override = default;
	
	//Resource(int p_id) : id(p_id) {}

	//StringName name_var;

	// getters and setters
	//const StringName& get_name_var() const { return name_var; };
    //void set_name_var(const StringName& p_name_var) { name_var = p_name_var; };

	// to enable hashing in unordered map
	bool operator==(const Resource& other) const {
		return this == &other;
    }

	// setters and getters
	//void set_id(int p_id) { id = p_id; }
	//int get_id() const { return id; };
};
*/
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

/*
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
*/

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








/*
class EntityParams {
public:
};
*/


class Entity : public Resource {
GDCLASS(Entity, Resource);

	//int id;

	TypedArray<Component> components;
	TypedArray<StringName> tags;
	/*
	//todo:these should all be ids really.. not nodes and components, but components are easier in editor picker..
	TypedArray<Node> nodes;	// actual godot nodes of this entity
	*/

protected:
	static void _bind_methods();

public:
	Entity();
	~Entity() override = default;

	//Entity(int p_id) : id(p_id) {}

	void set_components(const TypedArray<Component>& p_components) { components = p_components; }
	TypedArray<Component> get_components() const { return components; };

	void set_tags(TypedArray<StringName> p_tags_required) { tags = p_tags_required; }
    TypedArray<StringName> get_tags() const { return tags; }

/*
	// to enable hashing in unordered map
	bool operator==(const Entity& other) const {
        return id == other.id;
    }
*/
	//Entity(Object* p_object) : object(p_object) {}
	//Object* object; // actual godot game object

	// todo: these should be in EntitySpec or something like this on a per type basis to set the default values
/*	
	// setters and getters
	void set_id(int p_id) { id = p_id; }
	int get_id() const { return id; };
*/
	/*
	void set_nodes(const TypedArray<Node>& p_nodes) { nodes = p_nodes; }
	TypedArray<Node> get_nodes() const { return nodes; };
	*/
};












//todo: this should be Entity
class NodeECS : public Node {
GDCLASS(NodeECS, Node);

	//int id;

	/*
	TypedArray<Component> components;
	*/

	//Ref<Entity> entity;
	//Entity entity;

	TypedArray<Entity> entities;
	TypedArray<Component> components;
	TypedArray<StringName> tags;
	
protected:
	static void _bind_methods();

	void _notification(int p_what);

public:
	NodeECS() = default;
	~NodeECS() override = default;
	/*
	//Entity(const Entity& other) = default; // default copy constructor (should be generated implicitly by the compiler)
	NodeECS(int p_id) : id(p_id) {}
	*/
	// to enable hashing in unordered map
	bool operator==(const NodeECS& other) const {
		return this == &other;
        //return id == other.id;
    }

	//Entity(Object* p_object) : object(p_object) {}
	//Object* object; // actual godot game object
/*	
	// setters and getters
	void set_id(int p_id) { id = p_id; }
	int get_id() const { return id; };
*/
/*
	void set_entity(const Ref<Entity>& p_entity) { entity = p_entity; }
	Ref<Entity> get_entity() const { return entity; };
*/


	/*
	void set_entity(const Entity& p_entity) { entity = p_entity; }
	Entity get_entity() const { return entity; };
	*/

	/*
	void set_components(const TypedArray<Component>& p_components) { components = p_components; }
	TypedArray<Component> get_components() const { return components; };
	*/

	// setters and getters
	void set_entities(const TypedArray<Entity>& p_entities) { entities = p_entities; }
	TypedArray<Entity> get_entities() const { return entities; };

	void set_components(const TypedArray<Component>& p_components) { components = p_components; }
	TypedArray<Component> get_components() const { return components; };

	void set_tags(TypedArray<StringName> p_tags_required) { tags = p_tags_required; }
    TypedArray<StringName> get_tags() const { return tags; }
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

/*
class Tags : public Resource {
GDCLASS(Tags, Resource); 

	TypedArray<StringName> tags;

protected:
	static void _bind_methods() {};

public:
	Tags() = default;
	~Tags() override = default;

	void set_tags(const TypedArray<StringName>& p_tags) { tags = p_tags; }
	TypedArray<StringName> get_tags() const { return tags; };
};
*/

/*
union Union_Array {
	array<Variant> array_var;	// array which holds <value> all the variants in the same index as the object is stored in object_list
	array<bool> array_bool;
	array<int> array_int;
	array<float> array_float;
};
*/

//template <typename T>
class Component : public Resource{
GDCLASS(Component, Resource);

protected:
	static void _bind_methods();

public:
	Component();
	~Component() override = default;
	//Component(Variant p_data_var) { data_var = p_data_var; }

	//Union_Array union_array;

	// Variant Array is usually a variant unless using a simple type like int etc. in which case it uses the faster types, this packs the data closer as a Variant is always 20 bytes.
    using Variant_Array = std::variant<array<Variant>, array<bool>, array<int>, array<float>, array<String>, array<StringName>>;

	Variant_Array data_array;

	Variant data_var;	// default value

	void set_data_var(const Variant& p_data_var);
	// sets value from variant (does conversion from_var())
	const Variant& get_data_var() const { return data_var; }; // get value (does conversion to_var())

	template <typename T>
	array<T>& get_data() {
		return std::get<array<T>>(data_array);
	}


/*
	void set_data_var(const Array& p_data_var) { data_var = p_data_var; }; // sets value from variant (does conversion from_var())
	const Array& get_data_var() const { return data_var; }; // get value (does conversion to_var())
*/

	/*
	void set_data_var(const TypedArray<Variant>& p_data_var) { data_var = p_data_var; }; // sets value from variant (does conversion from_var())
	const TypedArray<Variant>& get_data_var() const { return data_var; }; // get value (does conversion to_var())
	*/

	/*
    void set_data_var(TypedArray<Variant> p_array) {
        data_var = p_array;
    }

    TypedArray<Variant> get_data_var() const {
        return data_var;
    }*/

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

/*
	//TypedArray<Variant> create_typed_array_from_variant(const Variant& p_variant, Array& new_array);
	Array create_array_from_variant(const Variant& p_variant);
*/
};


/*
class SystemUpdater : public Object {
GDCLASS(SystemUpdater, Object);


	static const TypedArray<Callable>& callables;
	
protected:
	static void _bind_methods() {};

public:
	//static TypedArray<Callable> callables;

	static void system_movement() {};
	//static system_damage();
	//static system_render();
	//static system_combat();
};
*/

class System : public Resource {
GDCLASS(System, Resource);

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
	TypedArray<Component> components_required;
	TypedArray<Component> components_forbidden;
	TypedArray<Component> components_remove;
	TypedArray<Component> components_add;

	TypedArray<StringName> tags_required;
	TypedArray<StringName> tags_forbidden;
	TypedArray<StringName> tags_add;
	TypedArray<StringName> tags_remove;

	/*
	float duration;
	effect_type : on_off; / periodic
	*/

protected:
	static void _bind_methods();

	/*
	// load callable functions into Ecs
	void load_callable();
	void load_callable_script();
	*/

	static const void get_affected_entities(TypedArray<int>& entities) {};

public:
	System();
	~System() override = default;
/*
	Callable system_callable; // callable called by update()

	static bool run_query(String query) { return false; } // returns true if query was successful }; // bulk queries to update components e.g., to multiply all values by scalaras and same index values in other components by using queries like (movement_component = velocity_component * position_component * direction_component * delta)
*/
	//TypedArray<int> effects;

	//array<int> components_required;

	// setters and getters
	void set_components_required(const TypedArray<Component>& p_components_required) { components_required = p_components_required; }
	TypedArray<Component> get_components_required() const { return components_required; };

	void set_components_forbidden(const TypedArray<Component>& p_components_forbidden) { components_forbidden = p_components_forbidden; }
	TypedArray<Component> get_components_forbidden() const { return components_forbidden; };

	void set_components_add(const TypedArray<Component>& p_components_add) { components_add = p_components_add; }
	TypedArray<Component> get_components_add() const { return components_add; };

	void set_components_remove(const TypedArray<Component>& p_components_remove) { components_remove = p_components_remove; }
	TypedArray<Component> get_components_remove() const { return components_remove; };

	void set_tags_required(TypedArray<StringName> p_tags_required) { tags_required = p_tags_required; }
    TypedArray<StringName> get_tags_required() const { return tags_required; }

	void set_tags_forbidden(TypedArray<StringName> p_tags_forbidden) { tags_forbidden = p_tags_forbidden; }
    TypedArray<StringName> get_tags_forbidden() const { return tags_forbidden; }

	void set_tags_add(TypedArray<StringName> p_tags_add) { tags_add = p_tags_add; }
    TypedArray<StringName> get_tags_add() const { return tags_add; }

	void set_tags_remove(TypedArray<StringName> p_tags_remove) { tags_remove = p_tags_remove; }
    TypedArray<StringName> get_tags_remove() const { return tags_remove; }

	virtual void update();
	GDVIRTUAL0(_update);
};





} // namespace sly


/**
 * Hash function for reverse lookup hash table, used by sly::map so it can store pointers to any Resource objects i.e. Entity, Component, System resources
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
	struct hash<sly::Resource> {
		size_t operator()(const sly::Resource* ptr) const {
			// Hash the id member of the object pointed to by ptr
			return hash<int>()(ptr->get_id()); 
		}
	};
	
} // namespac
 e std
*/

