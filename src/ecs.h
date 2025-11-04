#pragma once

#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"

using namespace godot;

namespace sly {

class Ecs : public RefCounted {
	GDCLASS(Ecs, RefCounted)

protected:
	static void _bind_methods();

public:
	Ecs() = default;
	~Ecs() override = default;

	void print_type(const Variant &p_variant) const;
};

}