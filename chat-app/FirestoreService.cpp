#include "FirestoreService.h"
#include "json.hpp"
#include <curl/curl.h>
#include <iostream>
#include <ctime>

using json = nlohmann::json;
using namespace std;

static const string PROJECT_ID = "YOUR_FIREBASE_PROJECT_ID";

size_t writeCallback(void* contents, size_t size, size_t nmemb, string* s) {
    size_t newLength = size * nmemb;
    s->append((char*)contents, newLength);
    return newLength;
}

void FirestoreService::sendMessage(const string& idToken, const string& sender, const string& message) {
    CURL* curl = curl_easy_init();
    string response;

    if (curl) {
        time_t now = time(nullptr);
        string url = "https://firestore.googleapis.com/v1/projects/" + PROJECT_ID + "/databases/(default)/documents/messages";

        json payload = {
            {"fields", {
                {"sender", {{"stringValue", sender}}},
                {"message", {{"stringValue", message}}},
                {"timestamp", {{"integerValue", static_cast<int>(now)}}}
            }}
        };

        string data = payload.dump();
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, ("Authorization: Bearer " + idToken).c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        cout << "Message sent.\n";
    }
}

void FirestoreService::viewMessages(const string& idToken) {
    CURL* curl = curl_easy_init();
    string response;

    if (curl) {
        string url = "https://firestore.googleapis.com/v1/projects/" + PROJECT_ID + "/databases/(default)/documents/messages";
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, ("Authorization: Bearer " + idToken).c_str());

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        json res = json::parse(response);
        if (res.contains("documents")) {
            for (auto& doc : res["documents"]) {
                auto fields = doc["fields"];
                string sender = fields["sender"]["stringValue"];
                string msg = fields["message"]["stringValue"];
                cout << sender << ": " << msg << endl;
            }
        } else {
            cout << "No messages found.\n";
        }
    }
}
