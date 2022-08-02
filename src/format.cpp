#include <string>

#include "format.h"

using std::string;

string Format::ConvertToDoubleDigits(int number){
    if(number < 10) { return "0" + std::to_string(number); }
    else { return std::to_string(number); }
}
// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds[[maybe_unused]]) { 
    string time = "";
    int hours = seconds / 3600;
    seconds = seconds - hours * 3600;
    int minutes = seconds / 60;
    seconds = seconds - minutes * 60;
    time = Format::ConvertToDoubleDigits(hours) + ";" + Format::ConvertToDoubleDigits(minutes) + ";" + Format::ConvertToDoubleDigits(seconds);
    return time; 
}