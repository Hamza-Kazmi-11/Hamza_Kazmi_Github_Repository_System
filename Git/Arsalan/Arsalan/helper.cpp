#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include"data_structures.cpp"
using namespace std;
class Helper
{
public:
    Hashmap *users;
    Graph *Friend_structure = new Graph(100);
    Helper()
    {
        Add_users_from_csv();
        Add_repo_from_csv();
        Add_commits_from_csv();
        Add_friends_from_csv();
    }

    void show_all_repos(string username)
    {
        users->print_repos(username,1);
    }
    void show_public_repos(string username)
    {
        users->print_repos(username,0);
    }

    void Add_friend(string username,string frend)
    {
        Friend_structure->addEdge(username ,frend);
    }
    void Add_friends_from_csv()
    {
        ifstream file("friends.csv");
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
        string name;
        getline(lineStream, name, ',');
        string friends;
        while (std::getline(lineStream, friends, ',')) 
        {
            if (friends != "\n") 
            {
                Friend_structure->addEdge(name,friends);
            }
        }
    }
    }
    }
    void show_friends(string username)
    {
        Friend_structure->printConnections(username);
    }

void Add_commits_from_csv()
{

    ifstream file("commit.csv");
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
        string rep;
        getline(lineStream, rep, ',');
        // cout << "Username: " << username << std::endl;
        string commits;
        while (std::getline(lineStream, commits, ',')) 
        {
            if (commits != "\n") 
            {
                // std::cout << "Repetition: " << reps << std::endl;
                users->Insert_commits(username,rep,commits);
            }
        }
    }
    }
}

void add_commit(string username,string rep,string commits)
{
    users->Insert_commits(username,rep,commits);
}
void view_commit(string name, string rep)
{
    users->View_commits(name,rep);
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
        if(users->get(username) == NULL)
        {
            cout << "No username found"<<endl;
            return;
        }
        string reps;
        while (std::getline(lineStream, reps, ',')) 
        {
            if (reps != "\n") 
            {
                // std::cout << "Repetition: " << reps << std::endl;
                users->Insert_Repo(username,reps,1);
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
        users->insert(username, password );
        Friend_structure->addPerson(username);
    }
    file.close();
}

int Add_repo(string username,string Rep,bool status)
{

     if(users->get(username) == NULL)
        {
            cout << "No username found"<<endl;
            return 0;
        }  
        return users->Insert_Repo(username,Rep,status); 

}
int Del_repo(string username,string Rep)
{

     if(users->get(username) == NULL)
        {
            cout << "No username found"<<endl;
            return 0;
        }  
        return users->Delete_Repo(username,Rep); 

}
int Search_repo(string username,string Rep)
{

     if(users->get(username) == NULL)
        {
            cout << "No username found"<<endl;
            return 0;
        }  
        return users->Search_Repo(username,Rep); 

}
string login(string user_name,string password)
{
    string* x = users->get(user_name);

    if(x != nullptr && x->compare(password) == 0)
    {
        return user_name;
    }
    return "-12";
}
void Register_User(string username,string password) {
    string data = username+","+password+"\n";
    ofstream file("user.csv", std::ios::app);
    if (!file) 
    {
        cout << "Failed to  user csv open the file." << endl;
        return;
    }
    file << data << endl;
    file.close();
    users->insert(username,password);
}


};