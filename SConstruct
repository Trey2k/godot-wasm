#!python
import os
import shutil
import re
from urllib import request
import tarfile

opts = Variables([], ARGUMENTS)

# Define options
opts.Add(BoolVariable('download_wasmer', 'Download Wasmer library', 'no'))
opts.Add('wasmer_version', 'Wasmer library version', 'v3.1.1')

# Standard flags CC, CCX, etc. with options
env = SConscript('godot-cpp/SConstruct')
opts.Update(env)
# Wasmer download
def download_wasmer(env):
    def download_tarfile(url, dest, rename={}):
        filename = 'tmp.tar.gz'
        os.makedirs(dest, exist_ok=True)
        request.urlretrieve(url, filename)
        file = tarfile.open(filename)
        file.extractall(dest)
        file.close()
        for k, v in rename.items(): os.rename(k, v)
        os.remove(filename)
    base_url = 'https://github.com/wasmerio/wasmer/releases/download/{}/wasmer-{}.tar.gz'
    if env['platform'] == 'osx':
        # For macOS, we need to universalize the AMD and ARM libraries
        download_tarfile(base_url.format(env['wasmer_version'], 'darwin-amd64'), 'wasmer', {'wasmer/lib/libwasmer.a': 'wasmer/lib/libwasmer.amd64.a'})
        download_tarfile(base_url.format(env['wasmer_version'], 'darwin-arm64'), 'wasmer', {'wasmer/lib/libwasmer.a': 'wasmer/lib/libwasmer.arm64.a'})
        os.system('lipo wasmer/lib/libwasmer*.a -output wasmer/lib/libwasmer.a -create')
    elif env['platform'] == 'linux':
        download_tarfile(base_url.format(env['wasmer_version'], 'linux-amd64'), 'wasmer')
    elif env['platform'] == 'windows':
        download_tarfile(base_url.format(env['wasmer_version'], 'windows-amd64'), 'wasmer')

if env['download_wasmer'] or not os.path.isdir('wasmer'):
    shutil.rmtree('wasmer', True)
    download_wasmer(env)

# Explicit static libraries
wasmer_library = File('wasmer/lib/{}wasmer{}'.format(env['LIBPREFIX'], env.get('LIBWASMERSUFFIX', env['LIBSUFFIX'])))

# CPP includes and libraries
env.Append(CPPPATH=['.', 'wasmer/include'])
env.Append(LIBS=[wasmer_library])
env.Append(CPPDEFINES=['GODOT_WASM_EXTENSION'])

# Builders
library = env.SharedLibrary(
    "addons/godot-wasm/bin/libgodot-wasm{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
    source=Glob('*.cpp'),
)

Default(library)

env.Help(opts.GenerateHelpText(env))

