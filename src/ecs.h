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
//#include <godot_cpp/variant/ref.hpp>
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
class Ability;
//class Entity;
class Effect;
class Attribute;
//class Archetype;

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

	TypedArray<Ability> abilities;	// all abilities added to the Ecs

	// registers containing all existing items not just enabled ones
	//map<Ability*> ability_register; //todo:remove
	//map<Entity*> entity_register; //todo:replace with static

	map<int64_t> entity_register; // instance ids of all entities

	//Dictionary tag_entity_register; // dictionary of tags and entities they're assigned to <StringName tag, array<int64_t> entity_id>

	std::unordered_map<int64_t, map<int64_t>> tag_register; // unordered map of tags and entities they're assigned to <StringName tag, array<int64_t> entity_id>

protected:
	static void _bind_methods();

	void _notification(int p_what);

public:
	Ecs() = default;
	~Ecs() override = default;

	map<Attribute*> attribute_register;			// all attributes listed in an ability are added here when Ability is initialized
	map<StringName> attribute_name_register;	// names of attributes are on the same index as the attribute in attribute_register, this allows for retrieval of attributes by name

/*
	int testint = 0; //todo:remove
	void increment_testint(StringName name) { 
		testint++; 
		print("testint val : ", testint, " from : ", name);
	}
*/

	// setters and getters
	static Ecs* get_singleton(); // static method to get the singleton instance

	// alternate way to connect from _ready in gdscript by calling Ecs.connect(get_tree()) instead of using autoload scene
	void connect(SceneTree* scene_tree);

	void process_ecs();
/*
	// create an Entity for a godot game object
	Entity* create_entity(Object* object);
	void remove_entity(Entity* entity);
*/
	// create an Entity for a godot game object
	int create_entity(Object* object);
	void remove_entity(Object* object);

	void tag_add(Object *object, StringName tag);
	void tag_remove(Object *object, StringName tag);

	void set_abilities(const TypedArray<Ability>& p_abilities) { abilities = p_abilities; }
	TypedArray<Ability> get_abilities() const { return abilities; };

	//void create_entity(Object* object);

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

	//friend Ability::Ability();
	//friend Entity::Entity();
	friend Ability;
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

#if 0
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
#endif











//todo: this should be Archetype
class NodeECS : public Node {
GDCLASS(NodeECS, Node);

	//int id;

	/*
	TypedArray<Attribute> attributes;
	*/

	//Ref<Archetype> archetype;
	//Archetype archetype;

	//Entity* entity;

	int64_t entity_id;

	TypedArray<Ability> abilities;
	//TypedArray<Archetype> archetypes; //todo: remove or replace with system archetypes
	//TypedArray<Attribute> attributes; //todo:remove?
	TypedArray<StringName> tags;
	
protected:
	static void _bind_methods();

	void _notification(int p_what);

public:
	NodeECS() = default;
	//~NodeECS() override = default;
	/*
	//Archetype(const Archetype& other) = default; // default copy constructor (should be generated implicitly by the compiler)
	NodeECS(int p_id) : id(p_id) {}
	*/
	/*
	// to enable hashing in unordered map
	bool operator==(const NodeECS& other) const {
		return this == &other;
        //return id == other.id;
    }*/

	

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
	void set_abilities(TypedArray<Ability> p_abilities_required) { abilities = p_abilities_required; }
    TypedArray<Ability> get_abilities() const { return abilities; }
/*
	void set_archetypes(const TypedArray<Archetype>& p_archetypes) { archetypes = p_archetypes; }
	TypedArray<Archetype> get_archetypes() const { return archetypes; };

	void set_attributes(const TypedArray<Attribute>& p_attributes) { attributes = p_attributes; }
	TypedArray<Attribute> get_attributes() const { return attributes; };
*/
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

class AttributeData : public RefCounted {
GDCLASS(AttributeData, RefCounted);	

	// Variant Array is usually a variant unless using a simple type like int etc. in which case it uses the faster types, this packs the data closer for ints or floats etc. as a Variant is always 20 bytes.
    using Variant_Array = std::variant<array<Variant>, array<bool>, array<int>, array<float>, array<String>, array<StringName>>;
	Variant_Array data_array;
	std::unordered_map<int64_t, int> data_array_lookup; // entity_id, index of value in data_array

protected:
	static void _bind_methods(){};

public:
	AttributeData() = default;

	template <typename T>
	const array<T>& get_data() const {
		return std::get<array<T>>(data_array);
	}

	template <typename T>
	array<T>& get_data() {
		return std::get<array<T>>(data_array);
	}

/*
	template <typename T>
	T data_value(int index) {
		return std::get<array<T>>(data_array).at(index);	// using at instead of []
	}
*/
	// sets value from variant (does conversion from_var())
	void set_var(int entity_id, Variant& value) {
		switch(value.get_type()) {
			case Variant::BOOL:
				set_value<bool>(entity_id, value);
				break;
			case Variant::INT:
				set_value<int64_t>(entity_id, value);
				break;
			case Variant::FLOAT:
				set_value<float>(entity_id, value);
				break;
			case Variant::STRING:
				set_value<String>(entity_id, value);
				break;
			case Variant::STRING_NAME:
				set_value<StringName>(entity_id, value);
				break;
			default:
				set_value<Variant>(entity_id, value);
		}

	}

