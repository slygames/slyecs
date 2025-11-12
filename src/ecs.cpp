#include "ecs.h"
#include <godot_cpp/core/class_db.hpp>

namespace sly {

map<Object*> Ecs::object_map;
map<Archetype*> Ecs::archetype_map;
map<Attribute*> Ecs::attribute_map;
map<Ability*> Ecs::ability_map;
//map<StringName> Ecs::tag_map;

// initialize static variables
Ecs* Ecs::singleton = nullptr;

void Ecs::_bind_methods() {
	//ClassDB::bind_static_method("Ecs", D_METHOD("get_singleton"), &Ecs::get_singleton);
	ClassDB::bind_method(D_METHOD("connect", "scene_tree"), &Ecs::connect);
	//todo:add
	//ClassDB::bind_method(D_METHOD("create_archetype", "object", "attributes"), &Ecs::register_archetype, DEFVAL(TypedArray<Attribute>()));
	ClassDB::bind_method(D_METHOD("create_archetype", "archetype"), &Ecs::register_object);
	ClassDB::bind_method(D_METHOD("remove_archetype", "archetype"), &Ecs::unregister_object);


	ClassDB::bind_method(D_METHOD("set_abilities", "p_abilities"), &Ecs::set_abilities);
	ClassDB::bind_method(D_METHOD("get_abilities"), &Ecs::get_abilities);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "abilities", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Ability"), "set_abilities", "get_abilities");
	//ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "abilities", PROPERTY_HINT_ARRAY_TYPE, "Ability"), "set_abilities", "get_abilities");

}

void NodeECS::_bind_methods() {
/*
	ClassDB::bind_method(D_METHOD("set_archetype", "p_archetype"), &NodeECS::set_archetype);
	ClassDB::bind_method(D_METHOD("get_archetype"), &NodeECS::get_archetype);
	ADD_PROPERTY(PropertyInfo(godot::Variant::OBJECT, "archetype", godot::PROPERTY_HINT_RESOURCE_TYPE, "Archetype"), "set_archetype", "get_archetype");
*/

	ClassDB::bind_method(D_METHOD("set_attributes", "p_attributes"), &NodeECS::set_attributes);
	ClassDB::bind_method(D_METHOD("get_attributes"), &NodeECS::get_attributes);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "attributes", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Attribute"), "set_attributes", "get_attributes");

	ClassDB::bind_method(D_METHOD("set_archetypes", "p_archetypes"), &NodeECS::set_archetypes);
	ClassDB::bind_method(D_METHOD("get_archetypes"), &NodeECS::get_archetypes);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "archetypes", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Archetype"), "set_archetypes", "get_archetypes");
/*
	ClassDB::bind_method(D_METHOD("set_attributes", "p_attributes"), &NodeEcs::set_attributes);
	ClassDB::bind_method(D_METHOD("get_attributes"), &NodeEcs::get_attributes);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "attributes", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Attribute"), "set_attributes", "get_attributes");
*/

/*
	ClassDB::bind_method(D_METHOD("set_attributes", "p_attributes"), &NodeECS::set_attributes);
	ClassDB::bind_method(D_METHOD("get_attributes"), &NodeECS::get_attributes);
	ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "attributes", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + "StringName,Attribute"), "set_attributes", "get_attributes");
*/

	ClassDB::bind_method(D_METHOD("set_tags", "tags"), &NodeECS::set_tags);
	ClassDB::bind_method(D_METHOD("get_tags"), &NodeECS::get_tags);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "tags", PROPERTY_HINT_ARRAY_TYPE, "StringName"), "set_tags", "get_tags" );
}

