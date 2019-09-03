#pragma once

class LoginParams
{
public:
    LoginParams(const char* username, const char* pass, const char* connection, const char* url);
    ~LoginParams(void);

    const char *getLogin();
    const char *getPassword();
    const char *getURL();
    const char *getConnection();
    const char *getSessionID();
    const char *getPin();

private:

    std::string mLogin;
    std::string mPassword;
    std::string mURL;
    std::string mConnection;
    std::string mSessionID;
    std::string mPin;
};

