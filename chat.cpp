
#include <iostream>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

typedef websocketpp::client<websocketpp::config::asio_client> client;

void on_message(websocketpp::connection_hdl hdl, client::message_ptr msg) {
    std::cout << "New message: " << msg->get_payload() << std::endl;
}

int main() {
    client c;
    string message;
    c.init_asio();
    websocketpp::connection_hdl hdl;

    auto con = c.get_connection("ws://localhost:9002", websocketpp::lib::error_code());
    c.connect(con);

    while (true) {
        cout << "Enter message: ";
        getline(cin, message);
        con->send(message);
    }

    return 0;
}
