#ifndef FIRESTORE_SERVICE_H
#define FIRESTORE_SERVICE_H

#include <string>

class FirestoreService {
public:
    void sendMessage(const std::string& idToken, const std::string& sender, const std::string& message);
    void viewMessages(const std::string& idToken);
};

#endif
