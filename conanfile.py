# pylint: disable=missing-docstring
from conans import ConanFile, CMake


class LibDABDecodeConan(ConanFile):
    name = 'libdabdecode'
    version = '1.0.2'
    description = (
        'The DAB frame decoding infrastructure of the ODR DAB data toolkit, '
        'that provides types and functions to work with DAB transmission '
        'frames'
    )
    settings = (
        'arch',
        'build_type',
        'compiler',
        'os',
    )
    options = {
        'shared': [True, False],
        'test': [True, False],
    }
    default_options = (
        'shared=True',
        'test=True',
    )
    url = 'https://github.com/Opendigitalradio/libdabdecode.git'
    license = 'BSD 3-clause'
    exports_sources = (
        'CMakeLists.txt',
        'LICENSE',
        'README.md',
        'cmake/*',
        'include/*',
        'src/*',
    )

    def build(self):
        cmake = CMake(self, parallel=True)
        cmake.definitions['EXTERNAL_DEPS_VIA'] = 'conan'
        cmake.configure()
        cmake.build()
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = [
            'dabdecode'
        ]
        self.cpp_info.includedirs = [
            'include'
        ]

    def requirements(self):
        self.requires('libdabcommon/[>=1.0]@Opendigitalradio/stable')