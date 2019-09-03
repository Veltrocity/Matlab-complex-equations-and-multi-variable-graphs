#include "stdafx.h"
#include "SessionStatusListener.h"
#include "fc_matlab2.h"
#include "fc_matlab.h"

/** Constructor. */
SessionStatusListener::SessionStatusListener(IO2GSession *session, bool printSubsessions, const char *sessionID, const char *pin)
{
    if (sessionID != 0)
        mSessionID = sessionID;
    else
        mSessionID = "";
    if (pin != 0)
        mPin = pin;
    else
        mPin = "";
    mSession = session;
    mSession->addRef();
    reset();
    mPrintSubsessions = printSubsessions;
    mRefCount = 1;
    mSessionEvent = CreateEvent(0, FALSE, FALSE, 0);
}

/** Destructor. */
SessionStatusListener::~SessionStatusListener()
{
    mSession->release();
    mSessionID.clear();
    mPin.clear();
    CloseHandle(mSessionEvent);
}

/** Increase reference counter. */
long SessionStatusListener::addRef()
{
    return InterlockedIncrement(&mRefCount);
}

/** Decrease reference counter. */
long SessionStatusListener::release()
{
    long rc = InterlockedDecrement(&mRefCount);
    if (rc == 0)
        delete this;
    return rc;
}

void SessionStatusListener::reset()
{
    mConnected = false;
    mDisconnected = false;
    mError = false;
}

/** Callback called when login has been failed. */
void SessionStatusListener::onLoginFailed(const char *error)
{
    std::cout << "Login error: " << error << std::endl;
	cb_sendMsg( (char*)error, 1);
    mError = true;
}

/** Callback called when session status has been changed. */
void SessionStatusListener::onSessionStatusChanged(IO2GSessionStatus::O2GSessionStatus status)
{
    switch (status)
    {
    case IO2GSessionStatus::Disconnected:
		printLog("status::disconnected");
		cb_sendMsg("status::disconnected", 1);
        mConnected = false;
        mDisconnected = true;
        SetEvent(mSessionEvent);
        break;
    case IO2GSessionStatus::Connecting:
		printLog("status::connecting");
		cb_sendMsg("status::connecting", 1);
        break;
    case IO2GSessionStatus::TradingSessionRequested:
    {
        std::cout << "status::trading session requested" << std::endl;
        O2G2Ptr<IO2GSessionDescriptorCollection> descriptors = mSession->getTradingSessionDescriptors();
        bool found = false;
        if (descriptors)
        {
            if (mPrintSubsessions)
                std::cout << "descriptors available:" << std::endl;
            for (int i = 0; i < descriptors->size(); ++i)
            {
                O2G2Ptr<IO2GSessionDescriptor> descriptor = descriptors->get(i);
                if (mPrintSubsessions)
                    std::cout << "  id:='" << descriptor->getID()
                              << "' name='" << descriptor->getName()
                              << "' description='" << descriptor->getDescription()
                              << "' " << (descriptor->requiresPin() ? "requires pin" : "") << std::endl;
                if (mSessionID == descriptor->getID())
                {
                    found = true;
                    break;
                }
            }
        }
        if (!found)
        {
            onLoginFailed("The specified sub session identifier is not found");
        }
        else
        {
            mSession->setTradingSession(mSessionID.c_str(), mPin.c_str());
        }
    }
    break;
    case IO2GSessionStatus::Connected:
		printLog("status::connected");
		cb_sendMsg("status::connected", 1);
        mConnected = true;
        mDisconnected = false;
        SetEvent(mSessionEvent);
        break;
    case IO2GSessionStatus::Reconnecting:
		printLog("status::reconnecting");
		cb_sendMsg("status::reconnecting", 1);
        break;
    case IO2GSessionStatus::Disconnecting:
		printLog("status::disconnecting");
		cb_sendMsg("status::disconnecting", 1);
        break;
    case IO2GSessionStatus::SessionLost:
		printLog("status::session lost");
		cb_sendMsg("status::session lost", 1);
        break;
    }
}

/** Check whether error happened. */
bool SessionStatusListener::hasError() const
{
    return mError;
}

/** Check whether session is connected */
bool SessionStatusListener::isConnected() const
{
    return mConnected;
}

/** Check whether session is disconnected */
bool SessionStatusListener::isDisconnected() const
{
    return mDisconnected;
}

/** Wait for connection or error. */
bool SessionStatusListener::waitEvents()
{
    return WaitForSingleObject(mSessionEvent, _TIMEOUT) == 0;
}

