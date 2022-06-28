#pragma once
#include <iostream>
#include <boost\asio.hpp>
#include <boost\system.hpp>
#include <boost\thread.hpp>
#include <boost\bind.hpp>
#include <array>
#include <string>
#include <mutex>

#define HELLO_MESSAGE "Hello! Do you want to start messaging with server? Y/N: "
#define GOODBY_MESSAGE "Client and Server stopped. Goodby!"
#define WRONG_COMMAND "Wrong command! Please, restart the program, and try again."
#define CHOICE_METHOD "Do you want to use asynchronus operation? Y/N: "