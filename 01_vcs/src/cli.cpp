#include "cli.h"

void print_help() {
  cout << "Usage: ./vcs [command] [args]\n";
  cout << "Available commands:\n";
  cout << "  init                   Create a new VCS repository\n";
  cout << "  commit [message]       Save changes to the repository\n";
  cout << "  log                    Show the commit history\n";
  cout << "  status                 Show the current status of the repository\n";
  cout << "  tag [tag name]         Assign the tag for this snapshot\n";
  cout << "  rollback [snapshot id] Rollback to snapshot\n";
}

bool handle_init_command(const vector<string>& args) {
  if (!args.empty()) {
    cerr << "Error: init command does not take any arguments." << endl;
    return false;
  }

  if (!vcs_init()) {
    cerr << "Error: repository already exists." << endl;
    return false;
  }

  cout << "Repository initialized successfully." << endl;
  return true;
}

bool handle_commit_command(const vector<string>& args) {
  if (args.empty()) {
    cerr << "Error: commit command requires a message argument." << endl;
    return false;
  }

  return vcs_commit(args[0]);
}

bool handle_diff_command(const vector<string>& args) {
  if (!args.empty()) {
    cerr << "Error: diff command does not take any arguments." << endl;
    return false;
  }

  cout << "Displaying differences between current state and latest commit" << endl;
  return true;
}

bool handle_log_command(const vector<string>& args) {
  if (!args.empty()) {
    cerr << "Error: log command does not take any arguments." << endl;
    return false;
  }

  vcs_log();
  return true;
}

bool handle_status_command(const vector<string>& args) {
  if (!args.empty()) {
    cerr << "Error: status command does not take any arguments." << endl;
    return false;
  }

  vcs_status();
  return true;
}

bool handle_tag_command(const vector<string>& args) {
  if (args.empty()) {
    cerr << "Error: tag command requires a tag name argument." << endl;
    return false;
  }

  if (vcs_tag(args[0])) {
    cout << "Tag '" << args[0] << "' created successfully." << endl;
    return true;
  } else {
    cerr << "Error: could not create tag '" << args[0] << "'." << endl;
    return false;
  }
}

bool handle_rollback_command(const vector<string>& args) {
  if (args.empty()) {
    cerr << "Error: rollback command requires a snapshot id argument." << endl;
    return false;
  }

  int snapshot_id = stoi(args[0]);

  if (vcs_rollback(snapshot_id)) {
    cout << "Rolled back to snapshot " << snapshot_id << endl;
    return true;
  } else {
    cerr << "Error: failed to rollback to snapshot " << snapshot_id << endl;
    return false;
  }
}