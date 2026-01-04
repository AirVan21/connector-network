# connector-network

Shared WebSocket connection library for C++ projects. Provides a secure WebSocket client using Boost.Beast and OpenSSL.

## Features

- Secure WebSocket (WSS) connections with TLS 1.2
- Asynchronous message handling via callbacks
- Non-blocking connect, send, and receive operations
- Clean disconnect handling

## Dependencies

- **C++20** compiler (GCC 10+, Clang 10+)
- **Boost** (ASIO, Beast)
- **OpenSSL** 1.1.1+

### Ubuntu/Debian
```bash
apt-get install -y build-essential cmake libboost-all-dev libssl-dev
```

### macOS
```bash
brew install boost openssl
```

## Usage as Git Submodule

Add this repository as a submodule in your project:

```bash
git submodule add git@github.com:AirVan21/connector-network.git Dependencies/connector-network
git submodule update --init --recursive
```

### CMake Integration

In your project's `CMakeLists.txt`:

```cmake
# Add the submodule
add_subdirectory(Dependencies/connector-network)

# Link to your target
target_link_libraries(YourTarget PRIVATE connector_network)

# Ensure Boost and OpenSSL are available
find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)
target_link_libraries(YourTarget PRIVATE
    ${Boost_LIBRARIES}
    OpenSSL::SSL
    OpenSSL::Crypto
)
```

## API

### ConnectionSettings

```cpp
struct ConnectionSettings {
    std::string host;  // e.g., "api.example.com"
    std::string port;  // e.g., "443"
    std::string path;  // e.g., "/ws/v2" (default: "/")
};
```

### Callbacks

```cpp
struct Callbacks {
    std::function<void(const std::string&)> on_message;    // Received message
    std::function<void(const std::string&)> on_error;      // Error occurred
    std::function<void(bool)> on_connection;               // Connection state changed
};
```

### WssWorker

```cpp
// Create worker with io_context and callbacks
connectors::WssWorker worker(io_context, callbacks);

// Connect (returns future<bool>)
auto connected = worker.Connect(settings);

// Start receiving messages
worker.StartListening();

// Send message (returns future<bool>)
auto sent = worker.Send("{\"action\": \"subscribe\"}");

// Disconnect
worker.Disconnect();
```

## Example

```cpp
#include <WssWorker.h>
#include <boost/asio.hpp>
#include <iostream>

int main() {
    boost::asio::io_context io_context;

    connectors::Callbacks callbacks{
        .on_message = [](const std::string& msg) {
            std::cout << "Received: " << msg << std::endl;
        },
        .on_error = [](const std::string& err) {
            std::cerr << "Error: " << err << std::endl;
        },
        .on_connection = [](bool connected) {
            std::cout << (connected ? "Connected" : "Disconnected") << std::endl;
        }
    };

    connectors::WssWorker worker(io_context, callbacks);

    connectors::ConnectionSettings settings{
        .host = "api.example.com",
        .port = "443",
        .path = "/ws"
    };

    if (worker.Connect(settings).get()) {
        worker.StartListening();
        worker.Send(R"({"action": "ping"})");
        io_context.run();
    }

    return 0;
}
```

## Building the Example

The `example/` folder contains a sample application. To build it:

```bash
mkdir build && cd build
cmake .. -DBUILD_EXAMPLE=ON
cmake --build .
./connector_example
```

## Docker Development

Build and run the development container (all dependencies included):

```bash
docker build -t connector-network .
docker run -it -v $(pwd):/connector-network connector-network

# Inside container
mkdir build && cd build && cmake .. && cmake --build .
```

## License

Apache 2.0
