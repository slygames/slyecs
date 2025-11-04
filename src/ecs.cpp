#include "ecs.h"
#include <godot_cpp/core/class_db.hpp>

namespace sly {

map<Ecs::Entity*> Ecs::entity_map;
map<Ecs::Component*> Ecs::component_map;
map<Ecs::System*> Ecs::system_map;

// initialize static variables
Ecs* Ecs::singleton = nullptr;

void sly::Ecs::_bind_methods() {
	ClassDB::bind_method(D_METHOD("connect", "scene_tree"), &Ecs::connect);
}

void Ecs::System::_bind_methods() {
	ClassDB::bind_method(D_METHOD("update"), &Ecs::System::update);
	GDVIRTUAL_BIND(_update);
}

void Ecs::_notification(int p_what) {
	switch(p_what) {
		case NOTIFICATION_READY:
			print("READY!!");
			break;
		case NOTIFICATION_PHYSICS_PROCESS:
			print("PHYSICS_PROCESS!!");
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
	
	print("processing.. ", get_process_delta_time());

	for(System* system : system_map) {
		system->update();
	}
}

void Ecs::System::update() {
	print("updating system : ", this->id);
	GDVIRTUAL_CALL(_update);
}

} // namespace sly
