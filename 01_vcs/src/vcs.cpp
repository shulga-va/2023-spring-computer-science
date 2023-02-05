#include "vcs.h"

namespace fs = filesystem;

bool vcs_init() {
  fs::path archive_dir = ".archive";
  if (fs::exists(archive_dir) && fs::is_directory(archive_dir)) {
    return false;
  }

  fs::create_directory(archive_dir);
  cout << "Created directory " << archive_dir << endl;

  vcs_commit("Init commit");
  return true;
}

int get_next_snapshot_id() {
  int snapshot_id = 0;
  string snapshot_dir = ".archive/snapshot_" + to_string(snapshot_id);
  while (fs::exists(snapshot_dir)) {
    snapshot_id++;
    snapshot_dir = ".archive/snapshot_" + to_string(snapshot_id);
  }
  return snapshot_id;
}

void create_snapshot_directory(int snapshot_id) {
  string snapshot_dir = ".archive/snapshot_" + to_string(snapshot_id);
  fs::create_directory(snapshot_dir);
}

bool vcs_commit(const string& message) {
  int snapshot_id = get_next_snapshot_id();
  string snapshot_dir = ".archive/snapshot_" + to_string(snapshot_id);
  create_snapshot();

  auto commit_log_file_path = fs::path(snapshot_dir) / string("commit.log");
  ofstream commit_log_file(commit_log_file_path);
  commit_log_file << message << '\n';
  commit_log_file.close();
  if(snapshot_id != 0)
    cout << "Committing changes with message: " << message << endl;
  return true;
} 

void copy_from_to(const fs::path &src_path, const fs::path &dst_path) {
  ifstream src(src_path, ios::binary);
  ofstream dst(dst_path, ios::binary);
  dst << src.rdbuf();
}

string compute_file_hash(const fs::path &path) {
  ifstream src(path, ios::binary);
  src.clear();
  src.seekg(0, ios::beg);
  istreambuf_iterator<char> src_begin(src);
  istreambuf_iterator<char> src_end;
  string data(src_begin, src_end);
  hash<string> hash_fn;
  size_t hash_value = hash_fn(data);

  stringstream ss;
  ss << hex << setfill('0') << setw(sizeof(size_t) * 2) << hash_value;
  return ss.str();
}

unordered_map<string, string> create_snapshot() {
  int snapshot_id = get_next_snapshot_id();
  create_snapshot_directory(snapshot_id);
  string snapshot_dir = ".archive/snapshot_" + to_string(snapshot_id);
  fs::create_directory(snapshot_dir);

  unordered_map<string, string> file_hashes;

  for (const auto &entry : fs::recursive_directory_iterator(".")) {
    if (!fs::is_directory(entry.path())) {
      copy_from_to(entry.path(), snapshot_dir / entry.path().filename());
      file_hashes[entry.path().string().substr(2)] = compute_file_hash(entry.path());
    }
  }
  auto hashes_log_file_path = fs::path(snapshot_dir) / string("hashes.log");
  ofstream hashes_log_file(hashes_log_file_path);
  for (const auto &[file, hash] : file_hashes) {
    hashes_log_file << file << ' ' << hash << '\n';
  }
  hashes_log_file.close();

  return file_hashes;
}

bool vcs_log() {
  cout << "Log message" << endl;

  return true;
}