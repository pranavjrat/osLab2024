#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main() {
    pid_t child_pid = fork();

    if (child_pid == -1) {
        // Fork failed
        cerr << "Fork failed" << endl;
        return 1;
    } else if (child_pid > 0) {
        // Parent process
        cout << "Parent process. Child PID: " << child_pid << endl;
        // Sleep for a while to allow the child process to become a zombie
        sleep(10);
        // Parent process terminates, but child's exit status will not be collected
    } else {
        // Child process
        cout << "Child process" << endl;
        // Child process exits immediately
        exit(0);
    }

    return 0;
}
