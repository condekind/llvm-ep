
add_llvm_library( LLVMcfg2dot MODULE
  cfg2dot.cpp

  DEPENDS
  intrinsics_gen
  PLUGIN_TOOL
  opt
  )
