#ifndef WASM_REGISTER_TYPES_H
#define WASM_REGISTER_TYPES_H

#ifdef GODOT_WASM_EXTENSION

#include <godot_cpp/core/class_db.hpp>
using namespace godot;

#else

#include "modules/register_module_types.h"

#endif

void initialize_wasm_module(ModuleInitializationLevel p_level);
void uninitialize_wasm_module(ModuleInitializationLevel p_level);

#endif