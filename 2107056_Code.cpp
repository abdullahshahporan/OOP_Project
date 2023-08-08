#include <iostream>
#include <vector>
using namespace std;

class User {
    string name;
    string number;
    string id;
    int password;
    int account_balance = 0;

public:
    User(string name, string number, string id, int password) {
        this->name = name;
        this->number = number;
        this->id = id;
        this->password = password;
    }

    int checkNumber(string number) {
        if (this->number == number)
            return 1;
        else
            return 0;
    }

    void cashIn(int amount) {
        account_balance += amount;
    }

    void cashOut(int amount) {
        if (amount <= account_balance) {
            account_balance -= amount;
        } else {
            cout << "You don't have sufficient balance" << endl;
        }
    }

    void sendMoney(int amount) {
        if (amount <= account_balance) {
            account_balance -= amount;
        } else {
            cout << "You don't have sufficient balance" << endl;
        }
    }

    int getBalance() {
        return account_balance;
    }

    friend class EmployeeManager;
};

class Agent {
    string name;
    string number;
    string id;
    int password;
    int account_balance;

public:
    friend class EmployeeManager;

    Agent(string name, string number, string id, int password, int account_balance) {
        this->name = name;
        this->number = number;
        this->id = id;
        this->password = password;
        this->account_balance = account_balance;
    }

    int checkNumber(string number) {
        if (this->number == number)
            return 1;
        else
            return 0;
    }

    void cashIn(int amount) {
        account_balance += amount;
    }

    void cashOut(int amount) {
        if (amount <= account_balance) {
            account_balance -= amount;
        } else {
            cout << "You don't have sufficient balance" << endl;
        }
    }

    void sendMoney(int amount) {
        if (amount <= account_balance) {
            account_balance -= amount;
        } else {
            cout << "You don't have sufficient balance" << endl;
        }
    }

    int getBalance() {
        return account_balance;
    }
};

