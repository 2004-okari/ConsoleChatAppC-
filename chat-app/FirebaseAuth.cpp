#include "FirebaseAuth.h"
#include "json.hpp"
#include <curl/curl.h>
#include <iostream>

using json = nlohmann::json;
using namespace std;

static const string API_KEY = "YOUR_FIREBASE_WEB_API_KEY";

size_t writeCallback(void* contents, size_t size, size_t nmemb, string* s) {
    size_t newLength = size * nmemb;
    s->append((char*)contents, newLength);
    return newLength;
}

bool FirebaseAuth::registerUser(const string& emailInput, const string& password) {
    CURL* curl = curl_easy_init();
    string response;

    if (curl) {
        string url = "https://identitytoolkit.googleapis.com/v1/accounts:signUp?key=" + API_KEY;
        json payload = {
            {"email", emailInput},
            {"password", password},
            {"returnSecureToken", true}
        };

        string data = payload.dump();
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        json res = json::parse(response);
        if (res.contains("idToken")) {
            cout << "Registration successful!\n";
            return true;
        } else {
            cout << "Registration failed: " << res.dump(2) << endl;
            return false;
        }
    }
    return false;
}

bool FirebaseAuth::loginUser(const string& emailInput, const string& password) {
    CURL* curl = curl_easy_init();
    string response;

    if (curl) {
        string url = "https://identitytoolkit.googleapis.com/v1/accounts:signInWithPassword?key=" + API_KEY;
        json payload = {
            {"email", emailInput},
            {"password", password},
            {"returnSecureToken", true}
        };

        string data = payload.dump();
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        json res = json::parse(response);
        if (res.contains("idToken")) {
            idToken = res["idToken"];
            userId = res["localId"];
            email = emailInput;
            cout << "Login successful!\n";
            return true;
        } else {
            cout << "Login failed: " << res.dump(2) << endl;
            return false;
        }
    }
    return false;
}

void FirebaseAuth::logout() {
    idToken = "";
    userId = "";
    email = "";
    cout << "Logged out.\n";
}

bool FirebaseAuth::isLoggedIn() const {
    return !idToken.empty();
}

string FirebaseAuth::getIdToken() const {
    return idToken;
}

string FirebaseAuth::getEmail() const {
    return email;
}
