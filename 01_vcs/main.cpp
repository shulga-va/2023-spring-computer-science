#include "src/cli.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    cerr << "Error: missing command" << endl;
    return 1;
  }

  string command = argv[1];
  
  if (command == "-h") {
    print_help();
    return 0;
  } 

  vector<string> args(argv + 2, argv + argc);

  if (command == "init") {
    handle_init_command(args);
  } else if (command == "commit") {
    handle_commit_command(args);
  } else if (command == "log") {
    handle_log_command(args);
  } else if (command == "status") {
    handle_status_command(args); 
  } else 
  {
    cerr << "Error: unknown command: " << command << endl;
    return 1;
  }

  return 0;
}