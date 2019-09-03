#include "stdafx.h"
#include "LoginParams.h"

LoginParams::LoginParams(const char* username, const char* pass, const char* connection, const char* url)
{
    /* Load parameters with short keys. */
    mLogin = username;
    mPassword = pass;
    mURL = url;
    mConnection = connection;
}

LoginParams::~LoginParams(void)
{
}


const char *LoginParams::getLogin()
{
    return mLogin.c_str();
}

const char *LoginParams::getPassword()
{
    return mPassword.c_str();
}

const char *LoginParams::getURL()
{
    return mURL.c_str();
}

const char *LoginParams::getConnection()
{
    return mConnection.c_str();
}

const char *LoginParams::getSessionID()
{
    return mSessionID.c_str();
}

const char *LoginParams::getPin()
{
    return mPin.c_str();
}
