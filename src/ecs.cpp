#include "ecs.h"
#include <godot_cpp/core/class_db.hpp>

namespace sly {

map<Object*> Ecs::object_map;
map<Entity*> Ecs::entity_map;
map<Component*> Ecs::component_map;
map<System*> Ecs::system_map;
//map<StringName> Ecs::tag_map;

// initialize static variables
Ecs* Ecs::singleton = nullptr;

void Ecs::_bind_methods() {
	//ClassDB::bind_static_method("Ecs", D_METHOD("get_singleton"), &Ecs::get_singleton);
	ClassDB::bind_method(D_METHOD("connect", "scene_tree"), &Ecs::connect);
	//todo:add
	//ClassDB::bind_method(D_METHOD("create_entity", "object", "components"), &Ecs::register_entity, DEFVAL(TypedArray<Component>()));
	ClassDB::bind_method(D_METHOD("create_entity", "entity"), &Ecs::register_object);
	ClassDB::bind_method(D_METHOD("remove_entity", "entity"), &Ecs::unregister_object);


	ClassDB::bind_method(D_METHOD("set_systems", "p_systems"), &Ecs::set_systems);
	ClassDB::bind_method(D_METHOD("get_systems"), &Ecs::get_systems);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "systems", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":System"), "set_systems", "get_systems");
	//ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "systems", PROPERTY_HINT_ARRAY_TYPE, "System"), "set_systems", "get_systems");

}

void NodeECS::_bind_methods() {
/*
	ClassDB::bind_method(D_METHOD("set_entity", "p_entity"), &NodeECS::set_entity);
	ClassDB::bind_method(D_METHOD("get_entity"), &NodeECS::get_entity);
	ADD_PROPERTY(PropertyInfo(godot::Variant::OBJECT, "entity", godot::PROPERTY_HINT_RESOURCE_TYPE, "Entity"), "set_entity", "get_entity");
*/

/*
	ClassDB::bind_method(D_METHOD("set_components", "p_components"), &NodeECS::set_components);
	ClassDB::bind_method(D_METHOD("get_components"), &NodeECS::get_components);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "components", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Component"), "set_components", "get_components");
*/

	ClassDB::bind_method(D_METHOD("set_entities", "p_entities"), &NodeECS::set_entities);
	ClassDB::bind_method(D_METHOD("get_entities"), &NodeECS::get_entities);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "entities", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Entity"), "set_entities", "get_entities");

	ClassDB::bind_method(D_METHOD("set_components", "p_components"), &NodeECS::set_components);
	ClassDB::bind_method(D_METHOD("get_components"), &NodeECS::get_components);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "components", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Component"), "set_components", "get_components");

	ClassDB::bind_method(D_METHOD("set_tags", "tags"), &NodeECS::set_tags);
	ClassDB::bind_method(D_METHOD("get_tags"), &NodeECS::get_tags);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "tags", PROPERTY_HINT_ARRAY_TYPE, "StringName"), "set_tags", "get_tags" );
}

void NodeECS::_notification(int p_what) {
	switch(p_what) {
		case NOTIFICATION_READY:
			// register parent of NodeEcs as the game object
			Ecs::get_singleton()->register_object(this->get_parent());

			// get unique set of all components from entities
			std::set<Component*> object_components;
			for(int i=0;i<entities.size();i++) {
				Entity* entity = cast_to<Entity>(entities[i]);
				TypedArray<Component> entity_components = entity->get_components();
				for(int j=0;j<entity_components.size();j++) {
					Component* component = cast_to<Component>(entity_components[j]);
					object_components.insert(component);
				}
			}
			// also get components arrays specified in the NodeEcs
			for(int i=0;i<components.size();i++) {
				Component* component = cast_to<Component>(components[i]);
				object_components.insert(component);
			}

			/*
			for(int i=0;i<object_components.size();i++) {
				object_components.data_var
			}*/

			//todo: need to create all the data rows for the components for this object and also associate the tags with the object.

			break;
	}
}

