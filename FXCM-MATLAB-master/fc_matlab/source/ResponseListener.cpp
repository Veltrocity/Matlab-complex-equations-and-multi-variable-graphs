#include "stdafx.h"
#include <math.h>

#include <sstream>
#include <iomanip>
#include "Offer.h"
#include <iostream>
#include "fc_matlab2.h"
#include "fc_matlab.h"
#include "OrderMonitor.h"
#include "ResponseListener.h"



ResponseListener::ResponseListener(IO2GSession *session)
{
    mSession = session;
    mSession->addRef();
    mRefCount = 1;
    mResponseEvent = CreateEvent(0, FALSE, FALSE, 0);
    mRequestID = "";
    mOrderID = "";
    mResponse = NULL;
    std::cout.precision(2);
	mInstrument = "";
	mOrderMonitor = NULL;
	for (int i = 0; i < 100; i++)
	{
		accBalance[i][0] = 0;
		accBalance[i][1] = 0;
	}
}

ResponseListener::~ResponseListener()
{
    if (mResponse)
        mResponse->release();
    mSession->release();
    CloseHandle(mResponseEvent);
}

void ResponseListener::setInstrument(const char *sInstrument)
{
    mInstrument = sInstrument;
}

/** Increase reference counter. */
long ResponseListener::addRef()
{
    return InterlockedIncrement(&mRefCount);
}

/** Decrease reference counter. */
long ResponseListener::release()
{
	
    long rc = InterlockedDecrement(&mRefCount);
	if (rc == 0)
	{
		delete this;
		printLog("ResponseListener -> delete");
	}
    return rc;
}

/** Set request. */
void ResponseListener::setRequestID(const char *sRequestID)
{
    mRequestID = sRequestID;
    if (mResponse)
    {
        mResponse->release();
        mResponse = NULL;
    }
    ResetEvent(mResponseEvent);
}

bool ResponseListener::waitEvents()
{
    return WaitForSingleObject(mResponseEvent, _TIMEOUT) == 0;
}

/** Gets response.*/
IO2GResponse *ResponseListener::getResponse()
{
    if (mResponse)
        mResponse->addRef();
    return mResponse;
}

std::string ResponseListener::getOrderID()
{
    return mOrderID;
}

/** Request execution completed data handler. */
void ResponseListener::onRequestCompleted(const char *requestId, IO2GResponse *response)
{
    if (response && mRequestID == requestId)
    {
        mResponse = response;
        mResponse->addRef();
        if (response->getType() != CreateOrderResponse)
            SetEvent(mResponseEvent);
    }
	std::cout << "onRequestCompleted: " << requestId << std::endl;
}

/** Request execution failed data handler. */
void ResponseListener::onRequestFailed(const char *requestId , const char *error)
{
    if (mRequestID == requestId)
    {
		sprintf(buf, "The request has been failed. ID: %s\n", requestId);
		cb_sendMsg(buf, 2);
		std::cout << buf;
        SetEvent(mResponseEvent);
    }
}

