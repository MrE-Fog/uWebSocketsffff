#include <iostream>
#include <cassert>

#include "../src/HttpParser.h"

int main() {
    unsigned char data[] = {0x47, 0x45, 0x54, 0x20, 0x2f, 0x20, 0x48, 0x54, 0x54, 0x50, 0x2f, 0x31, 0x2e, 0x31, 0xd, 0xa, 0x61, 0x73, 0x63, 0x69, 0x69, 0x3a, 0x20, 0x74, 0x65, 0x73, 0x74, 0xd, 0xa, 0x75, 0x74, 0x66, 0x38, 0x3a, 0x20, 0xd1, 0x82, 0xd0, 0xb5, 0xd1, 0x81, 0xd1, 0x82, 0xd, 0xa, 0x48, 0x6f, 0x73, 0x74, 0x3a, 0x20, 0x31, 0x32, 0x37, 0x2e, 0x30, 0x2e, 0x30, 0x2e, 0x31, 0xd, 0xa, 0x43, 0x6f, 0x6e, 0x6e, 0x65, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x3a, 0x20, 0x63, 0x6c, 0x6f, 0x73, 0x65, 0xd, 0xa, 0xd, 0xa, 'E', 'E'};
    int size = sizeof(data) - 2;
    void *user = nullptr;
    void *reserved = nullptr;

    uWS::HttpParser httpParser;

    void *returnedUser = httpParser.consumePostPadded((char *) data, size, user, reserved, [reserved](void *s, uWS::HttpRequest *httpRequest) -> void * {

        std::cout << httpRequest->getMethod() << std::endl;

        // This fails on anything other than Linux?
        assert(httpRequest->getHeader("utf8").length());

        /* Return ok */
        return s;

    }, [](void *user, std::string_view data, bool fin) -> void * {

        /* Return ok */
        return user;

    }, [](void *user) -> void * {

        /* Return break */
        return nullptr;
    });

    std::cout << "HTTP DONE" << std::endl;

}