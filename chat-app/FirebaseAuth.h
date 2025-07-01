#ifndef FIREBASE_AUTH_H
#define FIREBASE_AUTH_H

#include <string>

class FirebaseAuth {
private:
    std::string idToken;
    std::string userId;
    std::string email;

public:
    bool registerUser(const std::string& email, const std::string& password);
    bool loginUser(const std::string& email, const std::string& password);
    void logout();
    bool isLoggedIn() const;
    std::string getIdToken() const;
    std::string getEmail() const;
};

#endif
