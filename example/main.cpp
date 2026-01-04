#include <WssWorker.h>

#include <iostream>
#include <boost/asio.hpp>

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
