#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include"helper.cpp"

using namespace std;
Helper *g;
string username,password;
void main_page(string);
void register_login();
void into_rp(string);
int main()
{
    g = new Helper(); 
    register_login();
    main_page(username);
    return 0;
}
void into_rp(string rep)
{
    int l;
    do 
    {
        cout << "1-Add commit"<<endl;;
        cout << "2-show commits"<<endl;;
        cout << "3-fork"<<endl;
        cout << "0-back"<<endl;
        cin >> l;
        if(l == 1)
        {
            string commit;
            cout << "Enter new commit"<<endl;
            cin >>commit;
            g->add_commit(username,rep,commit);
        }
        else if (2)
        {
            g->view_commit(username,rep);
        }
        else if (l == 3)
        {
            cout << "Fork successfull"<<endl;
        }
        
    }
    while(l);
}
void main_page(string username)
{
    int l;
    do
    {
        cout << "1-Show Reps"<<endl;
        cout << "2-Get into Rep"<<endl;
        cout << "3-Add Rep"<<endl;
        cout << "4-Delete Rep"<<endl;
        cout << "5-See Friends"<<endl;
        cout << "6-See Reps of another person"<<endl;
        cout << "7-See Friends of another Person"<<endl;
        cout << "8-Follow a Person"<<endl;
        cout << "0-exit"<<endl;
        cin >> l;

        if (l == 1)
        {
            g->show_all_repos(username);
        }
         if (l == 2)
        {
            string rep;

            cout << "Enter Rep name"<<endl;
            cin >> rep;
            if(g->Search_repo(username,rep))
            {
                into_rp(rep);
            }

        }
        else if (l == 3)
        {
            string Rep;
            cout << "Enter Rep name to add:";
            cin >> Rep;
            int x;
            cout << "Enter 0  for private and 1 for public:";
            cin >> x;
            if( x != 0 && x != 1)
            {
                cout <<"Error while adding"<<endl;
                continue;
            }
            g->Add_repo(username,Rep,x);
        }
        else if (l == 4)
        {
            string Rep;
            cout << "Enter Rep name to delete:";
            cin >> Rep;
            g->Del_repo(username,Rep);
        }
        else if (l== 5)
        {
            g->show_friends(username);
        }
        
        else if (l == 6)
        {
            string name;
            cout << "Enter name of the person:";
            cin >> name;
            g->show_public_repos(name);
        }
        else if (l == 7)
        {
            string name;
            cout << "Enter name of the person:";
            cin >> name;
            g->show_friends(name);
        }
        else if (l == 8)
        {
            string name;
            cout << "Enter name of the person:";
            cin >> name;
        }

    } while (l);
    
}
void register_login()
{

    int l;
    do
    {
    cout << "1-login"<< endl;
    cout << "2-Register"<< endl;
    cout << "3 exit" << endl;
    cin >> l;
                if (l == 1)
                {
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
                        break;
                    }
                }
                if( l == 2)
                {
                    cout << "Enter user name:";
                    cin >> username;
                    cout << "Enter Password:";
                    cin >> password;
                    g->Register_User(username,password);
                    cout << "Register Successfull"<<endl;

                }
    } while (2);
}


