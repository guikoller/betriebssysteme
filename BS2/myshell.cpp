#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <unordered_map>

using namespace std;

struct ProcessInfo {
    pid_t pid;
    string command;
};

// Funktion zum Aufteilen eines Strings in Wörter
vector<string> splitInput(const string& input) {
    vector<string> tokens;
    stringstream ss(input);
    string token;
    
    while (ss >> token) {
        tokens.push_back(token);
    }
    
    return tokens;
}

int main() {
    string commandLine;
    unordered_map<pid_t, ProcessInfo> backgroundProcesses;

    while (true) {
        cout << "myshell> ";
        getline(cin, commandLine); // Eingabe lesen

        // Befehl zum Beenden der Shell
        if (commandLine == "exit") {
            cout << "Exiting myshell..." << endl;
            // Prozesse im Hintergrund beenden, falls noch welche laufen
            for (auto& pair : backgroundProcesses) {
                kill(pair.second.pid, SIGKILL);
            }
            break;
        }

        // Eingabe aufteilen in Befehlsname und Argumente
        vector<string> args = splitInput(commandLine);
        if (args.empty()) {
            continue; // Wenn keine Eingabe vorhanden ist, erneut auffordern
        }

        // Prüfen, ob der Befehl im Hintergrund ausgeführt werden soll
        bool runInBackground = false;
        if (!args.empty() && args.back() == "&") {
            runInBackground = true;
            args.pop_back(); // Entferne das "&" aus den Argumenten
        }

        // Befehlsname und Argumente vorbereiten
        const char* cmd = args[0].c_str(); // Erster Teil ist der Befehlsname
        vector<const char*> cmdArgs; // Argumente für execvp
        for (size_t i = 1; i < args.size(); ++i) {
            cmdArgs.push_back(args[i].c_str());
        }
        cmdArgs.push_back(nullptr); // Letztes Argument muss Nullpointer sein

        // Kindprozess erstellen
        pid_t pid = fork();
        if (pid < 0) {
            cerr << "Fork failed" << endl;
            exit(1);
        } else if (pid == 0) {
            // Im Kindprozess den Befehl ausführen
            execvp(cmd, const_cast<char* const*>(cmdArgs.data()));
            cerr << "Exec failed for command: " << cmd << endl;
            exit(1);
        } else {
            // Im Elternprozess
            if (runInBackground) {
                // Prozess läuft im Hintergrund
                cout << "Background process started with PID " << pid << endl;
                backgroundProcesses[pid] = {pid, args[0]}; // Prozessinformation speichern
            } else {
                // Prozess läuft im Vordergrund, warten bis er beendet ist
                int status;
                waitpid(pid, &status, 0);
            }
            
            // Überprüfen, ob im Hintergrund gestartete Prozesse beendet sind
            for (auto it = backgroundProcesses.begin(); it != backgroundProcesses.end(); ) {
                pid_t bgPid = it->first;
                int status;
                pid_t result = waitpid(bgPid, &status, WNOHANG);
                if (result > 0) {
                    cout << "Background process " << bgPid << " (" << it->second.command << ") finished." << endl;
                    it = backgroundProcesses.erase(it); // Prozess aus der Liste entfernen
                } else if (result == 0) {
                    // Prozess läuft noch
                    ++it;
                } else {
                    // Fehler bei waitpid
                    cerr << "Error waiting for background process " << bgPid << endl;
                    it = backgroundProcesses.erase(it); // Prozess aus der Liste entfernen
                }
            }
        }
    }

    return 0;
}

