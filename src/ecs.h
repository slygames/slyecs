#pragma once

#include <godot_cpp/classes/wrapped.hpp>
//#include "godot_cpp/variant/variant.hpp"
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/resource.hpp>
//#include <godot_cpp/classes/array.hpp> // Includes the definition for TypedArray
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/classes/resource_loader.hpp> // for load_ability_script
#include <godot_cpp/classes/script.hpp> // for load_ability_script
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/typed_array.hpp>
//#include "godot_cpp/classes/ref_counted.hpp"
//#include <godot_cpp/classes/weak_ref.hpp>
#include <functional> // for std::hash
//#include <cstdint>
#include "slymap.h"
#include "util.h"
#include <variant> // for std::variant
//#include <godot_cpp/variant/utility_functions.hpp> // for instance_from_id
#include <godot_cpp/variant/dictionary.hpp>
#include <godot_cpp/classes/scene_tree.hpp> // for Ecs::connect()
#include <godot_cpp/classes/window.hpp> // for Ecs::connect()
#include <godot_cpp/core/gdvirtual.gen.inc>
//#include <godot_cpp/classes/expression.hpp> // evaluate

using namespace godot;

namespace sly {

// forward declare classes
class Archetype;
class Ability;
class Attribute;

/**
 * Ecs runs as a singleton and calls update on each ability in physics process.
 */
class Ecs : public Node {
	GDCLASS(Ecs, Node)

	/*
	static map<Object*> object_map;
	static map<Archetype*> archetype_map;
	static map<Attribute*> attribute_map;
	//static map<StringName> tag_map;
	*/
	static Ecs* singleton;

	//TypedArray<Ability> abilities;

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

	// registers containing all existing items not just enabled ones
	map<Ref<Ability>> ability_register;
	map<Ref<Entity>> entity_register;

	// create an Entity for a godot game object
	void create_entity(Object* object);

	//void register_archetype(Object* object, const TypedArray<Attribute>& attributes = TypedArray<Attribute>()); // todo: add
	//void register_archetype(Object* object, const TypedArray<Attribute>& attributes = TypedArray<Attribute>());

	/*
	void register_object(Object* object);
	void unregister_object(Object* object);
	*/
/*
	void register_archetype(Archetype* archetype);
	void unregister_archetype(Archetype* archetype);

	void register_ability(Ability* ability);
	void unregister_ability(Ability* ability);

	void register_attribute(Attribute* attribute);
	void unregister_attribute(Attribute* attribute);
*/
	/*
	void set_abilities(const TypedArray<Ability>& p_abilities) { abilities = p_abilities; }
	TypedArray<Ability> get_abilities() const { return abilities; };
	*/

/*
	void set_abilities(const TypedArray<Ref<Ability>>& p_abilities) { abilities = p_abilities; }
	TypedArray<Ref<Ability>> get_abilities() const { return abilities; };
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

class AttributeSpec {
	map<Variant*> data_var;
};

class ArchetypeSpec {
	StringName name_var;

	// getters and setters
    const StringName& get_name_var() const { return name_var; };
    void set_name_var(const StringName& p_name_var) { name_var = p_name_var; };
};

class Abilitiespec {
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

	Ref<Archetype> archetype;

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

	void set_archetype(const Ref<Archetype>& p_archetype) { archetype = p_archetype; }
	Ref<Archetype> get_archetype() const { return archetype; };
};
*/


/*
// this should be Archetype and should be a RefCounted, not in editor.
class Actor : public NodeECS {
GDCLASS(Actor, NodeECS);

	//todo: this is unnecessary, should only store ints and those should be in a register in Ecs class or something. Archetype just needs it's own id.
	TypedArray<Attribute> attributes;

	Ref<Archetype> archetype;

protected:
	static void _bind_methods();

public:
	Actor() {};
	~Actor() override = default;
	
	//Archetype(Object* p_object) : object(p_object) {}
	//Object* object; // actual godot game object

	// todo: these should be in ArchetypeSpec or something like this on a per type basis to set the default values
	
	// setters and getters
	//void set_attributes(const TypedArray<Attribute>& p_attributes) { attributes = p_attributes; }
	//TypedArray<Attribute> get_attributes() const { return attributes; };


	void set_archetype(const Ref<Archetype>& p_archetype) { archetype = p_archetype; }
	Ref<Archetype> get_archetype() const { return archetype; };
};
*/








/*
class ArchetypeParams {
public:
};
*/


class Archetype : public Resource {	// Archetype
GDCLASS(Archetype, Resource);


