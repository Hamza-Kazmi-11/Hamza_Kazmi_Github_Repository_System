#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include"helper.cpp"

using namespace std;
Helper* g;
string username, password;
void main_page(string);
void register_login();
void into_rp(string);
int main()
{
    g = new Helper();
    register_login();
    delete g;
    return 0;
}
void into_rp(string rep)
{
    int option;
    do
    {
        cout << "\n\nMenu" << endl;
        cout << "1. Add commit" << endl;
        cout << "2. Show commits" << endl;
        cout << "0. Return" << endl;
        cout << "Enter your choice: ";
        cin >> option;
        if (option == 1)
        {
            string commit;
            cout << "Enter new commit" << endl;
            cin >> commit;
            g->add_commit(username, rep, commit);
            g->add_commit_in_file(username, rep, commit);
        }
        else if (option == 2)
        {
            g->view_commit(username, rep);
        }
        else if (option == 0) {
            break;
        }

    } while (option);
}
void main_page(string username)
{
    int option;
    do
    {
        cout << "1. Show Reps" << endl;
        cout << "2. Get into Rep" << endl;
        cout << "3. Add Rep" << endl;
        cout << "4. Delete Rep" << endl;
        cout << "5. See Friends" << endl;
        cout << "6. See Reps of another person" << endl;
        cout << "7. See Friends of another Person" << endl;
        cout << "8. Follow a Person" << endl;
        cout << "0. Exit" << endl;
        cin >> option;

        if (option == 1)
        {
            g->show_all_repos(username);
        }
        if (option == 2)
        {
            string rep;

            cout << "Enter Rep name" << endl;
            cin >> rep;
            if (g->Search_repo(username, rep))
            {
                into_rp(rep);
            }

        }
        else if (option == 3)
        {
            string Rep;
            cout << "Enter Rep name to add:";
            cin >> Rep;
            int x;
            cout << "Enter 0  for private and 1 for public:";
            cin >> x;
            if (x != 0 && x != 1)
            {
                cout << "Error while adding" << endl;
                continue;
            }
            g->Add_repo(username, Rep, x);
            g->Add_repo_in_file(username, Rep, x);
        }
        else if (option == 4)
        {
            string Rep;
            cout << "Enter Rep name to delete:";
            cin >> Rep;
            g->Del_repo(username, Rep);
            g->Delete_repo_in_file(username, Rep);
        }
        else if (option == 5)
        {
            g->show_friends(username);
            g->show_friends_from_file(username);
        }

        else if (option == 6)
        {
            string name;
            cout << "Enter name of the person:";
            cin >> name;
            g->show_public_repos(name);
        }
        else if (option == 7)
        {
            string name;
            cout << "Enter name of the person:";
            cin >> name;
            g->show_friends(name);
            g->show_friends_from_file(name);
        }
        else if (option == 8)
        {
            string name;
            cout << "Enter name of the person:";
            cin >> name;
            g->Add_friend_into_file(username, name);
        }
        else if (option == 0) {
            break;
        }

    } while (true);

}
void register_login()
{

    int option;
    do
    {
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;
        cin >> option;
        if (option == 1) {
            cout << "Enter user name:";
            cin >> username;
            cout << "Enter Password:";
            cin >> password;
            if (g->login(username, password).compare("-12") == 0)
            {
                cout << "Wrong username and password" << endl;
            }
            else
            {
                cout << "Login successful" << endl;
                main_page(username);
            }
        }
        else if (option == 2) {
            cout << "Enter user name:";
            cin >> username;
            cout << "Enter Password:";
            cin >> password;
            g->Register_User(username, password);
            cout << "Register Successfull" << endl;

        }
        else if (option == 3) {
            break;
        }
    } while (true);
}