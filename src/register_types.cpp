#include "register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include <godot_cpp/classes/engine.hpp> // for get_singleton()

#include "ecs.h"

using namespace godot;
using namespace sly;

void initialize_gdextension_types(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	// register classes
	GDREGISTER_RUNTIME_CLASS(Ecs);
	//GDREGISTER_RUNTIME_CLASS(Tag);
	GDREGISTER_RUNTIME_CLASS(ResourceEcs);
	GDREGISTER_RUNTIME_CLASS(RefCountedEcs);
	GDREGISTER_RUNTIME_CLASS(NodeEcs);
	GDREGISTER_RUNTIME_CLASS(Actor);
	GDREGISTER_RUNTIME_CLASS(Entity);
	GDREGISTER_RUNTIME_CLASS(Component);
	GDREGISTER_RUNTIME_CLASS(System);
	GDREGISTER_RUNTIME_CLASS(SystemUpdater);	// todo: should this be merged with system?!


	// register singletons
	godot::Engine::get_singleton()->register_singleton(StringName("Ecs"), Ecs::get_singleton());
}

void uninitialize_gdextension_types(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	// unregister singletons
	godot::Engine::get_singleton()->unregister_singleton(StringName("Ecs"));
	if (Ecs::get_singleton()) memdelete(Ecs::get_singleton());
}

extern "C"
{
	// Initialization
	GDExtensionBool GDE_EXPORT slyecs_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
	{
		GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
		init_obj.register_initializer(initialize_gdextension_types);
		init_obj.register_terminator(uninitialize_gdextension_types);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

		return init_obj.init();
	}
}
