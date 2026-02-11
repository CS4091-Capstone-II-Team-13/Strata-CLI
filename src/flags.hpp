#ifndef FLAGS_HPP
#define FLAGS_HPP

#include <mutex>

// @brief using this type def to can pass function pointers
typedef int (*function_pointer)();

// @brief Singleton data struct which holds the current state of the program, determined by the flags
class FlagState {

    private:
        FlagState() {}
        static FlagState* instancePtr;

        // Mutex to ensure thread safety
        static mutex mtx;

    public:
        // Deleting the copy constructor to prevent copies
        FlagState(const FlagState& obj) = delete;

        // @brief returns the current instance of the FlagState
        static FlagState* getInstance() {
            if (instancePtr == nullptr) {
                lock_guard<mutex> lock(mtx);
                if (instancePtr == nullptr) {
                    instancePtr = new FlagState();
                }
            }
            return instancePtr;
        }
};

#endif