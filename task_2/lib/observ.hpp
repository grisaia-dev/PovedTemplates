#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>

class Observer {
public:
	virtual void onWarning(const std::string& msg) const {}
	virtual void onError(const std::string& msg) {}
	virtual void onFatalError(const std::string& msg) {}
};

class WarningObserver : public Observer {
public:
	void onWarning(const std::string& msg) const override { std::cout << msg << std::endl; }
	void onError() = delete;
	void onFatalError() = delete;
};

class ErrorObserver : public Observer {
public:
	explicit ErrorObserver(const std::string& path_for_file) : file(path_for_file, file.binary | file.out) {}

	void onWarning(const std::string& msg) = delete;
	void onError(const std::string& msg) override {
		if (file.is_open())
			file << msg << std::endl;
		else
			std::cout << "File don't found!!" << std::endl;
	}
	void onFatalError() = delete;

	~ErrorObserver() { file.close(); }
private:
	std::fstream file;
};

class FatalErrorObserver : public Observer {
public:
	explicit FatalErrorObserver(const std::string& path_to_file) : file(path_to_file, file.binary | file.out) {}

	void onWarning(const std::string& msg) = delete;
	void onError() = delete;
	void onFatalError(const std::string& msg) override {
		std::cout << msg << std::endl;
		if (file.is_open())
			file << msg << std::endl;
		else
			std::cout << "File don't found!!" << std::endl;
	}

	~FatalErrorObserver() { file.close(); }
private:
	std::fstream file;
};

class Observed {
public:
	explicit Observed() = default;
	void AddObserver(Observer* observer) {
		observers_.push_back(observer);
	}

	void warning(const std::string& msg) const {
		for (auto& observer : observers_) {
			observer->onWarning(msg);
		}
	}

	void error(const std::string& msg) const {
		for (auto& observer : observers_) {
			observer->onError(msg);
		}
	}

	void fatalError(const std::string& msg) const {
		for (auto& observer : observers_) {
			observer->onFatalError(msg);
		}
	}
	
	void RemoveObserver(Observer* observer) {
		auto it = std::remove(observers_.begin(), observers_.end(), observer);
		observers_.erase(it, observers_.end());
	}
private:
	std::vector<Observer*> observers_;
};