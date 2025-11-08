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

void sly::Ecs::_bind_methods() {
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

	ClassDB::bind_method(D_METHOD("set_entity", "p_entity"), &NodeECS::set_entity);
	ClassDB::bind_method(D_METHOD("get_entity"), &NodeECS::get_entity);
	ADD_PROPERTY(PropertyInfo(godot::Variant::OBJECT, "entity", godot::PROPERTY_HINT_RESOURCE_TYPE, "Entity"), "set_entity", "get_entity");
/*
	ClassDB::bind_method(D_METHOD("set_components", "p_components"), &NodeECS::set_components);
	ClassDB::bind_method(D_METHOD("get_components"), &NodeECS::get_components);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "components", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Component"), "set_components", "get_components");
*/

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

System::System() {
	print("CONSTRUCT System");
	Ecs::system_map.insert(this);
	print("system map size A: ", Ecs::system_map.size());
}


void Component::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_data_var", "p_data_var"), &Component::set_data_var);
	ClassDB::bind_method(D_METHOD("get_data_var"), &Component::get_data_var);
	ADD_PROPERTY(PropertyInfo(Variant::NIL, "data_var", PROPERTY_HINT_NONE, "Variant", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_NIL_IS_VARIANT ), "set_data_var", "get_data_var");
	//ADD_PROPERTY(PropertyInfo(Variant::NIL, "data_var"), "set_data_var", "get_data_var");
	//ADD_PROPERTY(PropertyInfo(Variant::NIL, "data_var", PROPERTY_HINT_TYPE_STRING, String::num(Variant::NIL) + "/" + String::num(PROPERTY_HINT_NONE) + ":Variant"), "set_data_var", "get_data_var");
}

void System::_bind_methods() {
	ClassDB::bind_method(D_METHOD("update"), &System::update);
	GDVIRTUAL_BIND(_update);

	ClassDB::bind_method(D_METHOD("set_components", "p_components"), &System::set_components);
	ClassDB::bind_method(D_METHOD("get_components"), &System::get_components);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "components", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Component"), "set_components", "get_components");

	ClassDB::bind_method(D_METHOD("set_tags_required", "tags_required"), &System::set_tags_required);
	ClassDB::bind_method(D_METHOD("get_tags_required"), &System::get_tags_required);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "tags_required", PROPERTY_HINT_ARRAY_TYPE, "StringName"), "set_tags_required", "get_tags_required" );
	
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
	object_map.insert(object);
	print("entities ", entity_map.size());
	/*
	print("components ", component_map.size());
	print("systems ", system_map.size());
	print("objects ", object_map.size());
	*/
	print("comp map size B: ", component_map.size());
	print("system map size B: ", system_map.size());
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
} // namespace sly
