#pragma once
#include <string>
#include <iostream>
#include <fstream>

enum class Type {
    Warning,
    Error,
    FatalError,
    UnknowMessage
};

struct Message {
    Type type_of_message;
    std::string message;
};

class LogMessage {
public:
    virtual ~LogMessage() {}
    virtual LogMessage* SetNext(LogMessage* logmessage) = 0;
    virtual const Message message(const Message message) = 0;
};

class BaseLogMessage : public LogMessage {
public:
    explicit BaseLogMessage() : next_LogMessage(nullptr) {}
    LogMessage* SetNext(LogMessage* logmessage) override {
        next_LogMessage = logmessage;
        return logmessage;
    }

    const Message message(const Message message) override {
        if (next_LogMessage)
            return next_LogMessage->message(message);
        return {};
    }
private:
    LogMessage* next_LogMessage;
};

class WarningLogMessage : public BaseLogMessage {
public:
    const Message message(const Message message) override {
        if (message.type_of_message == Type::Warning) {
            std::cout << "-> WARNING!!" << std::endl;
            std::cout << "   " << message.message << std::endl;
        }
        return BaseLogMessage::message(message);
    }
};

class ErrorLogMessage : public BaseLogMessage {
public:
    void AddFile(const std::string path_to_file) { file.open(path_to_file, file.binary | file.out); }
    const Message message(const Message message) override {
        if (message.type_of_message == Type::Error && file.is_open()) {
            file << "-> ERROR!" << std::endl;
            file << "   " << message.message << std::endl;
        }
        return BaseLogMessage::message(message);
    }
    ~ErrorLogMessage() { file.close(); }
private:
    std::fstream file;
};

class FatalErrorLogMessage : public BaseLogMessage {
public:
    const Message message(const Message message) override {
        if (message.type_of_message == Type::FatalError) {
            std::cout << "-> FATALERROR!!" << std::endl;
            // throw ... Типо он выбрасывает исключение и пишет в консоль
            std::cout << "   " << message.message << std::endl;
        }
        return BaseLogMessage::message(message);
    }
};

class UnknowMsgLogMessage : public BaseLogMessage {
public:
    const Message message(const Message message) override {
        if (message.type_of_message == Type::UnknowMessage) {
            std::cout << "-> UNKNOW_MESSAGE!" << std::endl;
            // throw ... Типо он выбрасывает исключение и пишет в консоль
            std::cout << "   " << message.message << std::endl;
        }
        return BaseLogMessage::message(message);
    }
};