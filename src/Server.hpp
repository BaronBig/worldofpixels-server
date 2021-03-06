#pragma once

#include <string>
#include <string_view>
#include <chrono>
#include <memory>
#include <functional>
#include <map>

#include <ConnectionManager.hpp>
#include <Storage.hpp>
#include <WorldManager.hpp>
#include <ApiProcessor.hpp>
#include <AuthManager.hpp>

#include <PacketReader.hpp>
#include <explints.hpp>
#include <TimedCallbacks.hpp>
#include <AsyncCurl.hpp>
#include <TaskBuffer.hpp>
#include <AsyncPostgres.hpp>

#include <uWS.h>

class BansManager;
class Client;

class Server {
	const std::chrono::steady_clock::time_point startupTime;
	uWS::Hub h;
	// To stop the server from a signal handler, or other thread
	std::unique_ptr<uS::Async, void (*)(uS::Async *)> stopCaller;

	std::map<std::string, std::function<void(std::string_view)>, std::less<>> notifHandlers;

	Storage s;
	BansManager& bm;
	TaskBuffer tb;
	TimedCallbacks tc;
	AsyncPostgres ap;
	AuthManager am;
	WorldManager wm;
	ConnectionManager conn;
	ApiProcessor api;
	AsyncCurl ac;
	PacketReader<Client> pr;

	u32 saveTimer;
	u32 statsTimer;

public:
	Server(std::string basePath = ".");

	bool listenAndRun();
	bool freeMemory();
	void kickInactivePlayers();
	void stop();

private:
	void registerNotifs();
	void registerEndpoints();
	void registerPackets();
	static void doStop(uS::Async *);
	void unsafeStop();
};
