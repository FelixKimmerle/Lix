#pragma once
#include <string>
#include <map>

class Logger
{
  public:
    enum LogLevel
    {
        Error = 10,
        Warning = 20,
        Information = 30,
    };

  private:
    std::map<unsigned int, std::string> m_Registered;
    std::string get_time(std::string format);
    unsigned int m_uiCurrentLevel;
  public:
    Logger(/* args */);
    ~Logger();
    void log(const std::string &message, unsigned int level);
    void add(const std::string &format, unsigned int index);
    void set_log_level(unsigned int level);
};
