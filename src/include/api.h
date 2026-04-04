#pragma once

#include <nodepp/nodepp.h>
#include <string>

namespace StrataAPI {
    // Standard synchronous-looking wrappers for your Managers to call
    void uploadBinary(const std::string& filepath);
    void fetchRemoteConfig(const std::string& url);
    
    // Internal: Starts the Node++ event loop if needed
    void startEventLoop();
}