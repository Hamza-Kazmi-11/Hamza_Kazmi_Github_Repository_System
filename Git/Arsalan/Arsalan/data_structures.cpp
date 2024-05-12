#include <iostream>
#include <string>
using namespace std;
const int MAX_SIZE = 100;


class Graph {
private:
    struct Node {
        std::string name;
        Node* next;

        Node(const std::string& name) : name(name), next(nullptr) {}
    };

    struct Person {
        std::string name;
        Node* follows;
        Node* followedBy;
        Person() : name(""), follows(nullptr), followedBy(nullptr) {}
        Person(const std::string& name) : name(name), follows(nullptr), followedBy(nullptr) {}
    };

    Person* persons;
    int capacity;
    int size;

public:
    Graph(int capacity) : capacity(capacity), size(0) {
        persons = new Person[capacity];
    }

    ~Graph() {
        delete[] persons;
    }

    void addPerson(const std::string& name) {
        if (size >= capacity) {
            std::cout << "Graph capacity reached." << std::endl;
            return;
        }

        persons[size].name = name;
        size++;
    }

    void addEdge(const std::string& source, const std::string& destination) {
        int sourceIndex = findPersonIndex(source);
        int destIndex = findPersonIndex(destination);

        if (sourceIndex == -1 || destIndex == -1) {
            std::cout << "Person not found." << std::endl;
            return;
        }

        Node* followsNode = new Node(destination);
        followsNode->next = persons[sourceIndex].follows;
        persons[sourceIndex].follows = followsNode;

        Node* followedByNode = new Node(source);
        followedByNode->next = persons[destIndex].followedBy;
        persons[destIndex].followedBy = followedByNode;
    }

    void printConnections(const std::string& person) {
        int personIndex = findPersonIndex(person);
        if (personIndex == -1) {
            std::cout << "Person not found." << std::endl;
            return;
        }

        std::cout << "People followed by " << person << ": ";
        Node* followsNode = persons[personIndex].follows;
        while (followsNode != nullptr) {
            std::cout << followsNode->name << " ";
            followsNode = followsNode->next;
        }
        std::cout << std::endl;

        std::cout << "People following " << person << ": ";
        Node* followedByNode = persons[personIndex].followedBy;
        while (followedByNode != nullptr) {
            std::cout << followedByNode->name << " ";
            followedByNode = followedByNode->next;
        }
        std::cout << std::endl;
    }

private:
    int findPersonIndex(const std::string& name) {
        for (int i = 0; i < size; i++) {
            if (persons[i].name == name) {
                return i;
            }
        }
        return -1;
    }
};

class LinkedNode 
{
public:
    string data;
    LinkedNode* next;
    LinkedNode(string data) : data(data), next(nullptr) {}
};

class LinkedList
{
private:
    LinkedNode* head;
public:
    LinkedList() : head(nullptr) {}