/** Request update data received data handler. */
void ResponseListener::onTablesUpdates(IO2GResponse *data)
{
	if (data)
    {
        if (!mInstrument.empty() && data->getType() == TablesUpdates)
            printOffers(mSession, data, mInstrument.c_str());

        O2G2Ptr<IO2GResponseReaderFactory> factory = mSession->getResponseReaderFactory();
        if (factory)
        {
            O2G2Ptr<IO2GTablesUpdatesReader> reader = factory->createTablesUpdatesReader(data);
            if (reader)
            {
				int k = reader->size();
                for (int i = 0; i < reader->size(); ++i)
                {

					//sprintf(buf, "onTablesUpdates: %s\n", mRequestID);
					//cb_sendMsg(buf, 2);
					//std::cout << buf;

                    switch (reader->getUpdateTable(i))
                    {
                    case Orders:
                    {
                        O2G2Ptr<IO2GOrderRow> order = reader->getOrderRow(i);
                        if (mRequestID != order->getRequestID())
						{
							//std::cout << "1: " << mRequestID << ", " << order->getRequestID() << "\n";
                            break;
						}
                        if (reader->getUpdateType(i) == Insert)
                        {
                            //if ((isClosingOrder(order) || isOpeningOrder(order)) &&  mOrderMonitor == NULL)
                            {
								sprintf(buf, "The order has been added. OrderID=%s, Rate=%f, TimeInForce=%s\n", order->getOrderID(), order->getRate(), order->getTimeInForce());
								cb_sendMsg(buf, 2);
								std::cout << buf;
                                //mOrderMonitor = new OrderMonitor(order);
                            }
                        }
                        else if (reader->getUpdateType(i) == Delete)
                        {
                            //if (mOrderMonitor)
                            {
								sprintf(buf, "The order has been deleted. OrderID=%s\n", order->getOrderID());
								cb_sendMsg(buf, 2);
								std::cout << buf;
                                //mOrderMonitor->onOrderDeleted(order);
                                //if (mOrderMonitor->isOrderCompleted())
                                {
                                   // printResult();
                                   // SetEvent(mResponseEvent);
                                }
                            }
                        }
                    }
                    break;
                    case Trades:
                    {
                        if (reader->getUpdateType(i) == Insert)
                        {
                            O2G2Ptr<IO2GTradeRow> trade = reader->getTradeRow(i);

							sprintf(buf, "Open new trade: Ticket#=%s, OrderID=%s, Open Rate=%f, Commission=%f\n", trade->getTradeID(), trade->getOpenOrderID(), trade->getOpenRate(), trade->getCommission());
							cb_sendMsg(buf, 2);
							std::cout << buf;

                            //if (mOrderMonitor)
                            {
                                //mOrderMonitor->onTradeAdded(trade);
                                //if (mOrderMonitor->isOrderCompleted())
                                {
                                    //printResult();
                                    //SetEvent(mResponseEvent);
                                }
                            }
                        }
                    }
                    break;
                    case ClosedTrades:
                    {
                        if (reader->getUpdateType(i) == Insert)
                        {
                            O2G2Ptr<IO2GClosedTradeRow> closedTrade = reader->getClosedTradeRow(i);

							sprintf(buf, "Close trade: Ticket#=%s, OrderID=%s, Open Rate=%f, Commission=%f\n", closedTrade->getTradeID(), closedTrade->getOpenOrderID(), closedTrade->getOpenRate(), closedTrade->getCommission());
							cb_sendMsg(buf, 2);
							std::cout << buf;

                            //if (mOrderMonitor)
                            {
                                //mOrderMonitor->onClosedTradeAdded(closedTrade);
                                //if (mOrderMonitor->isOrderCompleted())
                                {
                                    //printResult();
                                    //SetEvent(mResponseEvent);
                                }
                            }
                        }
                    }
                    break;
                    case Messages:
                    {
                        if (reader->getUpdateType(i) == Insert)
                        {
                            O2G2Ptr<IO2GMessageRow> message = reader->getMessageRow(i);

							sprintf(buf, "Message: From#=%s, Subject=%s, Text=%s, MsgID=%f\n", message->getFrom(), message->getSubject(), message->getText(), message->getMsgID());
							cb_sendMsg(buf, 2);
							std::cout << buf;

                            //if (mOrderMonitor)
                            {
                                //mOrderMonitor->onMessageAdded(message);
                                //if (mOrderMonitor->isOrderCompleted())
                                {
                                    //printResult();
                                    //SetEvent(mResponseEvent);
                                }
                            }
                        }
                    }
                    break;
                    case Accounts:
                    {
                        if (reader->getUpdateType(i) == Update && reader->getUpdateTable(i) == Accounts)
                        {
                            O2G2Ptr<IO2GAccountRow> account = reader->getAccountRow(i);
							int accId = std::atoi(account->getAccountID());
							for (int i = 0; i < 100; i++)
							{
								if (accBalance[i][0] == accId)
									accBalance[i][1] = (int)account->getBalance();
								else
									if (accBalance[i][0] == 0)
										accBalance[i][1] = (int)account->getBalance();
							}
							
							sprintf(buf, "The balance has been changed. AccountID=%s, Balance=%f\n", account->getAccountID(), account->getBalance());
							cb_sendMsg(buf, 2);
							std::cout << buf;
                        }
                    }
                    break;
                    }
                }
            }
        }
    }

}


// Store offers data from response and print it
void ResponseListener::printOffers(IO2GSession *session, IO2GResponse *response, const char *sInstrument)
{
    O2G2Ptr<IO2GResponseReaderFactory> readerFactory = session->getResponseReaderFactory();
    if (!readerFactory)
    {
        sprintf(buf, "Cannot create response reader factory\n");
		cb_sendMsg(buf, 3);
		std::cout << buf;
        return;
    }
	
    O2G2Ptr<IO2GOffersTableResponseReader> responseReader = readerFactory->createOffersTableReader(response);
	int k = responseReader->size();
    for (int i = 0; i < responseReader->size(); ++i)
    {
        O2G2Ptr<IO2GOfferRow> offerRow = responseReader->getRow(i);
		Offer *offer = 0;
		
        offer = new Offer(offerRow->getOfferID(), offerRow->getInstrument(),
                     offerRow->getDigits(), offerRow->getPointSize(), offerRow->getTime(),
                     offerRow->getBid(), offerRow->getAsk());
		
        if (!sInstrument || strlen(sInstrument) == 0 || strcmp(offerRow->getInstrument(), sInstrument) == 0)
        {
			std::cout.precision(6);
			sprintf(buf, "%s, %s,  Bid=%f, Ask=%f \n", offer->getID(), offer->getInstrument(), offer->getBid(), offer->getAsk()); 
			cb_sendMsg(buf, 3);
			std::cout << buf;
        }
    }
}

