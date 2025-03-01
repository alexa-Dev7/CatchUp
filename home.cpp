
#include <iostream>
#include <fstream>
#include <json/json.h>
#include <vector>

using namespace std;

vector<string> getActiveUsers() {
    vector<string> users;
    ifstream file("users.json");
    Json::Value data;
    file >> data;

    for (auto user : data["users"]) {
        users.push_back(user["username"].asString());
    }

    return users;
}

int main() {
    vector<string> users = getActiveUsers();
    cout << "Active Users:\n";
    for (string user : users) {
        cout << "- " << user << " [Message]" << endl;
    }
    return 0;
}