	// get value directly (no conversion)
	template <typename T>
	T get_value(int64_t entity_id) const {
		int index = data_array_lookup.at(entity_id);
		/*
		array<T> data = *get_data<T>();
		T value = data[index];
		*/
		T value = get_data<T>()[index];
		//T value = get_data<T>().at(index);
		return value; 
	}

	// get value for an entity and convert it to variant (maybe useful for gdscript)
	Variant get_var(int64_t entity_id, Variant::Type var_type) const { 
		Variant value;
		switch(var_type) {
			case Variant::BOOL:
				value = Variant(get_value<bool>(entity_id));
				break;
			case Variant::INT:
				value = Variant(get_value<int>(entity_id));
				break;
			case Variant::FLOAT:
				value = Variant(get_value<float>(entity_id));
				break;
			case Variant::STRING:
				value = Variant(get_value<String>(entity_id));
				break;
			case Variant::STRING_NAME:
				value = Variant(get_value<StringName>(entity_id));
				break;
		}		
		return value; 
	} // get value (does conversion to_var())

	// sets value directly (no conversion)
	template <typename T>
	void set_value(int64_t entity_id, T value) { 
		//todo: need to get index for this entity to update the value if it already exists, how to keep consistency with entity_register?!
		/*
		array<T> data = *get_data<T>();
		int new_index = data.insert(value);
		*/
		int new_index = get_data<T>().insert(value);
	 	data_array_lookup[entity_id] = new_index;
	}


	/*
	//todo:remove if to_var and from_var are unused.
	template <typename T>
	Variant to_var(T val) { return Variant(val); }; // convert actual type to variant for editor

	template <typename T>
	T from_var(Variant var) { return cast_to<T>(var); };	// convert variant from editor to actual type
	*/
};


//template <typename T>
class Attribute : public Resource { // Attribute
GDCLASS(Attribute, Resource);

	StringName attribute_name;
	AttributeData attribute_data;

protected:
	static void _bind_methods();

public:
	Attribute() = default;
	//~Attribute() override = default;
	//Attribute(Variant p_data_var) { data_var = p_data_var; }

	void create_attribute_data_entry(); //todo:use or remove

	//Union_Array union_array;

	Variant data_var;	// default value

	void set_data_var(const Variant& p_data_var); // sets value from variant (does conversion from_var())
	const Variant& get_data_var() const { return data_var; }; // get value (does conversion to_var())

	AttributeData* get_attribute_data() {
		return &attribute_data;
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

	void set_attribute_name(StringName p_attribute_name) { attribute_name = p_attribute_name; }
	StringName get_attribute_name() { return attribute_name; }


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

#if 0
class Entity : public RefCounted {
	GDCLASS(Entity, RefCounted);

	int64_t object_id;

	//map<Attribute*> attributes;
	map<Ability*> abilities;
	map<Effect*> effects;
	map<StringName> tags;

protected:
	static void _bind_methods();

public:
	Entity() = default;

	void add_ability(Ability* p_ability);
	void clear_ability(Ability* p_ability);

	void add_effect(Effect* p_effect);
	void clear_effect(Effect* p_effect);

	void add_tag(StringName p_tag);
	void clear_tag(StringName p_tag);

	//todo: this should take stringname "attribute_name" instead of attribute?
	template <typename T>
	void set_attribute(Attribute* p_attribute, T value);

	template <typename T>
	T get_attribute(Attribute* p_attribute);

/*
	void grant_abilities(TypedArray<Ability>& p_abilities);
	void clear_abilities(TypedArray<Ability>& p_abilities);
*/
	void set_object(Object* object);	// set game object id from instance id
	Object* get_object();	// get game object id from instance id

	/*
	bool operator==(const godot::Ref<Entity>& lhs, const godot::Ref<Entity>& rhs) {
		return lhs.ptr() == rhs.ptr(); // Compare the underlying pointers
	}*/

	/*
	// to enable hashing in unordered map
	bool operator==(const Ref<Entity>& other) const {
		return this == other.ptr();
        //return id == other.id;
    }*/

};
#endif


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

	StringName ability_name;

	map<int64_t> entities_assigned;

	TypedArray<Attribute> attributes_required;
	TypedArray<Attribute> attributes_forbidden; //todo:remove? maybe useful
	/*
	TypedArray<Attribute> attributes_remove;
	TypedArray<Attribute> attributes_add;
	*/

	TypedArray<StringName> tags_required;
	TypedArray<StringName> tags_forbidden;

	/*
	float duration;
	effect_type : on_off; / periodic
	*/

	array<int64_t> entities_affected;

protected:
	static void _bind_methods();

	//void _notification(int p_what);

	/*
	// load callable functions into Ecs
	void load_callable();
	void load_callable_script();
	*/

	static const void get_affected_archetypes(TypedArray<int>& archetypes) {};

	/*
	void _notification(int p_what);
	*/


	
public:
	Ability();
	//~Ability() override;
	
	//static map<Ability*> abilities;	// ability registry

	map<int64_t> entities_approved;	// recalculated for each update(), filtered entities after checking tags, update operations only run for these

	void set_attribute_val(StringName attribute_name, Variant value);

	void initialize(); // called by Ecs class so that Ability can post attributes to attribute_register

	//~Ability() override = default;
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

	void set_tags_required(TypedArray<StringName> p_tags_required) { tags_required = p_tags_required; }
    TypedArray<StringName> get_tags_required() const { return tags_required; }

	void set_tags_forbidden(TypedArray<StringName> p_tags_forbidden) { tags_forbidden = p_tags_forbidden; }
    TypedArray<StringName> get_tags_forbidden() const { return tags_forbidden; }

	void set_ability_name(StringName p_ability_name) { ability_name = p_ability_name; }
	StringName get_ability_name() { return ability_name; }

	void set_is_enabled(bool p_is_enabled);
	bool get_is_enabled();

	// to enable hashing in unordered map
	bool operator==(const Ability& other) const {
		return this == &other;
    }

	// updated list of entities which qualify to run update() based on if entity has required and forbidden tags
	void update_entities_approved();

	virtual void update();
	GDVIRTUAL0(_update);
};



class Effect : public Resource {	// Ability
GDCLASS(Effect, Resource);

