#include <iostream>
using namespace std;
#include <stack>
#include <fstream>


struct TASK
{
  int id;
  string title;
  string description;
  string priority;
  string status;
  string createdAt;
};

struct Action{
 string type;
 TASK oldTask;
};


class Node{
public:
    TASK data;
    Node* next;    
    Node* prev;
Node(TASK t){
    data =t;
    next = nullptr;
    prev = nullptr;
}
};

class doublyLinkedList{
 
 private:
    Node* head;
    Node* tail;
    stack<Action> undostack;
    bool isUndo = false;
    
 
    public:
    ~doublyLinkedList() {
    saveToFile();    
    Clear();
}

    
    doublyLinkedList(){
        head = nullptr;
        tail = nullptr;
    }


    void addTask(TASK t)
    {
        Node* temp = head;
        while(temp){
            if(temp->data.id == t.id){
                cout<<"Task with ID "<<t.id<<" already exists. Please use a unique ID."<<endl;
                return;
            }
            temp = temp->next;
        }

       if(isUndo == false){
        Action action;
        action.type = "add";
        action.oldTask = t;
        undostack.push(action);
        }
       
       
        Node* newNode = new Node(t);
        if(head == nullptr){
            head = newNode;
            tail = newNode;
            return;
        }


        if(t.priority == "high"){
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            return;
        }else{
            tail->next= newNode;
            newNode->prev= tail;
            tail=newNode;
        return;
        }
    }

       void Display(){
            Node* temp = head;
            while(temp!= nullptr){
                cout<<"ID: "<<temp->data.id<<endl;
                cout<<"Title: "<<temp->data.title<<endl;
                cout<<"Description: "<<temp->data.description<<endl;
                cout<<"Priority: "<<temp->data.priority<<endl;
                cout<<"Status: "<<temp->data.status<<endl;
                cout<<"Created At: "<<temp->data.createdAt<<endl;
                cout<<"-----------------------------"<<endl;
                temp = temp->next;
            }
        }
     void Search(int user_id){
        Node* temp = head;
        if(temp == nullptr){
            cout<<"No Data in The List"<<endl;
            return;
        }
        while(temp){
        if(temp->data.id == user_id){
            cout<<"============================="<<"\n";
            cout<<"is found in the list."<<"\n";
            cout<<"============================="<<"\n";
            cout<<"ID is: "<<temp->data.id<<"\n"<<"title is: "<<temp->data.title<<"\n"<<"Description is: "<<temp->data.description<<"\n"<<"Priority is: "<<temp->data.priority<<"\n"<<"Status is: "<<temp->data.status<<"\n"<<"Created At is: "<<temp->data.createdAt<<"\n";
            return;
        }else{
            temp = temp->next;
        }
        
    }
 cout<<"The value is not found in the list."<<"\n";
     }

