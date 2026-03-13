#pragma once
#include <string>
#include <cstdlib>
#include <ctime>
#include "../Queue/queue.hpp"

//COLORS!!!!
inline const string RESET = "\033[0m";
inline const string RED = "\033[31m";
inline const string GREEN = "\033[32m";
inline const string YELLOW = "\033[33m";
inline const string BLUE = "\033[34m";
inline const string MAGENTA = "\033[35m";
inline const string CYAN = "\033[36m";
inline const string WHITE = "\033[37m";
inline const string BRED = "\033[91m";
inline const string BGREEN = "\033[92m";
inline const string BYELLOW = "\033[93m";
inline const string BBLUE = "\033[94m";
inline const string BMAGENTA = "\033[95m";
inline const string BCYAN = "\033[96m";
//End of Colors

using std::string;

class SIM
{
private:
    QUEUE _expressLane;
    QUEUE _normalLane;

    int _CustomerCount;

    int _expressNextArrival;
    int _normalNextArrival;

    int _expressServiceCountdown;
    int _normalServiceCountdown;

    static int randRange(int low, int high);
    static string randomItem();

    void arriveExpress(int elapsed);
    void arriveNormal(int elapsed);
    void processExpress(int elapsed);
    void processNormal(int elapsed);

public:
    SIM();
    void run(int minutes);
};