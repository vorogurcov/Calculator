#pragma once

#ifndef COMMAND_MANAGER_H
#define COMMAND_MANAGER_H

#include <iostream>
#include <windows.h>
#include <fstream>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <filesystem>

using PluginFunction = double(*)(double);

using RegisterFunction = void(*)(std::unordered_map<std::string, PluginFunction>&);

class CommandManager {
public:
   
    static std::unordered_map<std::string, PluginFunction> commandMap;

    static std::vector<HMODULE> loadedLibraries;

    static void LoadPlugins(const std::string& pluginFolder = "./plugins");

    static bool IsCommandAvailable(const std::string& commandName);
    
    static double InvokeCommand(const std::string& commandName, double arg1);
    
    ~CommandManager();

};

#endif // !COMMAND_MANAGER_H

