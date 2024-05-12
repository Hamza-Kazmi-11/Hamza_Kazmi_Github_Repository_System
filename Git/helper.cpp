#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include"data_structures.cpp"
using namespace std;
class Helper
{
public:
    Hashmap* users;
    Graph* Friend_structure = new Graph(100);
    Helper()
    {
        Add_users_from_csv();
        Add_repo_from_csv();
        Add_commits_from_csv();
        Add_friends_from_csv();
    }

    void add_commit_in_file(const string& username, const string& rep, const string& commit) {
        ofstream outFile("commit.csv", ios::app); // Open the file in append mode

        if (outFile.is_open()) {
            outFile << username << "," << rep << "," << commit << "\n"; // Append new commit to file
            outFile.close();
            cout << "Commit added successfully to commit.csv" << endl;
        }
        else {
            cout << "Error: Unable to open commit.csv for writing" << endl;
        }
    }

    void show_all_repos(string username)
    {
        users->print_repos(username, 1);
    }
    void show_public_repos(string username)
    {
        users->print_repos(username, 0);
    }

    void Add_friend(string username, string frend)
    {
        Friend_structure->addEdge(username, frend);
    }
    void Add_friends_from_csv()
    {
        ifstream file("followers.csv");
        if (!file)
        {
            cout << "Failed to open user csv the file." << endl;
            return;
        }
        string line;
        while (getline(file, line))
        {
            istringstream ss(line);
            string line;

            while (getline(ss, line))
            {
                istringstream lineStream(line);
                string name;
                getline(lineStream, name, ',');
                string friends;
                while (std::getline(lineStream, friends, ','))
                {
                    if (friends != "\n")
                    {
                        Friend_structure->addEdge(name, friends);
                    }
                }
            }
        }
    }

    void Add_friend_into_file(const string& name, const string& friendName) {
        ofstream outFile("followers.csv", ios::app); // Open the file in append mode

        if (outFile.is_open()) {
            outFile << name << "," << friendName << "\n"; // Append friend relationship to file
            outFile.close();
            cout << "Friend added successfully: " << name << " follows " << friendName << endl;
        }
        else {
            cout << "Error: Unable to open followers.csv for writing" << endl;
        }
    }

    void show_friends(string username)
    {
        Friend_structure->printConnections(username);
    }
    
    void show_friends_from_file(const string& username) {
        ifstream inFile("followers.csv"); // Open the file for reading

        if (!inFile) {
            cout << "Error: Unable to open followers.csv for reading" << endl;
            return;
        }

        string line;
        bool found = false;

        while (getline(inFile, line)) {
            istringstream ss(line);
            string user, follower;

            if (getline(ss, user, ',') && getline(ss, follower, ',')) {
                if (user == username) {
                    found = true;
                    cout << follower << " "; // Print the follower
                }
            }
        }

        inFile.close();

        if (found) {
            cout << endl;
        }
        else {
            cout << "No followers found for " << username << endl;
        }
    }

    void Add_commits_from_csv()
    {

        ifstream file("commit.csv");
        if (!file)
        {
            cout << "Failed to open user csv the file." << endl;
            return;
        }
        string line;
        while (getline(file, line))
        {
            istringstream ss(line);
            string line;

            while (getline(ss, line))
            {
                istringstream lineStream(line);
                string username;
                getline(lineStream, username, ',');
                // cout << "Username: " << username << std::endl;
                string rep;
                getline(lineStream, rep, ',');
                // cout << "Username: " << username << std::endl;
                string commits;
                while (getline(lineStream, commits, ','))
                {
                    if (commits != "\n")
                    {
                        // std::cout << "Repetition: " << reps << std::endl;
                        users->Insert_commits(username, rep, commits);
                    }
                }
            }
        }
    }