	TypedArray<String> commands;
	TypedArray<StringName> tags_add;
	TypedArray<StringName> tags_remove;
	float duration;
	float cooldown;

	int64_t target_entity_id;

protected:
	static void _bind_methods();
public:
	Effect() = default;
/*
	void attach_effect(Entity* target_entity);
	void detach_effect(Entity* target_entity);
*/
	void set_commands(TypedArray<String> p_commands) { commands = p_commands; }
    TypedArray<String> get_commands() const { return commands; }

	void set_tags_add(TypedArray<StringName> p_tags_add) { tags_add = p_tags_add; }
    TypedArray<StringName> get_tags_add() const { return tags_add; }

	void set_tags_remove(TypedArray<StringName> p_tags_remove) { tags_remove = p_tags_remove; }
    TypedArray<StringName> get_tags_remove() const { return tags_remove; }

	void set_duration(float p_duration) { duration = p_duration; }
	float get_duration() const { return duration; }

	void set_cooldown(float p_cooldown) { cooldown = p_cooldown; }
	float get_cooldown() const { return cooldown; }
};



} // namespace sly


/**
 * Hash function for reverse lookup hash table, used by sly::map so it can store pointers to any Resource objects i.e. Archetype, Attribute, Ability resources
 */
 //namespace std {
/*
    template <>
    struct hash<godot::Ref<RefCounted>> {
        std::size_t operator()(const godot::Ref<RefCounted>& k) const noexcept {
            // Hash the underlying raw pointer
            return std::hash<RefCounted*>{}(k.ptr());
        }
    };
*/
/*
	template <typename T>
	struct hash<godot::Ref<T>> {
		// Check if the Ref is valid before trying to get its instance ID
		if (p_ref.is_valid()) {
			return std::hash<uint64_t>()(p_ref->get_instance_id());
		}
		// Return a consistent hash for invalid/null Ref<T>
		return 0; 
	};
*/
/*
    template <>
	struct hash<godot::Ref<sly::Ability>> {
        std::size_t operator()(const godot::Ref<sly::Ability>& k) const noexcept {
            // Hash the underlying raw pointer
            return std::hash<sly::Ability*>{}(k.ptr());
        }
    };

    template <>
	struct hash<godot::Ref<sly::Entity>> {
        std::size_t operator()(const godot::Ref<sly::Entity>& k) const noexcept {
            // Hash the underlying raw pointer
            return std::hash<sly::Entity*>{}(k.ptr());
        }
    };
*/
	/*
    template <template T>
	struct hash<godot::Ref<T>> {
        std::size_t operator()(const godot::Ref<T>& k) const noexcept {
            // Hash the underlying raw pointer
            return std::hash<MyObject*>{}(k.ptr());
        }
    };*/

	/*
    template <>
    struct hash<godot::Ref<MyObject>> {
        std::size_t operator()(const godot::Ref<MyObject>& k) const noexcept {
            // Hash the underlying raw pointer
            return std::hash<MyObject*>{}(k.ptr());
        }
    };*/

	/*
	template <typename T>
	struct hash<godot::Ref<T>> {
		size_t operator()(const godot::Ref<T>& ref) const {
        // Hash the underlying pointer
        return std::hash<T*>{}(ref.ptr()); 
		}
	};*/




/*
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
*/	
//} // namespace std


