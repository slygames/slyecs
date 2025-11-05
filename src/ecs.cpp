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
	ClassDB::bind_method(D_METHOD("create_entity", "object", "components"), &Ecs::create_entity, DEFVAL(TypedArray<Component>()));
	ClassDB::bind_method(D_METHOD("remove_entity", "object"), &Ecs::remove_entity);
}

void Entity::_bind_methods() {
}

void System::_bind_methods() {
	ClassDB::bind_method(D_METHOD("update"), &System::update);
	GDVIRTUAL_BIND(_update);
}

void ResourceEcs::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_name_var", "new_name"), &Component::set_name_var);
	ClassDB::bind_method(D_METHOD("get_name_var"), &Component::get_name_var);
	ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "name_var"), "set_name_var", "get_name_var");
}

void Component::_bind_methods() {
}

void Ecs::_notification(int p_what) {
	switch(p_what) {
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

void Ecs::create_entity(Object* object, const TypedArray<Component>& components = TypedArray<Component>()) {
	print("creating..");
	print("obj class", object->get_class());
	print("components", components.size());
	Entity* new_entity = memnew(Entity(object));
	int entity_id = entity_map.insert(new_entity);
	new_entity->id = entity_id;
	for(int i; i < components.size(); i++) {
		auto component = cast_to<Component>(components[i]);
		new_entity->components.insert(component->id);
	}
}

void Ecs::remove_entity(Object *object) {
	Entity* entity;
	int entity_id = entity_map.find[entity];
	entity_map.remove(entity_id);
	memdelete(entity);
}

void System::update() {
	print("updating system : ", this->id);
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

void SystemUpdaters::system_movement() {
}
	
} // namespace sly
