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