class EmployeeManager {
    vector<User> users;
    vector<Agent> agents;

public:
    void showBalance() {
        int key, flag = 0;
        string number;
        cout << "1. User balance" << endl;
        cout << "2. Agent balance " << endl;
        cout << "Please enter a key : ";
        cin >> key;
        cout << "Enter account number : ";
        cin >> number;

        if (key == 2) {
            for (int i = 0; i < agents.size(); i++) {
                if (agents[i].checkNumber(number)) {
                    cout << "Your account balance is " << agents[i].account_balance << endl;
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                cout << "No registered account with this number" << endl;
            }
        } else if (key == 1) {
            for (int i = 0; i < users.size(); i++) {
                if (users[i].checkNumber(number)) {
                    cout << "Your account balance is " << users[i].account_balance << endl;
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                cout << "No registered account with this number" << endl;
            }
        }
    }

    void addNewAgentOrUser() {
        int key;
        cout << "1. Add user" << endl;
        cout << "2. Add agent" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter a key : ";
        cin >> key;

        if (key == 0) {
            return;
        }

        string name;
        string number;
        string id;
        int password, deposit;
        cout << "Number : ";
        cin >> number;
        getchar();
        cout << "Name : ";
        getline(cin, name);
        cout << "ID : ";
        cin >> id;
        cout << "Password : ";
        cin >> password;

        if (key == 2) {
            cout << "Deposit : ";
            cin >> deposit;
            Agent agent(name, number, id, password, deposit);
            agents.push_back(agent);
        } else if (key == 1) {
            cout << "Deposit : ";
            cin >> deposit;
            User user(name, number, id, password);
            user.cashIn(deposit);
            users.push_back(user);
        }
    }

    void removeUserOrAgent() {
        int key;
        cout << "1. Remove user" << endl;
        cout << "2. Remove agent" << endl;
        cout << "Enter a key : ";
        cin >> key;
        string number;
        cout << "Enter number : ";
        cin >> number;
        int flag = 0;
        if (key == 1) {
            for (int i = 0; i < users.size(); i++) {
                if (users[i].checkNumber(number)) {
                    users.erase(users.begin() + i);
                    flag = 1;
                    break;
                }
            }
        } else if (key == 2) {
            for (int i = 0; i < agents.size(); i++) {
                if (agents[i].checkNumber(number)) {
                    agents.erase(agents.begin() + i);
                    flag = 1;
                    break;
                }
            }
        }
        if (flag == 0) {
            cout << "No registered account with this number" << endl;
        } else {
            cout << "Member removed successfully!" << endl;
        }
    }

    void transferMoney() {
        int key, amount, i = 0, j = 0;
        string senderNumber, receiverNumber;
        cout << "1. Agent to Agent" << endl;
        cout << "2. Agent to User" << endl;
        cout << "3. User to Agent" << endl;
        cout << "4. User to User" << endl;
        cout << "Enter a key: ";
        cin >> key;
        cout << "Sender number: ";
        cin >> senderNumber;
        cout << "Receiver number: ";
        cin >> receiverNumber;
        switch (key) {
            case 1:
                i = findAgentIndex(senderNumber);
                if (i == -1)
                    break;
                j = findAgentIndex(receiverNumber);
                if (j == -1)
                    break;
                cout << "Enter amount: ";
                cin >> amount;
                agents[i].cashOut(amount);
                if (agents[i].getBalance() >= amount) {
                    agents[j].cashIn(amount);
                    cout << "Successfully " << amount << " tk transferred from " << senderNumber << " to " << receiverNumber << endl;
                }
                break;
            case 2:
                i = findAgentIndex(senderNumber);
                if (i == -1)
                    break;
                j = findUserIndex(receiverNumber);
                if (j == -1)
                    break;
                cout << "Enter amount: ";
                cin >> amount;
                agents[i].cashOut(amount);
                if (agents[i].getBalance() >= amount) {
                    users[j].cashIn(amount);
                    cout << "Successfully " << amount << " tk transferred from " << senderNumber << " to " << receiverNumber << endl;
                }
                break;
            case 3:
                i = findUserIndex(senderNumber);
                if (i == -1)
                    break;
                j = findAgentIndex(receiverNumber);
                if (j == -1)
                    break;
                cout << "Enter amount: ";
                cin >> amount;
                users[i].cashOut(amount);
                if (users[i].getBalance() >= amount) {
                    agents[j].cashIn(amount);
                    cout << "Successfully " << amount << " tk transferred from " << senderNumber << " to " << receiverNumber << endl;
                }
                break;
            case 4:
                i = findUserIndex(senderNumber);
                if (i == -1)
                    break;
                j = findUserIndex(receiverNumber);
                if (j == -1)
                    break;
                cout << "Enter amount: ";
                cin >> amount;
                users[i].sendMoney(amount);
                if (users[i].getBalance() >= amount) {
                    users[j].cashIn(amount);
                    cout << "Successfully " << amount << " tk transferred from " << senderNumber << " to " << receiverNumber << endl;
                }
                break;
            default:
                cout << "Wrong keyword" << endl;
        }
    }

    int findUserIndex(string number) {
        for (int i = 0; i < users.size(); i++) {
            if (users[i].checkNumber(number)) {
                return i;
            }
        }
        cout << number << " is not registered in our system" << endl;
        return -1;
    }

    int findAgentIndex(string number) {
        for (int i = 0; i < agents.size(); i++) {
            if (agents[i].checkNumber(number)) {
                return i;
            }
        }
        cout << number << " is not registered in our system" << endl;
        return -1;
    }
};

int main() {
    cout << "Welcome to the online mobile banking management system" << endl;
    EmployeeManager em;
    int choice;

    while (true) {
        cout << "1. Add member" << endl;
        cout << "2. Money transfer" << endl;
        cout << "3. Show balance" << endl;
        cout << "4. Remove member" << endl;
        cout << "0. Exit" << endl;
        cout << "Please enter a choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                em.addNewAgentOrUser();
                break;
            case 2:
                em.transferMoney();
                break;
            case 3:
                em.showBalance();
                break;
            case 4:
                em.removeUserOrAgent();
                break;
            case 0:
                cout << "Thank you" << endl;
                return 0;
            default:
                cout << "Wrong choice" << endl;
        }
    }

    return 0;
}

