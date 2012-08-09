// **********************************************************************
//
// Copyright (c) 2003-2012 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICE_OBSERVER_I_H
#define ICE_OBSERVER_I_H

#include <Ice/MetricsObserverI.h>

namespace IceMX
{

class ConnectionObserverI : public Ice::Instrumentation::ConnectionObserver, public ObserverT<ConnectionMetrics>
{
public:

    virtual void detach();

    virtual void stateChanged(Ice::Instrumentation::ConnectionState, Ice::Instrumentation::ConnectionState);
    virtual void sentBytes(Ice::Int, Ice::Long);
    virtual void receivedBytes(Ice::Int, Ice::Long);
};

class ThreadObserverI : public Ice::Instrumentation::ThreadObserver, public ObserverT<ThreadMetrics>
{
public:

    virtual void stateChanged(Ice::Instrumentation::ThreadState, Ice::Instrumentation::ThreadState);
};

class InvocationObserverI : public Ice::Instrumentation::InvocationObserver, public ObserverT<InvocationMetrics>
{
public:

    InvocationObserverI();

    virtual void retried();

    virtual Ice::Instrumentation::ObserverPtr getRemoteObserver(const Ice::ConnectionPtr&);

private:

};

class CommunicatorObserverI : public Ice::Instrumentation::CommunicatorObserver
{
public:

    CommunicatorObserverI(const MetricsAdminIPtr&);

    virtual void setObserverUpdater(const Ice::Instrumentation::ObserverUpdaterPtr&);
 
    virtual Ice::Instrumentation::ObserverPtr getConnectObserver(const Ice::EndpointInfoPtr&, 
                                                                 const std::string&);
 
    virtual Ice::Instrumentation::ObserverPtr getEndpointLookupObserver(const Ice::EndpointInfoPtr&, 
                                                                        const std::string&);
    
    virtual Ice::Instrumentation::ConnectionObserverPtr 
    getConnectionObserver(const Ice::ConnectionInfoPtr&, 
                          const Ice::EndpointInfoPtr&,
                          Ice::Instrumentation::ConnectionState, 
                          const Ice::Instrumentation::ConnectionObserverPtr&);

    virtual Ice::Instrumentation::ThreadObserverPtr getThreadObserver(const std::string&, const std::string&,
                                                                      Ice::Instrumentation::ThreadState,
                                                                      const Ice::Instrumentation::ThreadObserverPtr&);

    virtual Ice::Instrumentation::InvocationObserverPtr getInvocationObserverWithContext(const Ice::ObjectPrx&, 
                                                                                         const std::string&, 
                                                                                         const Ice::Context&);
    
    virtual Ice::Instrumentation::InvocationObserverPtr getInvocationObserver(const Ice::ObjectPrx&, 
                                                                              const std::string&);

    virtual Ice::Instrumentation::ObserverPtr getDispatchObserver(const Ice::Current&);

private:

    const MetricsAdminIPtr _metrics;

    ObserverFactoryT<ConnectionObserverI> _connections;
    ObserverFactoryT<ObserverI> _dispatch;
    ObserverFactoryT<InvocationObserverI> _invocations;
    ObserverFactoryT<ThreadObserverI> _threads;
    ObserverFactoryT<ObserverI> _connects;
    ObserverFactoryT<ObserverI>  _endpointLookups;
};

};

#endif
