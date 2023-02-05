#ifndef VCS_H
#define VCS_H

#include <string>
#include <unordered_map>
#include <iostream>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstring>
#include <dirent.h>
#include <sstream>
#include <unistd.h>
#include <sys/stat.h>

using namespace std;

bool vcs_init();
bool vcs_commit(const string &message);
bool vcs_log();

unordered_map<string, string> create_snapshot();

#endif