    void add_commit(string username, string rep, string commits)
    {
        users->Insert_commits(username, rep, commits);
    }
    void view_commit(string name, string rep)
    {
        users->View_commits(name, rep);
    }
    void Add_repo_from_csv()
    {

        ifstream file("Repos.csv");
        if (!file)
        {
            cout << "Failed to open user cs the file." << endl;
            return;
        }
        string line;
        while (getline(file, line))
        {
            istringstream ss(line);
            string line;

            while (getline(ss, line))
            {
                istringstream lineStream(line);
                string username;
                getline(lineStream, username, ',');
                // cout << "Username: " << username << std::endl;
                if (users->get(username) == NULL)
                {
                    cout << "No username found" << endl;
                    return;
                }
                string reps;
                while (std::getline(lineStream, reps, ','))
                {
                    if (reps != "\n")
                    {
                        // std::cout << "Repetition: " << reps << std::endl;
                        users->Insert_Repo(username, reps, 1);
                    }
                }
            }
        }
    }
    void Add_users_from_csv()
    {
        users = new Hashmap();
        ifstream file("user.csv");
        if (!file) {
            cout << "Failed to open user cs the file." << endl;
            return;
        }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string username, password;
            getline(ss, username, ',');
            getline(ss, password, ',');
            users->insert(username, password);
            Friend_structure->addPerson(username);
        }
        file.close();
    }

    void Add_repo_in_file(const string& username, const string& Rep, int x) {
        ofstream outFile("Repos.csv", ios::app); // Open the file in append mode

        if (outFile.is_open()) {
            outFile << username << "," << Rep << "," << x << "\n"; // Append repository data to file
            outFile.close();
            cout << "Repository added successfully to Repos.csv" << endl;
        }
        else {
            cout << "Error: Unable to open Repos.csv for writing" << endl;
        }
    }

    int Add_repo(string username, string Rep, bool status) {
        if (users->get(username) == NULL) {
            cout << "No username found" << endl;
            return 0;
        }
        return users->Insert_Repo(username, Rep, status);
    }

    int Del_repo(string username, string Rep) {
        if (users->get(username) == NULL)
        {
            cout << "No username found" << endl;
            return 0;
        }
        return users->Delete_Repo(username, Rep);
    }

    void Delete_repo_in_file(const string& username, const string& Rep) {
        ifstream inFile("Repos.csv"); // Open the file for reading
        ofstream outFile("temp.csv"); // Open a temporary file for writing

        if (!inFile || !outFile) {
            cout << "Error: Unable to open file(s) for processing" << endl;
            return;
        }

        string line;
        bool repoDeleted = false;

        while (getline(inFile, line)) {
            istringstream ss(line);
            string user, repo, visibility;

            if (getline(ss, user, ',') && getline(ss, repo, ',') && getline(ss, visibility, ',')) {
                if (user == username && repo == Rep) {
                    repoDeleted = true;
                    continue; // Skip writing this line to the temp file (effectively deleting it)
                }

                // Write the line to the temp file
                outFile << user << "," << repo << "," << visibility << "\n";
            }
        }

        inFile.close();
        outFile.close();

        // Rename temp file to Repos.csv if a repository was deleted
        if (repoDeleted) {
            remove("Repos.csv");
            rename("temp.csv", "Repos.csv");
            cout << "Repository deleted successfully from Repos.csv" << endl;
        }
        else {
            remove("temp.csv"); // Remove temp file if no changes were made
            cout << "Repository not found in Repos.csv" << endl;
        }
    }

    int Search_repo(string username, string Rep) {
        if (users->get(username) == NULL) {
            cout << "No username found" << endl;
            return 0;
        }
        return users->Search_Repo(username, Rep);
    }

    string login(string user_name, string password) {
        string* x = users->get(user_name);
        if (x != nullptr && x->compare(password) == 0) {
            return user_name;
        }
        return "-12";
    }

    void Register_User(string username, string password) {
        string data = username + "," + password + "\n";
        ofstream file("user.csv", ios::app);
        if (!file) {
            cout << "Failed to  user csv open the file." << endl;
            return;
        }
        file << data << endl;
        file.close();
        users->insert(username, password);
    }
};