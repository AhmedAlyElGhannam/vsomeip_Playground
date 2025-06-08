#include "server_simple.hpp"

int main(void)
{
    server _server;
    _server.init();
    _server.start();
    _server.stop();
}