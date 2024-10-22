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

// Определяем тип функции плагина
using PluginFunction = double(*)(double);

// Определяем тип функции для регистрации плагинов
using RegisterFunction = void(*)(std::unordered_map<std::string, PluginFunction>&);

class CommandManager {
public:
    CommandManager();
    // Карта команд: имя команды -> функция плагина
    static std::unordered_map<std::string, PluginFunction> commandMap;

    // Загруженные библиотеки
    static std::vector<HMODULE> loadedLibraries;

    // Загружаем все плагины из папки
    static void LoadPlugins(const std::string& pluginFolder = "./plugins");

    static bool IsCommandAvailable(const std::string& commandName);
    // Вызов команды по имени
    static double InvokeCommand(const std::string& commandName, double arg1);
    // Выгрузка всех загруженных библиотек при завершении работы
    ~CommandManager();

    
};

#endif // !COMMAND_MANAGER_H

