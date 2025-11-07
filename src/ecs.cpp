#include "ecs.h"
#include <godot_cpp/core/class_db.hpp>

namespace sly {

map<Entity*> Ecs::entity_map;
map<Component*> Ecs::component_map;
map<System*> Ecs::system_map;

// initialize static variables
Ecs* Ecs::singleton = nullptr;

void sly::Ecs::_bind_methods() {
	ClassDB::bind_method(D_METHOD("connect", "scene_tree"), &Ecs::connect);
	//todo:add
	//ClassDB::bind_method(D_METHOD("create_entity", "object", "components"), &Ecs::register_entity, DEFVAL(TypedArray<Component>()));
	ClassDB::bind_method(D_METHOD("create_entity", "entity"), &Ecs::register_entity);
	ClassDB::bind_method(D_METHOD("remove_entity", "entity"), &Ecs::unregister_entity);
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
}

void Entity::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_components", "p_components"), &Entity::set_components);
	ClassDB::bind_method(D_METHOD("get_components"), &Entity::get_components);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "components", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Component"), "set_components", "get_components");
	/*
	ClassDB::bind_method(D_METHOD("set_nodes", "p_nodes"), &Entity::set_nodes);
	ClassDB::bind_method(D_METHOD("get_nodes"), &Entity::get_nodes);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "nodes", PROPERTY_HINT_NODE_TYPE, "Node"), "set_nodes", "get_nodes");
	*/

	//ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "components", PROPERTY_HINT_ARRAY_TYPE, "Variant::Component"), "set_components", "get_components" );
	
	//PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Image")
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

void ResourceEcs::_bind_methods() {
	//ClassDB::bind_method(D_METHOD("set_id", "p_id"), &ResourceEcs::set_id);
	ClassDB::bind_method(D_METHOD("get_id"), &ResourceEcs::get_id);
	//ADD_PROPERTY(PropertyInfo(Variant::INT, "p_id"), "set_id", "get_id");

	ClassDB::bind_method(D_METHOD("set_name_var", "p_name"), &ResourceEcs::set_name_var);
	ClassDB::bind_method(D_METHOD("get_name_var"), &ResourceEcs::get_name_var);
	ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "name_var"), "set_name_var", "get_name_var");
}

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

	for(Ref<System> system : system_map) {
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

void Ecs::register_entity(Entity* p_entity) {
	//Entity* p_entity = memnew(Entity(p_entity));
	int entity_id = entity_map.insert(p_entity);
	p_entity->set_id(entity_id);
}


void Ecs::unregister_entity(Entity *p_entity) {
	int entity_id = entity_map.find[p_entity];
	entity_map.remove(entity_id);
	//memdelete(entity);
}

void Ecs::register_system(System *system) {
}

void Ecs::unregister_system(System *system) {
}

void Ecs::register_component(Component *system) {
}

void Ecs::unregister_component(Component *system) {
}

void System::update() {
	print("updating system");
	//print("updating system : ", this->get_id());
	GDVIRTUAL_CALL(_update);
}

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
/*
void SystemUpdaters::system_movement() {
}*/

	//for(SystemUpdater::ge)
} // namespace sly
