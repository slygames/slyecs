#include "ecs.h"

namespace sly {

map<Ecs::Entity*> Ecs::entity_map;
map<Ecs::Component*> Ecs::component_map;
map<Ecs::System*> Ecs::system_map;


void Ecs::_bind_methods() {
	godot::ClassDB::bind_method(D_METHOD("print_type", "variant"), &Ecs::print_type);
}

void Ecs::process_ecs() {
}

void Ecs::print_type(const Variant &p_variant) const {
	print_line(vformat("Type: %d", p_variant.get_type()));
}

} // namespace sly

