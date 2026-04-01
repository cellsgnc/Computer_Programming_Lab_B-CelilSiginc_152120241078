#include <iostream>
#include <string>
using namespace std;

struct MoneyBundle {
    string serialNumber, currencyType;
    int billCounts[3];
    MoneyBundle* next;
};

struct Customer {
    string name, transactionType;
};

void pushMoney(MoneyBundle** top, string serial, string type, int b100, int b50, int b20) {
    MoneyBundle* n = new MoneyBundle{serial, type, {b100, b50, b20}, *top};
    *top = n;
    cout << "[INFO] Money bundle added successfully (Push OK).\n";
}

void popMoney(MoneyBundle** top) {
    if (!*top) return;
    MoneyBundle* temp = *top;
    *top = (*top)->next;
    delete temp;
}

void enqueueCustomer(Customer c[], int* r, int* cnt, string name, string type) {
    if (*cnt == 5) {
        cout << "[ERROR] Queue is full! Cannot add new customer.\n";
        return;
    }
    *r = (*r + 1) % 5;
    c[*r] = {name, type};
    (*cnt)++;
    cout << "[INFO] Customer added to queue successfully (Enqueue OK).\n";
}

void dequeueCustomer(int* f, int* cnt) {
    if (*cnt == 0) return;
    *f = (*f + 1) % 5;
    (*cnt)--;
}

void processTransaction(MoneyBundle** top, Customer c[], int* f, int* cnt) {
    if (*cnt == 0) {
        cout << "[WARNING] No customer waiting.\n";
        return;
    }
    if (!*top) {
        cout << "[ERROR] No money in cash register, transaction cannot be completed!\n";
        return;
    }
    cout << "\n--- PROCESSING TRANSACTION ---\n";
    cout << "Customer: " << c[*f].name << "\n";
    cout << "Transaction Type: " << c[*f].transactionType << "\n";
    cout << "Used Bundle (Serial): " << (*top)->serialNumber << " (" << (*top)->currencyType << ")\n";
    cout << "--------------------------------\n";
    popMoney(top);
    dequeueCustomer(f, cnt);
}

void displayStatus(MoneyBundle* top, Customer c[], int f, int cnt) {
    cout << "\n========== CASH REGISTER (STACK) ==========\n";
    if (!top) cout << "Register is empty.\n";
    else for (MoneyBundle* cur = top; cur; cur = cur->next)
        cout << "[" << cur->serialNumber << " | " << cur->currencyType
             << " | 100s:" << cur->billCounts[0] << ", 50s:" << cur->billCounts[1]
             << ", 20s:" << cur->billCounts[2] << "]\n";
    cout << "\n========== CUSTOMER QUEUE (CIRCULAR) ==========\n";
    if (!cnt) cout << "Queue is empty.\n";
    else for (int i = 0; i < cnt; i++) {
        int idx = (f + i) % 5;
        cout << (i + 1) << ". " << c[idx].name << " (" << c[idx].transactionType << ")\n";
    }
    cout << "================================================\n\n";
}

int main() {
    MoneyBundle* cashTop = nullptr;
    Customer customers[5];
    int front = 0, rear = -1, count = 0, choice;

    do {
        cout << "1. Add Money (Push)\n2. Add Customer (Enqueue)\n3. Process Transaction\n"
             << "4. Show Status\n0. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            string sn, ct;
            int b100, b50, b20;
            cout << "Serial No: "; cin >> sn;
            cout << "Currency (TL/USD/EUR): "; cin >> ct;
            cout << "Count of 100s: "; cin >> b100;
            cout << "Count of 50s: "; cin >> b50;
            cout << "Count of 20s: "; cin >> b20;
            pushMoney(&cashTop, sn, ct, b100, b50, b20);
        }
        else if (choice == 2) {
            string name, type;
            cout << "Customer Name: "; cin >> name;
            cout << "Transaction (Deposit/Withdrawal): "; cin >> type;
            enqueueCustomer(customers, &rear, &count, name, type);
        }
        else if (choice == 3) {
            processTransaction(&cashTop, customers, &front, &count);
        }
        else if (choice == 4) {
            displayStatus(cashTop, customers, front, count);
        }
    } while (choice != 0);

    while (cashTop) popMoney(&cashTop);
    return 0;
}
