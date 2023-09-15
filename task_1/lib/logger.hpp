#pragma once
#include <string>
#include <fstream>
#include <iostream>

class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

class LogInConsole : public LogCommand {
public:
    void print(const std::string& message) override {
        std::cout << message << std::endl;
    }
};

class LogInFile : public LogCommand {
public:
    explicit LogInFile(const std::string& path) : file(path, file.binary | file.out) {}
    void print(const std::string& message) override {
        if (!file.is_open()) {
            std::cout << "error" << std::endl;
        } else {
            file << message;
        }
    }
    ~LogInFile() {
        file.close();
    }
private:
    std::fstream file;
};