from conans import ConanFile, CMake

class ConnectorNetworkConan(ConanFile):
    name = "connector_network"
    version = "1.0"
    settings = "os", "compiler", "build_type"
    generators = "cmake", "cmake_find_package", "cmake_paths"

    # Dependencies are system-installed:
    # - libboost-all-dev (Boost)
    # - libssl-dev (OpenSSL)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
