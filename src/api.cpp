#include "include/api.h"
#include <iostream>

APIConnector& APIConnector::getInstance() {
    static APIConnector instance;
    return instance;
}