    void insert(string data) 
    {
        LinkedNode* newNode = new LinkedNode(data);

        if (head == nullptr) 
        {
            head = newNode;
        } else {
            LinkedNode* current = head;
            while (current->next != nullptr) 
            {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void display() 
    {
        LinkedNode* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};


struct RepoStruct
{
    string Name;
    bool visibility;
    LinkedList *commits;
    LinkedList *Sfiles;
};







/// Tree Structure ////////////////
class Repo_BST 
{
private:
    static const int MAX_SIZE = 100;
    RepoStruct tree[MAX_SIZE];

public:
    Repo_BST() 
    {
        for (int i = 0; i < MAX_SIZE; i++) 
        {
            tree[i].Name = "";
            tree[i].visibility = 1;
            tree[i].commits = new LinkedList();
        }
    }
    void deleteNode(const std::string& value) {
    for (int i = 0; i < 20; i++) {
        if (tree[i].Name.compare(value) == 0) {
            tree[i].Name = "---"; 
            tree[i].visibility = 0; 
        }
    }
}

    void insert(const std::string& value ,int status) 
    {
        if (tree[0].Name == "") 
        {
            tree[0].Name = value;
        } else {
            int currentIndex = 0;
            while (true) 
            {
                if (value < tree[currentIndex].Name) 
                {
                    int leftChildIndex = (2 * currentIndex) + 1;
                    if (tree[leftChildIndex].Name == "") 
                    {
                        cout << "Here"<<endl;
                        tree[leftChildIndex].Name = value;
                        tree[leftChildIndex].visibility = status;
                        break;
                    } else 
                    {
                        currentIndex = leftChildIndex;
                    }
                } 
                else
                 {
                    int rightChildIndex = (2 * currentIndex) + 2;
                    if (tree[rightChildIndex].Name == "")
                    {
                        tree[rightChildIndex].Name = value;
                        tree[rightChildIndex].visibility = status;
                        break;
                    } else 
                    {
                        currentIndex = rightChildIndex;
                    }
                }
            }
        }
    }

    bool search(const std::string value) 
    {
        int currentIndex = 0;
        while (currentIndex < MAX_SIZE && tree[currentIndex].Name != "") 
        {
            if (value == tree[currentIndex].Name) 
            {
                return true;
            } else if (value < tree[currentIndex].Name)
            {
                currentIndex = (2 * currentIndex) + 1;
            } else
            {
                currentIndex = (2 * currentIndex) + 2;
            }
        }
        return false;
    }

    void printAllRepo(int currentIndex, int x) 
    {
            if (currentIndex >= MAX_SIZE || tree[currentIndex].Name == "")
            {
                return;
            }
            printAllRepo((2 * currentIndex) + 1,x);
            if(tree[currentIndex].visibility+x > 0 && tree[currentIndex].Name.compare("---"))
            // cout <<"Hello"<<endl;
            std::cout << "Rep:"<<tree[currentIndex].Name << "visibility:"<<tree[currentIndex].visibility << std::endl;
            printAllRepo((2 * currentIndex) + 2,x); 
        }

        void printAllRepos(int x)
        {
            // cout <<"Hello";
            printAllRepo(0,x);
        }
    bool Insert_commits(const std::string value , string commit) 
    {
        int currentIndex = 0;
        while (currentIndex < MAX_SIZE && tree[currentIndex].Name != "") 
        {
            if (value == tree[currentIndex].Name) 
            {
                tree[currentIndex].commits->insert(commit);
                return true;
            } else if (value < tree[currentIndex].Name)
            {
                currentIndex = (2 * currentIndex) + 1;
            } else
            {
                currentIndex = (2 * currentIndex) + 2;
            }
        }
        return false;
    }
    bool Display_commits(const std::string value) 
    {
        int currentIndex = 0;
        while (currentIndex < MAX_SIZE && tree[currentIndex].Name != "") 
        {
            if (value == tree[currentIndex].Name) 
            {
                tree[currentIndex].commits->display();
                return true;
            } else if (value < tree[currentIndex].Name)
            {
                currentIndex = (2 * currentIndex) + 1;
            } else
            {
                currentIndex = (2 * currentIndex) + 2;
            }
        }
        return false;
    }
};



// HashMaps Structure
struct hashNode 
{
    string key;
    string value;
    Repo_BST *reps;
    hashNode* next;
};
class Hashmap 
{
private:
    hashNode* table[MAX_SIZE];
    int hash(const string& key) 
    {
        int hashValue = 0;
        for (char c : key) {
            hashValue += c;
        }
        return hashValue % MAX_SIZE;
    }
public:
    Hashmap() 
    {
        for (int i = 0; i < MAX_SIZE; ++i) 
        {
            table[i] = nullptr;
        }
    }
    bool Insert_Repo(const string& key,string Rep , int status)
    {
        int index = hash(key);
        hashNode* currNode = table[index];
        while (currNode != nullptr) 
        {
            if (currNode->key == key);
            {
                currNode->reps->insert(Rep,status);
                return 1;
            }
            currNode = currNode->next;
        }
        return 0;
    }
    bool Delete_Repo(const string& key,string Rep)
    {
        int index = hash(key);
        hashNode* currNode = table[index];
        while (currNode != nullptr) 
        {
            if (currNode->key == key);
            {
       
                currNode->reps->deleteNode(Rep);
                return 1;
            }
            currNode = currNode->next;
        }
        return 0;
    }
    int Search_Repo(const string& key,string Rep)
    {
        int index = hash(key);
        hashNode* currNode = table[index];
        while (currNode != nullptr) 
        {
            if (currNode->key == key);
            {
                return currNode->reps->search(Rep);
            }
            currNode = currNode->next;
        }
        return 0;
    }
    int View_commits(const string& key,string Rep)
    {
        int index = hash(key);
        hashNode* currNode = table[index];
        while (currNode != nullptr) 
        {
            if (currNode->key == key);
            {
                return currNode->reps->Display_commits(Rep);
            }
            currNode = currNode->next;
        }
        return 0;
    }

    int Insert_commits(const string& key,string Rep,string commit)
    {
        int index = hash(key);
        hashNode* currNode = table[index];
        while (currNode != nullptr) 
        {
            if (currNode->key == key);
            {
                return currNode->reps->Insert_commits(Rep,commit);
            }
            currNode = currNode->next;
        }
        return 0;
    }

    void insert(const string& key, string value) {
        int index = hash(key);
        hashNode* newNode = new hashNode;
        newNode->key = key;
        newNode->value = value;
        newNode->next = nullptr;
        newNode->reps = new Repo_BST();
        if (table[index] == nullptr) 
        {
            table[index] = newNode;
        } 
        else {
            hashNode* currNode = table[index];
            while (currNode->next != nullptr) {
                currNode = currNode->next;
            }
            currNode->next = newNode;
        }
    }
    string* get(const string& key) 
    {
        int index = hash(key);
        hashNode* currNode = table[index];
        while (currNode != nullptr) 
        {
            if (currNode->key == key) 
            {
                return &currNode->value;
            }
            currNode = currNode->next;
        }
        return NULL;
    }

    void print_repos(string key,int x)
        {
        int index = hash(key);
        hashNode* currNode = table[index];
        while (currNode != nullptr) 
        {
            if (currNode->key == key) 
            {
                // cout << key<<endl;
                currNode->reps->printAllRepos(x);
            }
            currNode = currNode->next;
        }
    }

};




