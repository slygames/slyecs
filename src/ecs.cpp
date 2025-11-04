#include "ecs.h"

namespace sly {

void Ecs::_bind_methods() {
	godot::ClassDB::bind_method(D_METHOD("print_type", "variant"), &Ecs::print_type);
}

void Ecs::print_type(const Variant &p_variant) const {
	print_line(vformat("Type: %d", p_variant.get_type()));
}

}