void Entity::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_components", "p_components"), &Entity::set_components);
	ClassDB::bind_method(D_METHOD("get_components"), &Entity::get_components);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "components", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Component"), "set_components", "get_components");

	ClassDB::bind_method(D_METHOD("set_tags", "tags"), &Entity::set_tags);
	ClassDB::bind_method(D_METHOD("get_tags"), &Entity::get_tags);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "tags", PROPERTY_HINT_ARRAY_TYPE, "StringName"), "set_tags", "get_tags" );


	/*
	ClassDB::bind_method(D_METHOD("set_nodes", "p_nodes"), &Entity::set_nodes);
	ClassDB::bind_method(D_METHOD("get_nodes"), &Entity::get_nodes);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "nodes", PROPERTY_HINT_NODE_TYPE, "Node"), "set_nodes", "get_nodes");
	*/

	//ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "components", PROPERTY_HINT_ARRAY_TYPE, "Variant::Component"), "set_components", "get_components" );
	
	//PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Image")
}

Entity::Entity() {
	Ecs::entity_map.insert(this);
}

Component::Component() {
	print("CONSTRUCT component");
	Ecs::component_map.insert(this);
	print("comp map size A: ", Ecs::component_map.size());
}

void Component::set_data_var(const Variant &p_data_var) {
		print("set_data_var gdextension");
		data_var = p_data_var; 
		if(&p_data_var==nullptr) {
			print("data_var is null");
		}
		print("setting data_var ", p_data_var.get_type(), " : ", p_data_var);

		int id; //todo:remove
		switch(data_var.get_type()) {
			case Variant::BOOL:
				print("Vbool");
				data_array = sly::array<bool>();
				std::get<array<bool>>(data_array).insert(data_var);
				break;
			case Variant::INT:
				print("Vint");
				data_array = sly::array<int>();
				std::get<array<int>>(data_array).insert(data_var);
				break;
			case Variant::FLOAT:
				print("Vfloat");
				data_array = sly::array<float>();
				id = std::get<array<float>>(data_array).insert(data_var);
				print("inserted ", id, " into float component with value ", std::get<array<float>>(data_array)[id]);
				/*
				array<float>* float_array = &std::get<array<float>>(data_array);
				float_array->insert(data_var);
				*/
				break;
			case Variant::STRING:
				print("Vstring");
				data_array = sly::array<String>();
				std::get<array<String>>(data_array).insert(data_var);
				break;
			case Variant::STRING_NAME:
				print("Vstringname");
				data_array = sly::array<StringName>();
				std::get<array<StringName>>(data_array).insert(data_var);
				break;
				//todo: add other cases for primitive types
			default:
				print("Vvariant");
				data_array = sly::array<Variant>();
				std::get<array<Variant>>(data_array).insert(data_var);
		}
		emit_changed(); // for Resources to notify the editor/users of changes
}

System::System() {
	print("CONSTRUCT System");
	Ecs::system_map.insert(this);
	print("system map size A: ", Ecs::system_map.size());
}


void Component::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_data_var", "p_data_var"), &Component::set_data_var);
	ClassDB::bind_method(D_METHOD("get_data_var"), &Component::get_data_var);
	//ADD_PROPERTY(PropertyInfo(Variant::NIL, "data_var", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT), "set_data_var", "get_data_var");
	//ADD_PROPERTY(PropertyInfo(Variant::NIL, "data_var", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_NIL_IS_VARIANT ), "set_data_var", "get_data_var");
	ADD_PROPERTY(PropertyInfo(Variant::NIL, "data_var", PROPERTY_HINT_NONE, "Variant", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_NIL_IS_VARIANT ), "set_data_var", "get_data_var");

	/*
	ClassDB::bind_method(D_METHOD("set_data_var", "p_data_var"), &Component::set_data_var);
	ClassDB::bind_method(D_METHOD("get_data_var"), &Component::get_data_var);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "data_var_array", PROPERTY_HINT_TYPE_STRING, String::num(Variant::NIL)+ "/" + String::num(PROPERTY_HINT_NONE) + ":Variant"), "set_data_var", "get_data_var");
	//ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "data_var", PROPERTY_HINT_NONE, "Variant", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_NIL_IS_VARIANT ), "set_data_var", "get_data_var");
	*/


	/*
	ClassDB::bind_method(D_METHOD("set_data_var", "p_data_var"), &Component::set_data_var);
	ClassDB::bind_method(D_METHOD("get_data_var"), &Component::get_data_var);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "my_variant_array", PROPERTY_HINT_TYPE_STRING, String::num(Variant::NIL)), "set_data_var", "get_data_var");
*/
	//ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "data_var", PROPERTY_HINT_ARRAY_TYPE, "Variant", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_NIL_IS_VARIANT ), "set_data_var", "get_data_var");
	
	//ADD_PROPERTY(PropertyInfo(Variant::NIL, "data_var"), "set_data_var", "get_data_var");
	//ADD_PROPERTY(PropertyInfo(Variant::NIL, "data_var", PROPERTY_HINT_TYPE_STRING, String::num(Variant::NIL) + "/" + String::num(PROPERTY_HINT_NONE) + ":Variant"), "set_data_var", "get_data_var");
}

