#include <iostream>
#include <windows.h>
#include <fstream>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <filesystem>
#include "CommandManagerHeader.h"


std::unordered_map<std::string, PluginFunction> CommandManager::commandMap = 
*new std::unordered_map<std::string, PluginFunction>;
std::vector<HMODULE> CommandManager::loadedLibraries = 
*new std::vector<HMODULE>;



static std::string getCommandName(std::string& command)
{
    command.erase(command.length() - 4);
    std::size_t pos = command.find("func");
    return command.substr(pos + 4);
}

void CommandManager::LoadPlugins(const std::string& pluginFolder) {
    for (const auto& entry : std::filesystem::directory_iterator(pluginFolder)) {
        std::string path = entry.path().string();
        if (path.substr(path.find_last_of(".") + 1) == "dll") {
            HMODULE hModule = LoadLibraryA(path.c_str());
            if (hModule) {
                
                std::string funcName = getCommandName(path);
                std::string funcDLLname = "func" + funcName;

                RegisterFunction registerPlugin = (RegisterFunction)GetProcAddress(hModule, funcDLLname.c_str());
                if (registerPlugin) {
                    registerPlugin(commandMap); 
                    commandMap[funcName.c_str()] = (PluginFunction)GetProcAddress(hModule, funcDLLname.c_str());
                    loadedLibraries.push_back(hModule);
                    std::cout << "Loaded plugin: " << path << std::endl;
                   
                }
            }
        }
    }
}

    
double CommandManager::InvokeCommand(const std::string& commandName,double arg1) {
    auto it = commandMap.find(commandName);
    if (it != commandMap.end()) {
        return it->second(arg1);  
    }
    else {
        throw std::runtime_error("Command not found: " + commandName);
    }
}

    
CommandManager::~CommandManager() {
    for (HMODULE hModule : loadedLibraries) {
        FreeLibrary(hModule);
    }
}

bool CommandManager::IsCommandAvailable(const std::string& commandName) {
    return commandMap.find(commandName) != commandMap.end();
}
