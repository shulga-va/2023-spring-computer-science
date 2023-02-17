#ifndef CLI_H
#define CLI_H

#include "vcs.h"

void print_help();
bool handle_init_command(const vector<string>& args);
bool handle_commit_command(const vector<string>& args);
bool handle_diff_command(const vector<string>& args);
bool handle_log_command(const vector<string>& args);
bool handle_status_command(const vector<string>& args);
bool handle_tag_command(const vector<string>& args);
bool handle_rollback_command(const vector<string>& args);

#endif