void NodeECS::_notification(int p_what) {
	switch(p_what) {
		case NOTIFICATION_READY:
			// register parent of NodeEcs as the game object
			Ecs::get_singleton()->register_object(this->get_parent());
//todo:enable
/*			
			// get unique set of all attributes from archetypes
			std::set<Attribute*> object_attributes;
			for(int i=0;i<archetypes.size();i++) {
				Archetype* archetype = cast_to<Archetype>(archetypes[i]);
				TypedArray<Attribute> archetype_attributes = archetype->get_attributes();
				for(int j=0;j<archetype_attributes.size();j++) {
					Attribute* attribute = cast_to<Attribute>(archetype_attributes[j]);
					object_attributes.insert(attribute);
				}
			}
			// also get attributes arrays specified in the NodeEcs
			for(int i=0;i<attributes.size();i++) {
				Attribute* attribute = cast_to<Attribute>(attributes[i]);
				object_attributes.insert(attribute);
			}
*/
			/*
			for(int i=0;i<object_attributes.size();i++) {
				object_attributes.data_var
			}*/

			//todo: need to create all the data rows for the attributes for this object and also associate the tags with the object.

			break;
	}
}

void Archetype::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_attributes", "p_attributes"), &Archetype::set_attributes);
	ClassDB::bind_method(D_METHOD("get_attributes"), &Archetype::get_attributes);
	//ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "attributes", PROPERTY_HINT_DICTIONARY_TYPE, "Variant::STRING_NAME, Attribute"), "set_attributes", "get_attributes");
	
	
	ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "attributes", PROPERTY_HINT_TYPE_STRING, String::num(Variant::STRING_NAME) + ":;" + String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":" + "Attribute", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_SCRIPT_VARIABLE), "set_attributes", "get_attributes");

	
/*
	ClassDB::bind_method(D_METHOD("set_tags", "tags"), &Archetype::set_tags);
	ClassDB::bind_method(D_METHOD("get_tags"), &Archetype::get_tags);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "tags", PROPERTY_HINT_ARRAY_TYPE, "StringName"), "set_tags", "get_tags" );
*/

	/*
	ClassDB::bind_method(D_METHOD("set_nodes", "p_nodes"), &Archetype::set_nodes);
	ClassDB::bind_method(D_METHOD("get_nodes"), &Archetype::get_nodes);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "nodes", PROPERTY_HINT_NODE_TYPE, "Node"), "set_nodes", "get_nodes");
	*/

	//ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "attributes", PROPERTY_HINT_ARRAY_TYPE, "Variant::Attribute"), "set_attributes", "get_attributes" );
	
	//PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Image")
}

Archetype::Archetype() {
	print("CONSTRUCT archetype");
	Ecs::archetype_map.insert(this);
	print("archetype map size A: ", Ecs::attribute_map.size());
}

Attribute::Attribute() {
	print("CONSTRUCT attribute");
	Ecs::attribute_map.insert(this);
	print("comp map size A: ", Ecs::attribute_map.size());
}

void Attribute::set_data_var(const Variant &p_data_var) {
		data_var = p_data_var; 
		if(&p_data_var==nullptr) {
			return;
		}

		switch(data_var.get_type()) {
			case Variant::BOOL:
				data_array = sly::array<bool>();
				break;
			case Variant::INT:
				data_array = sly::array<int>();
				break;
			case Variant::FLOAT:
				data_array = sly::array<float>();
				break;
			case Variant::STRING:
				data_array = sly::array<String>();
				break;
			case Variant::STRING_NAME:
				data_array = sly::array<StringName>();
				break;
			//todo: add other cases for primitive types
			default:
				data_array = sly::array<Variant>();
		}
		emit_changed(); // for Resources to notify the editor/users of changes
}

/*
const Variant &Attribute::get_data_var() const {
	return data_var; // get value (does conversion to_var())
}*/

Ability::Ability() {
	print("CONSTRUCT Ability");
	Ecs::ability_map.insert(this);
	print("ability map size A: ", Ecs::ability_map.size());
}


