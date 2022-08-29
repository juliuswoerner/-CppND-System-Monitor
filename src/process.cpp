#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;
using std::stof;

// TODO: Return this process's ID

Process::Process(int pid){
    Process::SetPid(pid);
}

void Process::SetPid(int pid) { Process::pid_ = pid; }

int Process::Pid() { return pid_; }

void Process::Hertz() {
    string line, attribute1, attribute2, attribute3, value;
    int count = 0;
    std::ifstream stream("/proc/cpuinfo");
    while (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream >> attribute1 >> attribute2 >> attribute3 >> value;
        if(attribute1 == "cpu" && attribute2 == "MHz"){
            hertz_ = 1000000 * stof(value);
            break;
        }
        count += 1;
        if(count>40){ 
           break; 
           }
    }
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
    float total_time, utime, stime, cutime, cstime, starttime, cpu_usage;
    long uptime, seconds;
    Process::Hertz();
    string v[23], line;
    std::ifstream stream("/proc/" + std::to_string(pid_) + "/stat");
    while (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream >> v[0] >> v[1] >> v[2] >> v[3] >> v[4] >> v[5] >> v[6] >> v[7] >> v[8] >> v[9] >> v[10] >> v[11] >> v[12] >> v[13] >> v[14] >> v[15] >> v[16] >> v[17] >> v[18] >> v[19] >> v[20] >> v[21] >> v[22] ;
        utime = stof(v[13]);
        stime = stof(v[14]);
        cutime = stof(v[15]);
        cstime = stof(v[16]);
        starttime = stof(v[21]);
        total_time = utime + stime + cutime + cstime;
        uptime = UpTime();
        seconds = uptime - (starttime / hertz_);
        cpu_usage = ((total_time / hertz_) / seconds);
        return cpu_usage;
    }
    return 0.0; 
}

// TODO: Return the command that generated this process
string Process::Command() { 
    string command = LinuxParser::Command(pid_);
    if(command.length() > 50){
        command = command.substr(0,49) + "...";
    }
    return command; 
    }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
// TODO: Check what to compare
bool Process::operator<(Process const& a) const { 
    if(Process::pid_ < a.pid_) { return true; }
    else { return false; } 
}