void System::_bind_methods() {
	ClassDB::bind_method(D_METHOD("update"), &System::update);
	GDVIRTUAL_BIND(_update);

	ClassDB::bind_method(D_METHOD("set_components_required", "p_components_required"), &System::set_components_required);
	ClassDB::bind_method(D_METHOD("get_components_required"), &System::get_components_required);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "components_required", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Component"), "set_components_required", "get_components_required");

	ClassDB::bind_method(D_METHOD("set_components_forbidden", "p_components_forbidden"), &System::set_components_forbidden);
	ClassDB::bind_method(D_METHOD("get_components_forbidden"), &System::get_components_forbidden);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "components_forbidden", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Component"), "set_components_forbidden", "get_components_forbidden");

	ClassDB::bind_method(D_METHOD("set_components_add", "p_components_add"), &System::set_components_add);
	ClassDB::bind_method(D_METHOD("get_components_add"), &System::get_components_add);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "components_add", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Component"), "set_components_add", "get_components_add");

	ClassDB::bind_method(D_METHOD("set_components_remove", "p_components_remove"), &System::set_components_remove);
	ClassDB::bind_method(D_METHOD("get_components_remove"), &System::get_components_remove);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "components_remove", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Component"), "set_components_remove", "get_components_remove");


	ClassDB::bind_method(D_METHOD("set_tags_required", "tags_required"), &System::set_tags_required);
	ClassDB::bind_method(D_METHOD("get_tags_required"), &System::get_tags_required);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "tags_required", PROPERTY_HINT_ARRAY_TYPE, "StringName"), "set_tags_required", "get_tags_required" );

	ClassDB::bind_method(D_METHOD("set_tags_forbidden", "tags_forbidden"), &System::set_tags_forbidden);
	ClassDB::bind_method(D_METHOD("get_tags_forbidden"), &System::get_tags_forbidden);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "tags_forbidden", PROPERTY_HINT_ARRAY_TYPE, "StringName"), "set_tags_forbidden", "get_tags_forbidden" );

	ClassDB::bind_method(D_METHOD("set_tags_add", "tags_add"), &System::set_tags_add);
	ClassDB::bind_method(D_METHOD("get_tags_add"), &System::get_tags_add);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "tags_add", PROPERTY_HINT_ARRAY_TYPE, "StringName"), "set_tags_add", "get_tags_add" );

	ClassDB::bind_method(D_METHOD("set_tags_remove", "tags_remove"), &System::set_tags_remove);
	ClassDB::bind_method(D_METHOD("get_tags_remove"), &System::get_tags_remove);
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
	ClassDB::bind_method(D_METHOD("set_entity", "p_entity"), &NodeECS::set_entity);
	ClassDB::bind_method(D_METHOD("get_entity"), &NodeECS::get_entity);
	ADD_PROPERTY(PropertyInfo(godot::Variant::OBJECT, "entity", godot::PROPERTY_HINT_RESOURCE_TYPE, "Entity"), "set_entity", "get_entity");
	//ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Entity"), "set_entity", "get_entity");
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

	for(System* system : system_map) {
		system->update();
	}
}

/* //todo: add
void Ecs::register_entity(Object* object, const TypedArray<Component>& components) {
	print("creating..");
	print("obj class", object->get_class());
	print("components", components.size());
	Entity* p_entity = memnew(Entity(object));
	int entity_id = entity_map.insert(p_entity);
	p_entity->id = entity_id;
	for(int i; i < components.size(); i++) {
		auto component = cast_to<Component>(components[i]);
		p_entity->components.insert(component->id);
	}
}
*/