void Attribute::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_data_var", "data_var"), &Attribute::set_data_var);
	ClassDB::bind_method(D_METHOD("get_data_var"), &Attribute::get_data_var);
	//ADD_PROPERTY(PropertyInfo(Variant::NIL, "data_var", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT), "set_data_var", "get_data_var");
	//ADD_PROPERTY(PropertyInfo(Variant::NIL, "data_var", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_NIL_IS_VARIANT ), "set_data_var", "get_data_var");
	ADD_PROPERTY(PropertyInfo(Variant::NIL, "gd_data_var", PROPERTY_HINT_NONE, "Variant", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_NIL_IS_VARIANT ), "set_data_var", "get_data_var");

	/*
	ClassDB::bind_method(D_METHOD("set_data_var", "p_data_var"), &Attribute::set_data_var);
	ClassDB::bind_method(D_METHOD("get_data_var"), &Attribute::get_data_var);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "data_var_array", PROPERTY_HINT_TYPE_STRING, String::num(Variant::NIL)+ "/" + String::num(PROPERTY_HINT_NONE) + ":Variant"), "set_data_var", "get_data_var");
	//ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "data_var", PROPERTY_HINT_NONE, "Variant", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_NIL_IS_VARIANT ), "set_data_var", "get_data_var");
	*/


	/*
	ClassDB::bind_method(D_METHOD("set_data_var", "p_data_var"), &Attribute::set_data_var);
	ClassDB::bind_method(D_METHOD("get_data_var"), &Attribute::get_data_var);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "my_variant_array", PROPERTY_HINT_TYPE_STRING, String::num(Variant::NIL)), "set_data_var", "get_data_var");
*/
	//ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "data_var", PROPERTY_HINT_ARRAY_TYPE, "Variant", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_NIL_IS_VARIANT ), "set_data_var", "get_data_var");
	
	//ADD_PROPERTY(PropertyInfo(Variant::NIL, "data_var"), "set_data_var", "get_data_var");
	//ADD_PROPERTY(PropertyInfo(Variant::NIL, "data_var", PROPERTY_HINT_TYPE_STRING, String::num(Variant::NIL) + "/" + String::num(PROPERTY_HINT_NONE) + ":Variant"), "set_data_var", "get_data_var");
}