	TypedArray<Attribute> attributes;
	TypedArray<Archetype> parents;

/*
	Dictionary attributes; // <StringName, Attribute>
*/

	//int id;
	//TypedArray<StringName> tags;
	/*
	//todo:these should all be ids really.. not nodes and attributes, but attributes are easier in editor picker..
	TypedArray<Node> nodes;	// actual godot nodes of this 
	*/

protected:
	static void _bind_methods();

public:
	Archetype();
	~Archetype() override = default;

	//Archetype(int p_id) : id(p_id) {}

	void set_attributes(const TypedArray<Attribute>& p_attributes) { attributes = p_attributes; }
	TypedArray<Attribute> get_attributes() const { return attributes; }; //todo: maybe return Dictionary&
/*
	void set_parents(const TypedArray<Archetype>& p_parents) { parents = p_parents; }
	TypedArray<Archetype> get_parents() const { return parents; };
*/
	/*
	void set_attributes(const Dictionary& p_attributes) { attributes = p_attributes; }
	Dictionary get_attributes() const { return attributes; }; //todo: maybe return Dictionary&
	*/
/*
	void set_tags(TypedArray<StringName> p_tags_required) { tags = p_tags_required; }
    TypedArray<StringName> get_tags() const { return tags; }
*/
/*
	// to enable hashing in unordered map
	bool operator==(const Archetype& other) const {
        return id == other.id;
    }
*/
	//Archetype(Object* p_object) : object(p_object) {}
	//Object* object; // actual godot game object

	// todo: these should be in ArchetypeSpec or something like this on a per type basis to set the default values
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












//todo: this should be Archetype
class NodeECS : public Node {
GDCLASS(NodeECS, Node);

	//int id;

	/*
	TypedArray<Attribute> attributes;
	*/

	//Ref<Archetype> archetype;
	//Archetype archetype;

	TypedArray<Archetype> archetypes;
	TypedArray<Attribute> attributes;
	TypedArray<StringName> tags;
	
protected:
	static void _bind_methods();

	void _notification(int p_what);

public:
	NodeECS() = default;
	~NodeECS() override = default;
	/*
	//Archetype(const Archetype& other) = default; // default copy constructor (should be generated implicitly by the compiler)
	NodeECS(int p_id) : id(p_id) {}
	*/
	// to enable hashing in unordered map
	bool operator==(const NodeECS& other) const {
		return this == &other;
        //return id == other.id;
    }

	//Archetype(Object* p_object) : object(p_object) {}
	//Object* object; // actual godot game object
/*	
	// setters and getters
	void set_id(int p_id) { id = p_id; }
	int get_id() const { return id; };
*/
/*
	void set_archetype(const Ref<Archetype>& p_archetype) { archetype = p_archetype; }
	Ref<Archetype> get_archetype() const { return archetype; };
*/


	/*
	void set_archetype(const Archetype& p_archetype) { archetype = p_archetype; }
	Archetype get_archetype() const { return archetype; };
	*/

	/*
	void set_attributes(const TypedArray<Attribute>& p_attributes) { attributes = p_attributes; }
	TypedArray<Attribute> get_attributes() const { return attributes; };
	*/

	// setters and getters
	void set_archetypes(const TypedArray<Archetype>& p_archetypes) { archetypes = p_archetypes; }
	TypedArray<Archetype> get_archetypes() const { return archetypes; };

	void set_attributes(const TypedArray<Attribute>& p_attributes) { attributes = p_attributes; }
	TypedArray<Attribute> get_attributes() const { return attributes; };