     bool Delete(int user_id){
        Node*  del = head;
        if(del == nullptr){
            
            return false;
        }
        if(head->data.id == user_id){
            if(isUndo == false){
            Action action;
            action.type = "delete";
            action.oldTask = del->data;
            undostack.push(action);
            }
            del =head;
            head= head->next;

            if(head == nullptr){
                tail = nullptr;
            }else{
                head->prev =nullptr;
            }
            delete del;
            return true;
        }else if(tail->data.id == user_id){
           if(isUndo == false){
            Action action;
            action.type = "delete";
            action.oldTask = tail->data;
            undostack.push(action);
           }
            del =tail;
            if(tail->prev == nullptr ){
                head=tail=nullptr;
            }else{
            tail = tail->prev;
            tail->next = nullptr;
        }
            delete del;
            return true;
        }else{
            
            while(del != nullptr && del->data.id != user_id ){
               del=del->next;  
            }

            if(del == nullptr){
              
                 
                return false;
            }
           if(isUndo == false){
            Action action;
            action.type = "delete";
            action.oldTask = del->data;
            undostack.push(action);
           }
            del->prev->next =del->next;
            if(del->next != nullptr){
            del->next->prev = del ->prev;
        }
            delete del;
        
            return true;
            
        } 
     }
     void Update(int user_id){
        if(head == nullptr){
            cout<<"No Data in The List"<<endl;
            return;
        }
        Node* temp = head;
        while(temp!= nullptr && temp->data.id != user_id){
            temp = temp->next;
        }
        if(temp ==nullptr){
            cout<<"The value is not found in the list."<<endl;
            return;
        }
        if(isUndo == false){
            Action action;
            action.type = "update";
            action.oldTask = temp->data;
            undostack.push(action);
        }

        TASK updateTask = temp->data;
         cin.ignore(); 
           
  
          
         string choice;
         do{
         cout<<"what do you want to update?"<<endl;
        
         cout<<"1. title" <<endl;
         cout<<"2. description" <<endl;
         cout<<"3. priority"<<endl;
         cout<<"4. status"<<endl;
         cout<<"5. createdAt"<<endl;

         getline(cin, choice);
         if(choice == "1"){
            cout << "Enter new title: ";
            getline(cin, updateTask.title);
         }else if(choice == "2"){
            cout << "Enter new description: ";
            getline(cin, updateTask.description);
         }else if(choice == "3"){
            cout << "Enter new priority: ";
            getline(cin, updateTask.priority);
        }else if(choice == "4"){
            cout << "Enter new status: ";
            getline(cin, updateTask.status);
        }else if(choice == "5"){
            cout << "Enter new createdAt: ";
            getline(cin, updateTask.createdAt);
        }else{
            cout<<"Invalid choice."<<endl;
        }
        string continueChoice;
        cout << "Do you want to update another field? (y/n): ";
        getline(cin, continueChoice);
        if (continueChoice != "y") {
            break;
        }
    }while(true);

        isUndo = true;
        Delete(user_id);
        addTask(updateTask);
        isUndo = false;
     }
     
     
     void Clear(){
        Node* temp = head;
        while(temp){
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
        head = tail = nullptr;

      while (undostack.empty() ==  false) {
        undostack.pop();
    }
     }



     void undo(){
        if(undostack.empty()){
            cout<<"No action to undo."<<endl;
            return;
        }
        
        Action lastAction = undostack.top();
        undostack.pop();

        if(lastAction.type == "add"){
            isUndo = true;
            Delete(lastAction.oldTask.id);
            isUndo = false;
        }else if(lastAction.type == "delete"){
            isUndo = true;
            addTask(lastAction.oldTask);
            isUndo = false;
        }else if(lastAction.type == "update"){
            isUndo = true;
            Delete(lastAction.oldTask.id);
            addTask(lastAction.oldTask);
            isUndo = false;
        }
        cout<<"Undo action: "<<lastAction.type<<" completed."<<endl;
      
     }

     void saveToFile() {
    ofstream file("tasks.txt");

    Node* temp = head;

    while (temp != nullptr) {
        file << temp->data.id << endl;
        file << temp->data.title << endl;
        file << temp->data.description << endl;
        file << temp->data.priority << endl;
        file << temp->data.status << endl;
        file << temp->data.createdAt << endl;

        file << "----" << endl; 

        temp = temp->next;
    }

    file.close();
}

void loadFromFile() {
    ifstream file("tasks.txt");

    if (!file) return;

     Clear();
    while (!undostack.empty()){
        undostack.pop();
    }
    TASK t;

    isUndo = true;

    while (file >> t.id) {
        file.ignore();
        getline(file, t.title);
        getline(file, t.description);
        getline(file, t.priority);
        getline(file, t.status);
        getline(file, t.createdAt);

        string separator;
        getline(file, separator);

        addTask(t);
    }
    isUndo = false;
    file.close();
}
     void Start(){
        cout<< "=====================================" << endl;
        cout<< "Welcome to the TODO List Application!" << endl;
         cout<< "=====================================" << endl;
          cout<< "what do you want to do?" << endl;
          cout<< "=====================================" << endl;
          cout<< "1. Add Task" << endl;
          cout<< "2. Display Task" << endl;
          cout<< "3. Search Task" << endl;
          cout<< "4. Delete Task" << endl;
          cout<< "5. Update Task" << endl;
          cout<< "6. Undo" << endl;
          cout<<"7. Clear the list" << endl;
          cout<<"8. Exit" << endl;
          cout<<"\n";

     }
};

int main() {

doublyLinkedList todoList;

todoList.loadFromFile(); 

do
{
    
todoList.Start();
string choice;
cout << "Enter your choice: ";
cin>> choice;

if (choice == "1"){
    TASK newTask;
    cout << "Enter task ID: ";
    cin>> newTask.id;
    cin.ignore(); 
    cout << "Enter new title: ";
    getline(cin, newTask.title);

    cout << "Enter new description: ";
    getline(cin, newTask.description);

    cout << "Enter new priority: ";
    getline(cin, newTask.priority);

    cout << "Enter new status: ";
    getline(cin, newTask.status);

    cout << "Enter new createdAt: ";
    getline(cin, newTask.createdAt);
    cout << "\n=========================\n";
    todoList.addTask(newTask);
    cout << "Task added successfully!" << endl;
    cout << "=========================\n";
    cout<<"\n";
}else if (choice == "2"){
    todoList.Display();
    cout << "\n";
}else if (choice == "3"){
    int searchId;
    cout << "Enter task ID to search: ";
    cin >> searchId;
    todoList.Search(searchId);
    cout<<"\n";
    
}else if (choice == "4"){
    int deleteId;
    cout << "Enter task ID to delete: ";
    cin >> deleteId;
    
   if(todoList.Delete(deleteId)){
       cout<<"The value is deleted from the list."<<endl;
   }else{
       cout<<"The value is not found in the list."<<endl;
   }
 
}else if (choice == "5"){
    int updateId;
    cout << "Enter task ID to update: ";
    cin >> updateId;
    todoList.Update(updateId);
    cout<<"Update is done."<<endl;
}else if (choice == "6"){
    todoList.undo();
    
    cout << "\n=========================\n";
}else if (choice == "7"){
    todoList.Clear();
    cout << "All tasks have been cleared." << endl;
    cout << "\n=========================\n";
}else if (choice == "8"){
    todoList.saveToFile();
    cout << "Exiting the application. Goodbye!" << endl;
    break;
}


} while (true);




return 0;

}