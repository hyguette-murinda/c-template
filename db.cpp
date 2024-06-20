#include <iostream>
#include <mysqlx/xdevapi.h>

using namespace std;
using namespace mysqlx;

// Function to save user info to MySQL database
void saveUserInfo(const string& username, const string& password, const string& email) {
    try {
        // Create a session with MySQL server
        Session sess("localhost", 3306, "username", "password");

        // Select the 'school' schema
        Schema sch = sess.getSchema("school");

        // Get the 'users' collection
        Collection coll = sch.getCollection("users");

        // Insert user information into the collection
        coll.add({{"username", username}, {"password", password}, {"email", email}}).execute();

        // Print success message
        cout << "User info saved successfully!" << endl;
    } catch (const Error &err) {
        // Handle any errors
        cerr << "Error: " << err << endl;
    }
}

int main() {
    // Example usage
    saveUserInfo("john_doe", "password123", "john@example.com");

    return 0;
}
