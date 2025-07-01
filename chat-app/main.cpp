#include <iostream>
#include "FirebaseAuth.h"
#include "FirestoreService.h"

using namespace std;

void displayMenu() {
  cout << "\n==== Chat App Menu ====" << endl;
  cout << "1. Register" << endl;
  cout << "2. Login" << endl;
  cout << "3. Send Message" << endl;
  cout << "4. View Chat History" << endl;
  cout << "5. Logout" << endl;
  cout << "6. Exit" << endl;
  cout << "Choose an option: ";
}

int main() {
    FirebaseAuth auth;
    FirestoreService db;
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string email, password;
            cout << "Email: "; getline(cin, email);
            cout << "Password: "; getline(cin, password);
            auth.registerUser(email, password);
        } else if (choice == 2) {
            string email, password;
            cout << "Email: "; getline(cin, email);
            cout << "Password: "; getline(cin, password);
            auth.loginUser(email, password);
        } else if (choice == 3) {
            if (!auth.isLoggedIn()) {
                cout << "Please login first.\n";
                continue;
            }
            string message;
            cout << "Enter message: "; getline(cin, message);
            db.sendMessage(auth.getIdToken(), auth.getEmail(), message);
        } else if (choice == 4) {
            if (!auth.isLoggedIn()) {
                cout << "Please login first.\n";
                continue;
            }
            db.viewMessages(auth.getIdToken());
        } else if (choice == 5) {
            auth.logout();
        } else if (choice == 6) {
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