void Ecs::register_object(Object *object) {
	int object_id = object_map.insert(object);

	/*
	//todo:remove
	print("registering entity and creating components");
	print("entities ", entity_map.size());
	*/
	/*
	print("components ", component_map.size());
	print("systems ", system_map.size());
	print("objects ", object_map.size());
	*/
	/*
	print("comp map size B: ", component_map.size());
	print("system map size B: ", system_map.size());
	*/

	// add default value entry in each member component at index object_id
	



/*

	//todo: remove for loop need to do for one component at a time based on the specific entity components.
	for(int i=0;i<component_map.size();i++)
	{
		print("in for loop ", i);

		Component* component = component_map[i];
		//Variant data_var = component->get_data_var();
		/*
		component->values[object_id] = data_var;
		print("inserted ", object_id, " : ", data_var);
		//component->create_array_from_variant(component->get_data_var());
		*/
		/*
		int id;
		print("data type", component->data_var.get_type());
		switch(component->data_var.get_type()) {
			case Variant::BOOL:
				print("Vbool");
				component->data_array = sly::array<bool>();
				std::get<array<bool>>(component->data_array).insert(component->data_var);
				break;
			case Variant::INT:
				print("Vint");
				component->data_array = sly::array<int>();
				std::get<array<int>>(component->data_array).insert(component->data_var);
				break;
			case Variant::FLOAT:
				print("Vfloat");
				component->data_array = sly::array<float>();
				id = std::get<array<float>>(component->data_array).insert(component->data_var);
				print("inserted ", id, " into float component with value ", std::get<array<float>>(component->data_array)[id]);
				//array<float>* float_array = &std::get<array<float>>(component->data_array);
				//float_array->insert(component->data_var);
				break;
			case Variant::STRING:
				print("Vstring");
				component->data_array = sly::array<String>();
				std::get<array<String>>(component->data_array).insert(component->data_var);
				break;
			case Variant::STRING_NAME:
				print("Vstringname");
				component->data_array = sly::array<StringName>();
				std::get<array<StringName>>(component->data_array).insert(component->data_var);
				break;
				//todo: add other cases for primitive types
			default:
				print("Vvariant");
				component->data_array = sly::array<Variant>();
				std::get<array<Variant>>(component->data_array).insert(component->data_var);
		}
		*/

		/*
		int data_id = 
		print("Object Id ", object_id, "Data Id ", data_id);
		print("VARIANT DATA : ", component->values[object_id]);
		*/
	//}
/*
	for(int i=0;i<component_map.size();i++) {
			Component* component = component_map[i];
			for(int i=0;i<component->values.size();i++) {
				//print("Variant Data");
				//print("VARIANT DATA : ", component->values[i]);
				print("VARIANT DATA : ", component->values[i]);
			}
	}
*/
/*
	for(int i=0;i<component_map.size();i++)
	{
		Component* component = component_map[i];
		print(component.get_data)
	}
*/
}

void Ecs::unregister_object(Object *object) {
	object_map.remove(object_map.find[object]);
}

/*
void Ecs::register_entity(Entity *entity) {
	entity_map.insert(entity);
	//Entity* p_entity = memnew(Entity(p_entity));
	//int entity_id = entity_map.insert(entity);
	//entity->set_id(entity_id);
}

void Ecs::unregister_entity(Entity *entity) {
	entity_map.remove(entity_map.find[entity]);
}

void Ecs::register_system(System *system) {
	system_map.insert(system);
}

void Ecs::unregister_system(System *system) {
	system_map.remove(system_map.find[system]);
}

void Ecs::register_component(Component *component) {
	component_map.insert(component);
}

void Ecs::unregister_component(Component *component) {
	component_map.remove(component_map.find[component]);
}
*/

void System::update() {
	print("updating system");
	/*
	print("updating system : ", Ecs::system_map.find[this]);

	for(System* system : Ecs::system_map.value) {

	}*/

	//vector<Entity*> affected_entities;
	//get_affected_entities()

	/*
	for (NodeEcs* node_ecs : node_ecs_map) {

	}*/

	GDVIRTUAL_CALL(_update);
}
/*
// loads callables from gdscript
void System::load_callable_script() {
	Ref<Script> script = ResourceLoader::get_singleton()->load("res://systems.gd");
	if (script.is_valid()) {
		//Variant result = script->call("your_static_function", arguments);
		// Process the result
	}
}

// loads callables from C++ system
void System::load_callable() {
	TypedArray<Callable> callables;
	Callable movement_system = Callable(this, "update");
	movement_system.call();
}
*/

/*
void SystemUpdaters::system_movement() {
}*/

	//for(SystemUpdater::ge)


/*
//TypedArray<Variant::Type> Component::create_typed_array_from_variant(const Variant& p_variant) {
Array Component::create_array_from_variant(const Variant& p_variant) {
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