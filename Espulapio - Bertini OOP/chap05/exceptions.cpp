#include "exceptions.h"
#include <string>
#include <stdexcept>


void encoreChar(int i, std::string &str) {
    char letter = str[i];
    if((letter >= 'A' && letter < 'N') || (letter >= 'a' && letter < 'n')) {
        letter += 13;
    }
    else if((letter >= 'M' && letter < 'Z') || (letter >= 'm' && letter < 'z')) {
        letter -= 13;
    }

    try {
        str.replace(i, 1, 1, letter);   // add BUG
    } catch(std::out_of_range &e) {
        print("Cannot encore character at: ", i);
    }

}

void encodeString(int numChar, std::string &str) {
    for (int i = numChar-1; i >=0; i--)
    {
        /* code */
        encoreChar(i, str);
    }
    
}

void exceptionExample() {
    std::string secret = "Cesar's code";
    print("Original: ", secret);
    encodeString(secret.size(), secret);
    print("Cifer: ", secret);
    encodeString(99, secret);   //BUG
    print("Decifer: ", secret);

}

class DBConnection {
public:
    DBConnection(std::string dbName) : _dbName(dbName) { }

    void performQuery(std::string query) {
        this->_query = query;
    }

    void open() {
        print("Open Connections: ", this->_query);
    }

    void close() {
        print("Close Connection: ", this->_query);
    }
private:
    std::string _dbName;

    std::string _query;
};

class DBConnectionManager {
public:
    DBConnectionManager(DBConnection dbc) : db(dbc) {}
    ~DBConnectionManager() {
        if(!closed) {
            try
            {
                db.close();
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            
        }
    }

    void close() {
        db.close();
        closed = true;
    }

private:
    DBConnection db;

    bool closed;
};

void dbExample() {
    DBConnectionManager dcm(DBConnection("172.180.54.2:test"));
}