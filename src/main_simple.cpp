/**
 *
 * Simple http service without any optimization .
 *
 *
 *
 *
 *
 *
 */

#include <iostream>
#include <map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "HTTPServer.h"

int main_test(int argc, const char *argv[]) {
    std::cout << "Server started !" << std::endl;
    std::fstream cfile;


    cfile.open("server.config");
    if (!cfile.is_open()) {
        std::cout << "error open the config file ." << std::endl;
        exit(0);
    }
    std::map<std::string, std::string> config;
    std::string line;
    while (getline(cfile, line)) {
        if (line.rfind("#", 0) == 0)
            continue;

        int epos = line.find("=");
        config.insert(std::pair<std::string, std::string>(line.substr(0, epos), line.substr(epos + 1, line.length())));
    }
    cfile.close();
    std::cout << "finished read the config file ." << std::endl;
    int it_port = atoi(config["port"].c_str());


    // create hte socket .
    int socket_desc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in socket_address;
    memset(&socket_address, 0, sizeof(struct sockaddr_in));
    socket_address.sin_family = AF_INET;
    socket_address.sin_port = htons(it_port);
    socket_address.sin_addr.s_addr = INADDR_ANY;
    if (bind(socket_desc, (struct sockaddr *) &socket_address, sizeof(socket_address)) != 0) {
        std::cout << "Failed to bind to the address!" << std::endl;
        exit(0);
    }
    if (listen(socket_desc, SOMAXCONN) != 0) {
        std::cout << "Failed to put the socket in a listening state" << std::endl;
        exit(0);
    }


    // start the loop to accept the request;
    int accept_status;
    sockaddr_in socket_accept;
    int run_loop = 1;
    while (run_loop) {
        std::cout << "wait for next connection ." << std::endl;
        int address_size = sizeof(address_size);
        memset(&socket_accept, 0, address_size);
        accept_status = accept(socket_desc, (sockaddr *) &socket_accept, (socklen_t *) &address_size);
        fcntl(accept_status, F_SETFL, O_NONBLOCK);

        if (INVALID_SOCKET == accept_status) {
            exit(0);
        } else {
            std::cout << "client accept !" << std::endl;
            std::string response = "hello, world!";
            send(socket_desc, response.data(), response.length(), 0);
        }
        close(accept_status);
    }
    // end the loop;


    shutdown(socket_desc, SHUT_RDWR);
    close(socket_desc);
    std::cout << "socket server closed ." << std::endl;
    return 0;
}