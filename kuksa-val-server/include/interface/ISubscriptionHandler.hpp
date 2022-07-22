/*
 * ******************************************************************************
 * Copyright (c) 2019 Robert Bosch GmbH.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * https://www.eclipse.org/org/documents/epl-2.0/index.php
 *
 *  Contributors:
 *      Robert Bosch GmbH - initial API and functionality
 * *****************************************************************************
 */
#ifndef __ISUBSCRIPTIONHANDLER_H__
#define __ISUBSCRIPTIONHANDLER_H__

#include <string>
#include <memory>
#include <jsoncons/json.hpp>
#include <boost/uuid/uuid.hpp>
#include "IPublisher.hpp"
#include "IServer.hpp"
#include "VSSPath.hpp"

#include "KuksaChannel.hpp"

class VssDatabase;
class WsServer;
class IVssDatabase;
class IPublisher;

using SubscriptionId = boost::uuids::uuid;

class ISubscriptionHandler {
  public:
    virtual ~ISubscriptionHandler() {}

    virtual SubscriptionId subscribe(KuksaChannel& channel,
                                     std::shared_ptr<IVssDatabase> db,
                                     const std::string &path, const std::string& attr) = 0;
    virtual int unsubscribe(SubscriptionId subscribeID) = 0;
    virtual int unsubscribeAll(KuksaChannel channel) = 0;
    virtual int publishForVSSPath(const VSSPath path, const std::string& vssdatatype, const std::string& attr, const jsoncons::json &value) = 0;

    virtual std::shared_ptr<IServer> getServer() = 0;
    virtual int startThread() = 0;
    virtual int stopThread() = 0;
    virtual bool isThreadRunning() const = 0;
    virtual void* subThreadRunner() = 0;
    virtual void addPublisher(std::shared_ptr<IPublisher> publisher) = 0;
};
#endif