void Ability::_bind_methods() {
	ClassDB::bind_method(D_METHOD("update"), &Ability::update);
	GDVIRTUAL_BIND(_update);

	ClassDB::bind_method(D_METHOD("set_attributes_required", "p_attributes_required"), &Ability::set_attributes_required);
	ClassDB::bind_method(D_METHOD("get_attributes_required"), &Ability::get_attributes_required);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "attributes_required", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Attribute"), "set_attributes_required", "get_attributes_required");

	ClassDB::bind_method(D_METHOD("set_attributes_forbidden", "p_attributes_forbidden"), &Ability::set_attributes_forbidden);
	ClassDB::bind_method(D_METHOD("get_attributes_forbidden"), &Ability::get_attributes_forbidden);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "attributes_forbidden", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Attribute"), "set_attributes_forbidden", "get_attributes_forbidden");

	ClassDB::bind_method(D_METHOD("set_attributes_add", "p_attributes_add"), &Ability::set_attributes_add);
	ClassDB::bind_method(D_METHOD("get_attributes_add"), &Ability::get_attributes_add);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "attributes_add", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Attribute"), "set_attributes_add", "get_attributes_add");

	ClassDB::bind_method(D_METHOD("set_attributes_remove", "p_attributes_remove"), &Ability::set_attributes_remove);
	ClassDB::bind_method(D_METHOD("get_attributes_remove"), &Ability::get_attributes_remove);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "attributes_remove", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Attribute"), "set_attributes_remove", "get_attributes_remove");


	ClassDB::bind_method(D_METHOD("set_tags_required", "tags_required"), &Ability::set_tags_required);
	ClassDB::bind_method(D_METHOD("get_tags_required"), &Ability::get_tags_required);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "tags_required", PROPERTY_HINT_ARRAY_TYPE, "StringName"), "set_tags_required", "get_tags_required" );

	ClassDB::bind_method(D_METHOD("set_tags_forbidden", "tags_forbidden"), &Ability::set_tags_forbidden);
	ClassDB::bind_method(D_METHOD("get_tags_forbidden"), &Ability::get_tags_forbidden);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "tags_forbidden", PROPERTY_HINT_ARRAY_TYPE, "StringName"), "set_tags_forbidden", "get_tags_forbidden" );

	ClassDB::bind_method(D_METHOD("set_tags_add", "tags_add"), &Ability::set_tags_add);
	ClassDB::bind_method(D_METHOD("get_tags_add"), &Ability::get_tags_add);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "tags_add", PROPERTY_HINT_ARRAY_TYPE, "StringName"), "set_tags_add", "get_tags_add" );

	ClassDB::bind_method(D_METHOD("set_tags_remove", "tags_remove"), &Ability::set_tags_remove);
	ClassDB::bind_method(D_METHOD("get_tags_remove"), &Ability::get_tags_remove);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "tags_remove", PROPERTY_HINT_ARRAY_TYPE, "StringName"), "set_tags_remove", "get_tags_remove" );

	//PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Image")
}
/*
void ResourceEcs::_bind_methods() {
	//ClassDB::bind_method(D_METHOD("set_id", "p_id"), &ResourceEcs::set_id);
	//ClassDB::bind_method(D_METHOD("get_id"), &ResourceEcs::get_id);
	//ADD_PROPERTY(PropertyInfo(Variant::INT, "p_id"), "set_id", "get_id");

	ClassDB::bind_method(D_METHOD("set_name_var", "p_name"), &ResourceEcs::set_name_var);
	ClassDB::bind_method(D_METHOD("get_name_var"), &ResourceEcs::get_name_var);
	ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "name_var"), "set_name_var", "get_name_var");
}
*/
/*
void NodeECS::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_archetype", "p_archetype"), &NodeECS::set_archetype);
	ClassDB::bind_method(D_METHOD("get_archetype"), &NodeECS::get_archetype);
	ADD_PROPERTY(PropertyInfo(godot::Variant::OBJECT, "archetype", godot::PROPERTY_HINT_RESOURCE_TYPE, "Archetype"), "set_archetype", "get_archetype");
	//ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "archetype", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Archetype"), "set_archetype", "get_archetype");
}
*/

/*
void Actor::_bind_methods() {
}
*/

void Ecs::_notification(int _what) {
	switch(_what) {
		case NOTIFICATION_READY:
			//print("READY!!");
			this->set_physics_process(true);
			break;
		case NOTIFICATION_PHYSICS_PROCESS:
			//print("PHYSICS_PROCESS!!");
			process_ecs();
			break;
	}
}

Ecs *Ecs::get_singleton() {
	if (!Ecs::singleton) {
        Ecs::singleton = memnew(Ecs); // Use Godot's memory allocation
    }
    return Ecs::singleton;
}

void Ecs::connect(SceneTree* scene_tree) {
	if (scene_tree) {
        Window* root = scene_tree->get_root();
        if (root) {
			this->set_physics_process(true);
			root->call_deferred("add_child", this);
        }
    }
}

void Ecs::process_ecs() {
	
	//print("processing.. ", get_process_delta_time());

	for(Ability* ability : ability_map) {
		ability->update();
	}
}

/* //todo: add
void Ecs::register_archetype(Object* object, const TypedArray<Attribute>& attributes) {
	print("creating..");
	print("obj class", object->get_class());
	print("attributes", attributes.size());
	Archetype* p_archetype = memnew(Archetype(object));
	int archetype_id = archetype_map.insert(p_archetype);
	p_archetype->id = archetype_id;
	for(int i; i < attributes.size(); i++) {
		auto attribute = cast_to<Attribute>(attributes[i]);
		p_archetype->attributes.insert(attribute->id);
	}
}
*/

