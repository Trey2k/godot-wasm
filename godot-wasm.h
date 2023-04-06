#ifndef GODOT_WASM_H
#define GODOT_WASM_H
#include <string>
#include <vector>
#include "wasmer.h"

#ifdef GODOT_WASM_EXTENSION
#include <godot_cpp/classes/ref.hpp>
using namespace godot;
#else
#include "core/object/ref_counted.h"
#include "core/core_bind.h"
#endif

class Wasm : public RefCounted {
  GDCLASS(Wasm, RefCounted)

protected:
  static void _bind_methods();

private:
  wasm_engine_t *engine;
  wasm_store_t *store;
  wasm_module_t *module;
  wasm_instance_t *instance;
  Dictionary functions;
  Dictionary globals;
  wasm_memory_t *memory;
  void map_names();

public:
  Wasm();
  ~Wasm();
  void _init();
  // godot_error compile(PoolByteArray bytecode);
  // godot_error instantiate(PoolByteArray bytecode);
  Error load(PackedByteArray bytecode);
  Dictionary inspect();
  Variant function(String name, Array args);
  Variant global(String name);
  Variant mem_read(uint32_t type, uint64_t offset, uint32_t length);
  uint64_t mem_write(Variant value, uint64_t offset);
};

#endif
