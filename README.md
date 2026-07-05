# 📝 To-Do List Manager (C++)

## 📌 Description
A console-based To-Do List Manager built using C++.

This project uses a Doubly Linked List to manage tasks efficiently, with additional features like:
- Undo functionality
- File persistence
- Priority-based sorting

The system allows users to add, delete, update, search, and manage tasks in a structured way.

---

## ⚙️ Features

- ➕ Add new tasks  
- ❌ Delete tasks  
- 🔄 Update tasks  
- 🔍 Search for tasks by ID  
- ↩️ Undo last deleted task  
- 📊 Priority sorting (High → Medium → Low)  
- 💾 Save tasks to file  
- 📂 Load tasks from file  

---

## 🧠 Data Structures Used

- Doubly Linked List → for storing tasks  
- Stack → for Undo functionality  

---

## ▶️ How to Run

### 1. Compile:
```bash
g++ todo_list.cpp -o todo
2. Run:
Execute the compiled program:

Bash
./todo
📷 Example Usage
Add a task with a specific priority (High, Medium, Low).

Delete a task simply by providing its ID.

Undo your last deletion instantly if you made a mistake.

Display all tasks sorted by their priority.

📁 File Handling
The program features built-in file handling. It automatically saves your tasks to a local file when exiting and loads them back when you start the program again, ensuring no data is lost!

👨‍💻 Author
Adham Al-Amir