void Ecs::register_object(Object *object) {
	int object_id = object_map.insert(object);
	print("register_object");

	array<Attribute*> object_attributes;

	// get attributes for all archetype ids associated with this object
	array<int> archetype_ids;
	//todo:

	for(Attribute* attribute : object_attributes) {
		attribute->create_attribute_data_entry(); // creates an entry in the attribute for this object and assigns the default values.
	}
	/*
	//todo:remove
	print("registering archetype and creating attributes");
	print("archetypes ", archetype_map.size());
	*/
	/*
	print("attributes ", attribute_map.size());
	print("abilities ", ability_map.size());
	print("objects ", object_map.size());
	*/
	/*
	print("comp map size B: ", attribute_map.size());
	print("ability map size B: ", ability_map.size());
	*/

	// add default value entry in each member attribute at index object_id
	



/*

	//todo: remove for loop need to do for one attribute at a time based on the specific archetype attributes.
	for(int i=0;i<attribute_map.size();i++)
	{
		print("in for loop ", i);

		Attribute* attribute = attribute_map[i];
		//Variant data_var = attribute->get_data_var();
		/*
		attribute->values[object_id] = data_var;
		print("inserted ", object_id, " : ", data_var);
		//attribute->create_array_from_variant(attribute->get_data_var());
		*/
		/*
		int id;
		print("data type", attribute->data_var.get_type());
		switch(attribute->data_var.get_type()) {
			case Variant::BOOL:
				print("Vbool");
				attribute->data_array = sly::array<bool>();
				std::get<array<bool>>(attribute->data_array).insert(attribute->data_var);
				break;
			case Variant::INT:
				print("Vint");
				attribute->data_array = sly::array<int>();
				std::get<array<int>>(attribute->data_array).insert(attribute->data_var);
				break;
			case Variant::FLOAT:
				print("Vfloat");
				attribute->data_array = sly::array<float>();
				id = std::get<array<float>>(attribute->data_array).insert(attribute->data_var);
				print("inserted ", id, " into float attribute with value ", std::get<array<float>>(attribute->data_array)[id]);
				//array<float>* float_array = &std::get<array<float>>(attribute->data_array);
				//float_array->insert(attribute->data_var);
				break;
			case Variant::STRING:
				print("Vstring");
				attribute->data_array = sly::array<String>();
				std::get<array<String>>(attribute->data_array).insert(attribute->data_var);
				break;
			case Variant::STRING_NAME:
				print("Vstringname");
				attribute->data_array = sly::array<StringName>();
				std::get<array<StringName>>(attribute->data_array).insert(attribute->data_var);
				break;
				//todo: add other cases for primitive types
			default:
				print("Vvariant");
				attribute->data_array = sly::array<Variant>();
				std::get<array<Variant>>(attribute->data_array).insert(attribute->data_var);
		}
		*/

		/*
		int data_id = 
		print("Object Id ", object_id, "Data Id ", data_id);
		print("VARIANT DATA : ", attribute->values[object_id]);
		*/
	//}
/*
	for(int i=0;i<attribute_map.size();i++) {
			Attribute* attribute = attribute_map[i];
			for(int i=0;i<attribute->values.size();i++) {
				//print("Variant Data");
				//print("VARIANT DATA : ", attribute->values[i]);
				print("VARIANT DATA : ", attribute->values[i]);
			}
	}
*/
/*
	for(int i=0;i<attribute_map.size();i++)
	{
		Attribute* attribute = attribute_map[i];
		print(attribute.get_data)
	}
*/
}

void Attribute::create_attribute_data_entry() {
	switch(data_var.get_type()) {
		case Variant::BOOL:
			get_data<bool>().insert(data_var);
			break;
		case Variant::INT:
			get_data<int>().insert(data_var);
			break;
		case Variant::FLOAT:
			get_data<float>().insert(data_var);
			break;
		case Variant::STRING:
			get_data<String>().insert(data_var);
			break;
		case Variant::STRING_NAME:
			get_data<StringName>().insert(data_var);
			break;
		//todo: add other cases for primitive types
		default:
			get_data<Variant>().insert(data_var);
	}
}

void Ecs::unregister_object(Object *object) {
	object_map.remove(object_map.find[object]);
}

