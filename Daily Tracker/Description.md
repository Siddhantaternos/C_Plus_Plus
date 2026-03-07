# ⚔ Daily Mission Tracker (C++ CLI)

A simple command-line productivity tool built in C++ that helps track your **daily purpose, tasks, and progress** directly from the terminal.

Instead of using complex productivity apps, this project focuses on a **minimal system**:

• Define a **daily mission (purpose)**
• Add tasks with **unique tags**
• Update task status anytime
• Track progress in a **CSV database that opens in Excel**

The goal is simple:
Know what you need to do today, track it honestly, and build a history of your execution.

---

## ✨ Features

* Terminal based task manager

* Define a **Daily Purpose**

* Add multiple tasks for the day

* Assign **unique tags** to each task

* Update task status using the tag

* Track task progress with 3 states:

  ```
  1 → Need to be completed
  2 → Currently working
  3 → Completed
  ```

* Automatically stores all data in a **CSV file**

* CSV file can be opened in **Excel / Google Sheets / Notion**

---

## 📊 Example Output (CSV)

```
Date, Purpose, Tag, Task, Status
7-3-2026, Improve discipline, gym01, Gym workout, 3
7-3-2026, Improve discipline, study01, Study Algorithms, 2
```

---

## ⚙ How to Compile

```
g++ purpose.cpp -o mission
```

Run the program:

```
./mission
```

or on Windows:

```
mission.exe
```

---

## 📁 File Structure

```
purpose.cpp
mission_log.csv
README.md
```

---

## 🧠 Why This Project Exists

Most productivity tools are overloaded with features.

This tool follows a different philosophy:

> Track what matters today.
> Finish the mission.
> Repeat tomorrow.

A simple system executed consistently beats a perfect system that is never used.

---

## 🚀 Future Improvements

* Task filtering by date
* Dashboard view for completed tasks
* Colored terminal UI
* Weekly productivity summary
* Direct Excel (.xlsx) export