void ResponseListener::printResult()
{
	return;

    //if (mOrderMonitor)
    {
        OrderMonitor::ExecutionResult result = mOrderMonitor->getResult();
        std::vector<IO2GTradeRow*> trades;
        std::vector<IO2GClosedTradeRow*> closedTrades;
        O2G2Ptr<IO2GOrderRow> order = mOrderMonitor->getOrder();
        std::string orderID = order->getOrderID();
        mOrderMonitor->getTrades(trades);
        mOrderMonitor->getClosedTrades(closedTrades);

        switch (result)
        {
        case OrderMonitor::Canceled:
        {
            if (trades.size() > 0)
            {
                printTrades(trades, orderID);
                printClosedTrades(closedTrades, orderID);
				sprintf(buf, "A part of the order has been canceled. Amount = %d, the following positions have been opened:\n",mOrderMonitor->getRejectAmount());
				cb_sendMsg(buf, 2);
				std::cout << buf;
            }
            else
            {
				sprintf(buf, "The order: OrderID = %s, has been canceled\n",orderID.c_str());
				cb_sendMsg(buf, 2);
				std::cout << buf;

				sprintf(buf, "The cancel amount = %d\n",mOrderMonitor->getRejectAmount());
				cb_sendMsg(buf, 2);
				std::cout << buf;
            }
        }
        break;
        case OrderMonitor::FullyRejected:
        {
  		    sprintf(buf, "The order has been rejected. OrderID =%s\n",orderID.c_str());
			cb_sendMsg(buf, 2);
			std::cout << buf;

  		    sprintf(buf, "The rejected amount = %d\n", mOrderMonitor->getRejectAmount());
			cb_sendMsg(buf, 2);
			std::cout << buf;

  		    sprintf(buf, "TRejection cause: %s\n", mOrderMonitor->getRejectMessage());
			cb_sendMsg(buf, 2);
			std::cout << buf;
        }
        break;
        case OrderMonitor::PartialRejected:
        {
            printTrades(trades, orderID);
            printClosedTrades(closedTrades, orderID);

			sprintf(buf, "A part of the order has been rejected. Amount =%d\n",mOrderMonitor->getRejectAmount());
			cb_sendMsg(buf, 2);
			std::cout << buf;

			sprintf(buf, "Rejection cause: =%s\n",mOrderMonitor->getRejectMessage());
			cb_sendMsg(buf, 2);
			std::cout << buf;
        }
        break;
        case OrderMonitor::Executed:
        {
            printTrades(trades, orderID);
            printClosedTrades(closedTrades, orderID);
        }
        break;
        }
    }
}

void ResponseListener::printTrades(std::vector<IO2GTradeRow*> &trades, std::string &sOrderID)
{
    if (trades.size() == 0)
        return;

	sprintf(buf, "For the order: OrderID= %s, the following positions have been opened:\n",sOrderID.c_str());
	cb_sendMsg(buf, 2);
	std::cout << buf;

	for (size_t i = 0; i < trades.size(); ++i)
    {
        O2G2Ptr<IO2GTradeRow> trade = trades[i];
        std::string tradeID = trade->getTradeID();
        int amount = trade->getAmount();
        double rate = trade->getOpenRate();
		sprintf(buf, "Trade ID: %s, Amount: %d, Rate: %f\n",tradeID.c_str(), amount, rate);
		cb_sendMsg(buf, 2);
		std::cout << buf;
    }
}

void ResponseListener::printClosedTrades(std::vector<IO2GClosedTradeRow*> &closedTrades, std::string &sOrderID)
{
    if (closedTrades.size() == 0)
        return;
	sprintf(buf, "For the order: OrderID= %s, the following positions have been closed:\n",sOrderID.c_str());
	cb_sendMsg(buf, 2);
	std::cout << buf;
    
	for (size_t i = 0; i < closedTrades.size(); ++i)
    {
        IO2GClosedTradeRow *closedTrade = closedTrades[i];
        std::string tradeID = closedTrade->getTradeID();
        int amount = closedTrade->getAmount();
        double rate = closedTrade->getCloseRate();
		sprintf(buf, "Closed Trade ID: %s, Amount: %d, Closed Rate: %f\n",tradeID.c_str(), amount, rate);
		cb_sendMsg(buf, 2);
		std::cout << buf;

		closedTrade->release();
    }
}


