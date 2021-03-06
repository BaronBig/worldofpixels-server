#pragma once

#include "ConnectionProcessor.hpp"

#include <map>
#include <string>
#include <functional>

#include <Ip.hpp>
#include <HttpData.hpp>
#include <explints.hpp>

class ConnectionCounter : public ConnectionProcessor {
	u32 total;
	u32 totalChecked;

	u32 currentChecking;
	u32 currentActive;

	u8 maxConnsPerIp;
	std::map<Ip, u8> connCountPerIp;
	std::function<void(ConnectionCounter&)> updatesFunc;

public:
	ConnectionCounter();

	u32 getTotal() const;
	u32 getTotalChecked() const;
	u32 getCurrentActive() const;
	u32 getCurrentChecking() const;

	u8 getMaxConnectionsPerIp() const;
	void setMaxConnectionsPerIp(u8);
	void setCounterUpdateFunc(std::function<void(ConnectionCounter&)>);

	bool preCheck(IncomingConnection&, HttpData);

	void connected(Client&);
	void disconnected(ClosedConnection&);

	nlohmann::json getPublicInfo();
};