	void set_tags(TypedArray<StringName> p_tags_required) { tags = p_tags_required; }
    TypedArray<StringName> get_tags() const { return tags; }
};

/*
class Tags : public Object {
GDCLASS(Tags, Object);

	static const TypedArray<Callable>& callables;
	static const TypedArray<int>& get_affected_archetypes();
	
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
class Attribute : public Resource { // Attribute
GDCLASS(Attribute, Resource);

protected:
	static void _bind_methods();

public:
	Attribute();
	~Attribute() override = default;
	//Attribute(Variant p_data_var) { data_var = p_data_var; }

	void create_attribute_data_entry();

	//Union_Array union_array;

	// Variant Array is usually a variant unless using a simple type like int etc. in which case it uses the faster types, this packs the data closer for ints or floats etc. as a Variant is always 20 bytes.
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

	void set_var(int archetype_id, Variant& value) {}; // sets value from variant (does conversion from_var())
	const Variant get_var(int archetype_id) const { return 0; }; // get value (does conversion to_var())

	template <typename T>
	Variant to_var(T val) { return Variant(val); }; // convert actual type to variant for editor

	template <typename T>
	T from_var(Variant var) { return cast_to<T>(var); };	// convert variant from editor to actual type

	template <typename T>
	const T get_value(int archetype_id) { return T(); }; // get value directly (no conversion)

	template <typename T>
	void set_value(int archetype_id, T& value) {}; // sets value directly (no conversion)

	//todo:overload * operator and maybe = operator in sly::map so that two attributes can be multiplied together which will be useful to multiply all values by scalaras and same index values in other attributes by using queries like (movement_attribute = velocity_attribute * position_attribute * direction_attribute * delta)

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
class AbilityUpdater : public Object {
GDCLASS(AbilityUpdater, Object);


	static const TypedArray<Callable>& callables;
	
protected:
	static void _bind_methods() {};

public:
	//static TypedArray<Callable> callables;

	static void ability_movement() {};
	//static ability_damage();
	//static ability_render();
	//static ability_combat();
};
*/

class Entity : public RefCounted {
	GDCLASS(Entity, RefCounted);

	int64_t object_id;

protected:
	static void _bind_methods() {};

public:
	Entity() = default;

	void set_object(Ref<RefCounted> object);	// set game object id from instance id
	Ref<RefCounted> get_object();	// get game object id from instance id

};


class Ability : public Resource {	// Ability
GDCLASS(Ability, Resource);

/*
//todo: enums should be attributes so this value can be read from the attribute instead, then ability_combat can handle all these states, and have a gdscript equivalent in abilities.gd
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
	bool is_enabled;

	map<Ref<Entity>> entities_assigned;

	TypedArray<Attribute> attributes_required;
	TypedArray<Attribute> attributes_forbidden;
	TypedArray<Attribute> attributes_remove;
	TypedArray<Attribute> attributes_add;

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

	static const void get_affected_archetypes(TypedArray<int>& archetypes) {};

public:
	Ability();
	~Ability() override = default;
/*
	Callable ability_callable; // callable called by update()

	static bool run_query(String query) { return false; } // returns true if query was successful }; // bulk queries to update attributes e.g., to multiply all values by scalaras and same index values in other attributes by using queries like (movement_attribute = velocity_attribute * position_attribute * direction_attribute * delta)
*/
	//TypedArray<int> effects;

	//array<int> attributes_required;

	// setters and getters
	void set_attributes_required(const TypedArray<Attribute>& p_attributes_required) { attributes_required = p_attributes_required; }
	TypedArray<Attribute> get_attributes_required() const { return attributes_required; };

	void set_attributes_forbidden(const TypedArray<Attribute>& p_attributes_forbidden) { attributes_forbidden = p_attributes_forbidden; }
	TypedArray<Attribute> get_attributes_forbidden() const { return attributes_forbidden; };

	void set_attributes_add(const TypedArray<Attribute>& p_attributes_add) { attributes_add = p_attributes_add; }
	TypedArray<Attribute> get_attributes_add() const { return attributes_add; };

	void set_attributes_remove(const TypedArray<Attribute>& p_attributes_remove) { attributes_remove = p_attributes_remove; }
	TypedArray<Attribute> get_attributes_remove() const { return attributes_remove; };

	void set_tags_required(TypedArray<StringName> p_tags_required) { tags_required = p_tags_required; }
    TypedArray<StringName> get_tags_required() const { return tags_required; }

	void set_tags_forbidden(TypedArray<StringName> p_tags_forbidden) { tags_forbidden = p_tags_forbidden; }
    TypedArray<StringName> get_tags_forbidden() const { return tags_forbidden; }

	void set_tags_add(TypedArray<StringName> p_tags_add) { tags_add = p_tags_add; }
    TypedArray<StringName> get_tags_add() const { return tags_add; }

	void set_tags_remove(TypedArray<StringName> p_tags_remove) { tags_remove = p_tags_remove; }
    TypedArray<StringName> get_tags_remove() const { return tags_remove; }

	void set_is_enabled(bool p_is_enabled);
	bool get_is_enabled();

	virtual void update();
	GDVIRTUAL0(_update);
};





} // namespace sly


/**
 * Hash function for reverse lookup hash table, used by sly::map so it can store pointers to any Resource objects i.e. Archetype, Attribute, Ability resources
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

