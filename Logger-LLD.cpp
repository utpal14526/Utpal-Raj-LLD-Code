#include <iostream>
#include <string>
#include <vector>
using namespace std;

// -----------------------------------------------------------
// ENUM FOR LOG LEVEL
// -----------------------------------------------------------
enum class LogLevel {
    DEBUG,
    INFO,
    WARN,
    ERROR
};

// -----------------------------------------------------------
// LOG MESSAGE DTO
// -----------------------------------------------------------
class LogMessage {
public:
    LogLevel level;
    string message;
    string createdAt;

    LogMessage(LogLevel lvl, const string& msg, const string& ts)
        : level(lvl), message(msg), createdAt(ts) {}
};

// -----------------------------------------------------------
// STRATEGY PATTERN: FORMATTERS
// -----------------------------------------------------------
class LogFormatter {
public:
    virtual string format(const LogMessage* msg) = 0;
    virtual ~LogFormatter() = default;
};

class PlainTextFormatter : public LogFormatter {
public:
    string format(const LogMessage* msg) override {
        return "[TEXT] Level=" + to_string(static_cast<int>(msg->level)) +
               " Message=" + msg->message + " Time=" + msg->createdAt;
    }
};

class JsonFormatter : public LogFormatter {
public:
    string format(const LogMessage* msg) override {
        return "{ \"level\": \"" + to_string(static_cast<int>(msg->level)) +
               "\", \"message\": \"" + msg->message +
               "\", \"createdAt\": \"" + msg->createdAt + "\" }";
    }
};

// -----------------------------------------------------------
// OBSERVER PATTERN: APPENDERS
// -----------------------------------------------------------
class LogAppender {
protected:
    LogFormatter* formatter;
public:
    LogAppender(LogFormatter* fmt) : formatter(fmt) {}
    virtual void append(const LogMessage* msg) = 0;
    virtual ~LogAppender() = default;
};

class ConsoleAppender : public LogAppender {
public:
    ConsoleAppender(LogFormatter* fmt) : LogAppender(fmt) {}

    void append(const LogMessage* msg) override {
        cout << "[Console] " << formatter->format(msg) << endl;
    }
};

class FileAppender : public LogAppender {
public:
    FileAppender(LogFormatter* fmt) : LogAppender(fmt) {}

    void append(const LogMessage* msg) override {
        // In real system: write to file
        cout << "[File] " << formatter->format(msg) << endl;
    }
};

// -----------------------------------------------------------
// CHAIN OF RESPONSIBILITY: HANDLERS
// -----------------------------------------------------------
class LogHandler {
protected:
    LogHandler* next = nullptr;
    vector<LogAppender*> appenders;

public:
    virtual ~LogHandler() = default;

    void setNext(LogHandler* nxt) { next = nxt; }

    void subscribe(LogAppender* app) { appenders.push_back(app); }

    void handle(const LogMessage* msg) {
        if (canHandle(msg)) {
            notifyAll(msg);
        } else if (next != nullptr) {
            next->handle(msg);
        }
    }

    virtual bool canHandle(const LogMessage* msg) = 0;

private:
    void notifyAll(const LogMessage* msg) {
        for (auto app : appenders) {
            app->append(msg);
        }
    }
};

class InfoLogHandler : public LogHandler {
public:
    bool canHandle(const LogMessage* msg) override {
        return msg->level == LogLevel::INFO;
    }
};

class WarnLogHandler : public LogHandler {
public:
    bool canHandle(const LogMessage* msg) override {
        return msg->level == LogLevel::WARN;
    }
};

class ErrorLogHandler : public LogHandler {
public:
    bool canHandle(const LogMessage* msg) override {
        return msg->level == LogLevel::ERROR;
    }
};

// -----------------------------------------------------------
// SINGLETON LOGGER FACADE
// -----------------------------------------------------------
class Logger {
private:
    LogHandler* chainHead;

    Logger() {
        // Build chain
        LogHandler* info = new InfoLogHandler();
        LogHandler* warn = new WarnLogHandler();
        LogHandler* error = new ErrorLogHandler();

        info->setNext(warn);
        warn->setNext(error);

        // Attach default appenders
        LogFormatter* plainFmt = new PlainTextFormatter();
        LogFormatter* jsonFmt = new JsonFormatter();

        info->subscribe(new ConsoleAppender(plainFmt));
        warn->subscribe(new ConsoleAppender(plainFmt));
        error->subscribe(new ConsoleAppender(jsonFmt));
        error->subscribe(new FileAppender(jsonFmt));

        chainHead = info;
    }

public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void log(LogLevel level, const string& msg) {
        LogMessage logMsg(level, msg, "06-12-2025");
        chainHead->handle(&logMsg);
    }

    Logger(const Logger&) = delete;
    void operator=(const Logger&) = delete;
};

// -----------------------------------------------------------
// MAIN
// -----------------------------------------------------------
int main() {
    Logger::getInstance().log(LogLevel::INFO, "This is an info log");
    Logger::getInstance().log(LogLevel::WARN, "Warning occurred");
    Logger::getInstance().log(LogLevel::ERROR, "Error happened bro");

    return 0;
}
