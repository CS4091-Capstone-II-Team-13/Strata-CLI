#include "include/api.h"
#include <nodepp/nodepp.h>
#include <nodepp/http.h>

using namespace nodepp;

void StrataAPI::uploadBinary(const std::string& filepath) {

    on_main([filepath](){
        
    });
}

void StrataAPI::startEventLoop() {
    // start the nodepp engine
    nodepp::on_main([](){
        console::log("Node++ Engine Active.");
    });
}