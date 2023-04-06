def can_build(env, platform):
    return True

def configure(env):
    from SCons.Script import BoolVariable, EnumVariable, Variables, Help

    opts = Variables()

    opts.Add(BoolVariable('download_wasmer', 'Download Wasmer library', 'no'))
    opts.Add('wasmer_version', 'Wasmer library version', 'v3.1.1')
    
    opts.Update(env)
    Help(opts.GenerateHelpText(env))

#def get_doc_classes():
#    return []

#def get_doc_path():
 #   return "doc_classes"