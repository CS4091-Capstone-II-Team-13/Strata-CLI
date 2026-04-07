#pragma once

#include <httplib.h>
#include <string>
#include <vector>

// tells httplib to use SSL
#define CPPHTTPLIB_OPENSSL_SUPPORT

class APIConnector {
    public:
    // Singleton access method
    static APIConnector& getInstance();
    APIConnector(const APIConnector&) = delete;
    void operator=(const APIConnector&) = delete;

    // API functions
    

    private:
        APIConnector();

        httplib::Client cli;
        std::string api_token = "YOUR_SECURE_TOKEN";
};