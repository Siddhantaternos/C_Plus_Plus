#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <limits>
#include <vector>

using namespace std;

struct Task {
    string description;
    string tag;
    int status;
    string learning;
};

string getDate() {
    time_t t = time(0);
    tm* now = localtime(&t);
    char buffer[20];
    sprintf(buffer, "%d-%d-%d", now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
    return string(buffer);
}

void addMission() {
    string purpose;
    cout << "\n----------------------------------------\n";
    cout << "  DAILY MISSION\n";
    cout << "----------------------------------------\n\n";

    // Purpose of the Day
    cout << "Purpose of the Day:\n-> ";
    getline(cin, purpose);

    vector<Task> tasks;
    Task task;

    // First task
    cout << "\nTask 1: ";
    getline(cin, task.description);

    cout << "Special Tag (example: gym01 / study02): ";
    getline(cin, task.tag);

    task.status = 1; // Default status
    tasks.push_back(task);

    // Ask for more tasks
    int taskNum = 2;
    while(true) {
        cout << "\nAnother task? (y/n): ";
        char another;
        cin >> another;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if(another != 'y' && another != 'Y') {
            break;
        }

        cout << "\nTask " << taskNum << ": ";
        getline(cin, task.description);

        cout << "Special Tag (example: gym" << taskNum << " / study" << taskNum << "): ";
        getline(cin, task.tag);

        task.status = 1;
        tasks.push_back(task);
        taskNum++;
    }

    // Ask status for each task
    cout << "\n----------------------------------------\n";
    cout << "  TASK STATUS\n";
    cout << "----------------------------------------\n";

    for(size_t i = 0; i < tasks.size(); i++) {
        cout << "\nTask: " << tasks[i].description << " (Tag: " << tasks[i].tag << ")\n";
        cout << "Status (1: Need to complete, 2: Working, 3: Completed): ";
        cin >> tasks[i].status;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Ask what you learned for each task
    cout << "\n----------------------------------------\n";
    cout << "  WHAT YOU LEARNED\n";
    cout << "----------------------------------------\n";

    for(size_t i = 0; i < tasks.size(); i++) {
        cout << "\nTask: " << tasks[i].description << "\nWhat you learned: ";
        getline(cin, tasks[i].learning);
    }

    // Save to CSV (Excel)
    ofstream file("mission_log.csv", ios::app);

    for(size_t i = 0; i < tasks.size(); i++) {
        file << getDate() << ","
             << purpose << ","
             << tasks[i].tag << ","
             << tasks[i].description << ","
             << tasks[i].status << ","
             << tasks[i].learning << "\n";
    }

    file.close();

    cout << "\n========================================\n";
    cout << "  MISSION SAVED TO EXCEL!\n";
    cout << "========================================\n";
    cout << "Total tasks: " << tasks.size() << "\n\n";
}

void updateStatus() {
    string tag;
    int newStatus;

    cout << "\n----------------------------------------\n";
    cout << "  UPDATE TASK STATUS\n";
    cout << "----------------------------------------\n\n";

    cout << "Enter task tag: ";
    cin >> tag;

    cout << "Status (1: Need to complete, 2: Working, 3: Completed): ";
    cin >> newStatus;

    ifstream file("mission_log.csv");
    ofstream temp("temp.csv");

    string date, purpose, t, task, status, learning;
    bool found = false;

    while(getline(file, date, ',') &&
          getline(file, purpose, ',') &&
          getline(file, t, ',') &&
          getline(file, task, ',') &&
          getline(file, status, ',') &&
          getline(file, learning))
    {
        if(t == tag && !found) {
            char buffer[10];
            sprintf(buffer, "%d", newStatus);
            status = string(buffer);
            found = true;
        }

        temp << date << ","
             << purpose << ","
             << t << ","
             << task << ","
             << status << ","
             << learning << "\n";
    }

    file.close();
    temp.close();

    if(found) {
        remove("mission_log.csv");
        rename("temp.csv", "mission_log.csv");
        cout << "\nStatus updated successfully!\n";
    } else {
        remove("temp.csv");
        cout << "\nTask with tag '" << tag << "' not found.\n";
    }
}

void viewMissions() {
    ifstream file("mission_log.csv");

    if(!file.is_open()) {
        cout << "\nNo missions found.\n";
        return;
    }

    cout << "\n========================================\n";
    cout << "  ALL MISSIONS\n";
    cout << "========================================\n\n";

    string date, purpose, tag, task, status, learning;

    while(getline(file, date, ',') &&
          getline(file, purpose, ',') &&
          getline(file, tag, ',') &&
          getline(file, task, ',') &&
          getline(file, status, ',') &&
          getline(file, learning))
    {
        cout << "Date: " << date << "\n";
        cout << "Purpose: " << purpose << "\n";
        cout << "Task: " << task << " [Tag: " << tag << "]\n";

        string statusText;
        if(status == "1") statusText = "Need to complete";
        else if(status == "2") statusText = "Working";
        else if(status == "3") statusText = "Completed";

        cout << "Status: " << statusText << "\n";
        cout << "Learned: " << learning << "\n";
        cout << "--------------------------------------\n";
    }

    file.close();
}

int main() {
    int choice;

    while(true) {
        cout << "========================================\n";
        cout << "     PERSONAL MISSION TRACKER\n";
        cout << "========================================\n";
        cout << "\n1. Create Daily Mission\n";
        cout << "2. Update Task Status\n";
        cout << "3. View All Missions\n";
        cout << "4. Exit\n";

        cout << "\nChoice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if(choice == 1) {
            addMission();
        } else if(choice == 2) {
            updateStatus();
        } else if(choice == 3) {
            viewMissions();
        } else if(choice == 4) {
            cout << "\nGoodbye!\n";
            break;
        } else {
            cout << "\nInvalid choice. Try again.\n";
        }
    }

    return 0;
}
