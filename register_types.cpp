#include "register_types.h"

#include "godot-wasm.h"

void initialize_wasm_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
		return;
	
	ClassDB::register_class<Wasm>();
}

void uninitialize_wasm_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
		return;
}

#ifdef GODOT_WASM_EXTENSION
extern "C"
{
	// Initialization.

	GDExtensionBool GDE_EXPORT wasm_library_init(const GDExtensionInterface *p_interface, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
	{
		GDExtensionBinding::InitObject init_obj(p_interface, p_library, r_initialization);

		init_obj.register_initializer(initialize_wasm_module);
		init_obj.register_terminator(uninitialize_wasm_module);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

		return init_obj.init();
	}
}
#endif