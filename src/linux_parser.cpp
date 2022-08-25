#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"
#include "system.h"
#include "process.h"
#include "processor.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  float max_memory = 0.0, free_memory = 0.0;
  string attribute, value, line;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  while (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> attribute >> value;
    if(attribute == "MemTotal:"){
      max_memory = stof(value);
    }
    else if(attribute == "MemFree:"){
      free_memory = stof(value);
    }
    else if(max_memory != 0.0 && free_memory != 0.0){ return 1.0 - (free_memory / max_memory); }
  }
  return 0.0; 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  long up_time;
  string line, start, end;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> up_time;
  }
  return up_time; 
  }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  vector<string> cpu_utilizations;
  string cpu[5]={"","","","",""};
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> cpu[0] >> cpu[1] >> cpu[2] >> cpu[3] >> cpu[4];
    for(int i=1; i<5; i++){
      cpu_utilizations.push_back(cpu[i]);
    }
    return cpu_utilizations;
  }
  return cpu_utilizations; 
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string attribute, value, line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  while (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> attribute >> value;
    if(attribute == "processes"){
      return stoi(value);
    }
  }
  return 0; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string attribute, value, line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  while (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> attribute >> value;
    if(attribute == "procs_running"){
      return stoi(value);
    }
  }
  return 0; 
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  string command, line;
  std::ifstream stream(kProcDirectory + "/" + std::to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> command;
  }
  return command; 
  }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string attribute, v[23], line, key, memStr;
  int mem;
  std::ifstream stream(kProcDirectory + "/" + std::to_string(pid) + kStatFilename);
  while (stream.is_open()) {
    std::cout << "check 1" << std::endl;
    std::getline(stream, line);
    std::cout << "check 2" << std::endl;
    std::istringstream linestream(line);
    std::cout << "check 3" << std::endl;
    linestream >> v[0] >> v[1] >> v[2] >> v[3] >> v[4] >> v[5] >> v[6] >> v[7] >> v[8] >> v[9] >> v[10] >> v[11] >> v[12] >> v[13] >> v[14] >> v[15] >> v[16] >> v[17] >> v[18] >> v[19] >> v[20] >> v[21] >> v[22] ;
    std::cout << "check 4" << std::endl;
    memStr = v[22];
    std::cout << "check 5" << std::endl;
    mem = stoi(memStr)/1024;
    std::cout << "check 6" << std::endl;
    memStr = std::to_string(mem);
    std::cout << "check 7" << std::endl;
    return memStr;
  }

  return ""; 
  }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string attribute, value, line;
  std::ifstream stream(kProcDirectory + "/" + std::to_string(pid) + kStatusFilename);
  while (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> attribute >> value;
    if(attribute == "Uid:"){
      return value;
    }
  }
  return std::to_string(pid); 
  }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string line, name, temp, x, id;
  string uid = Uid(pid);
  std::ifstream stream(kPasswordPath);
  while (std::getline(stream, line)) {
    std::replace(line.begin(), line.end(), ':', ' ');
    std::istringstream linestream(line);

    linestream >> temp >> x >> id;
    if(id == uid) {
      name = temp;
      return name;
    }
  }
  return "dummy"; 
  }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  string attribute, v[23], line;
  std::ifstream stream(kProcDirectory + "/" + std::to_string(pid) + kStatFilename);
  while (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> v[0] >> v[1] >> v[2] >> v[3] >> v[4] >> v[5] >> v[6] >> v[7] >> v[8] >> v[9] >> v[10] >> v[11] >> v[12] >> v[13] >> v[14] >> v[15] >> v[16] >> v[17] >> v[18] >> v[19] >> v[20] >> v[21] >> v[22] ;
    long time = UpTime() - stol(v[21]);
    return time;
  }
  return 0; 
 }