/*
void Ecs::register_archetype(Archetype *archetype) {
	archetype_map.insert(archetype);
	//Archetype* p_archetype = memnew(Archetype(p_archetype));
	//int archetype_id = archetype_map.insert(archetype);
	//archetype->set_id(archetype_id);
}

void Ecs::unregister_archetype(Archetype *archetype) {
	archetype_map.remove(archetype_map.find[archetype]);
}

void Ecs::register_ability(Ability *ability) {
	ability_map.insert(ability);
}

void Ecs::unregister_ability(Ability *ability) {
	ability_map.remove(ability_map.find[ability]);
}

void Ecs::register_attribute(Attribute *attribute) {
	attribute_map.insert(attribute);
}

void Ecs::unregister_attribute(Attribute *attribute) {
	attribute_map.remove(attribute_map.find[attribute]);
}
*/

void Ability::update() {
	print("updating ability");
	/*
	print("updating ability : ", Ecs::ability_map.find[this]);

	for(Ability* ability : Ecs::ability_map.value) {

	}*/

	//vector<Archetype*> affected_archetypes;
	//get_affected_archetypes()

	/*
	for (NodeEcs* node_ecs : node_ecs_map) {

	}*/

	GDVIRTUAL_CALL(_update);
}
/*
// loads callables from gdscript
void Ability::load_callable_script() {
	Ref<Script> script = ResourceLoader::get_singleton()->load("res://abilities.gd");
	if (script.is_valid()) {
		//Variant result = script->call("your_static_function", arguments);
		// Process the result
	}
}

// loads callables from C++ ability
void Ability::load_callable() {
	TypedArray<Callable> callables;
	Callable movement_ability = Callable(this, "update");
	movement_ability.call();
}
*/

/*
void AbilityUpdaters::ability_movement() {
}*/

	//for(AbilityUpdater::ge)


/*
//TypedArray<Variant::Type> Attribute::create_typed_array_from_variant(const Variant& p_variant) {
Array Attribute::create_array_from_variant(const Variant& p_variant) {
    // get the type from the Variant
    Variant::Type type = p_variant.get_type();

	//TypedArray<type> typed_node_array;
	//godot::Array new_array(base_array, godot::Variant::NIL, godot::StringName(), (godot::Script*)nullptr);
	//Array base_array; // Create an empty base array

	Array base_array;
	//TypedArray<Variant> base_array;

	StringName class_name = "";

	// If the variant holds an Object-derived type, we need its class name
    if (type == Variant::Type::OBJECT) {
        // We attempt to get the object's actual class name if it exists.
        // If p_variant is null/empty, we can't reliably get the class, 
        // so you might want a default behavior (e.g., untyped Array or Array[Object]).

		Object* object = cast_to<Object>(p_variant);
        if (object != nullptr) {
            Object* obj = p_variant.operator Object *();
            if (obj) {
                class_name = obj->get_class();
            }
        }
    }

    // 2. Create the TypedArray using the type information
    // The Array constructor allows setting the expected type at runtime.
    // We use the base Array constructor for runtime typing, then cast to TypedArray<Variant>.
    // Internally, Godot manages type checking for these arrays.

    Array new_array(base_array, type, class_name, (Script*)nullptr); // Pass type, class_name, and script (null for C++ built-ins)

	new_array.set_typed(type, Node::get_class_static(), Variant());

	new_array.push_back(p_variant);

	print("array created", new_array.size());
	print("variant value is :", p_variant);

    // Note: The TypedArray<T> C++ wrapper is mostly for compile-time convenience and
    // better C++ type handling, but the underlying Godot Array can have its type
    // set at runtime using the Variant::Type enum and class name.

    // You can now add elements of the correct type to the 'new_array'.
    // The Godot runtime will enforce the type check.
    // For this example, we return a TypedArray<Variant> which holds the runtime type info.
    // When passed to GDScript, it will behave as a typed array of the specified type.
    return new_array;
}
*/



} // namespace sly