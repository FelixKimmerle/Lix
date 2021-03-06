#include "Logger.hpp"
#include "ConsoleColor.hpp"
#include <iostream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <chrono>


Logger::Logger(/* args */) : m_uiCurrentLevel(0)
{
}

Logger::~Logger()
{
}

std::string Logger::get_time(std::string format)
{
    using namespace std::chrono;

    // get current time
    auto now = system_clock::now();

    // get number of milliseconds for the current second
    // (remainder after division into seconds)
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    // convert to std::time_t in order to convert to std::tm (broken time)
    auto timer = system_clock::to_time_t(now);

    // convert to broken time
    std::tm bt = *std::localtime(&timer);

    std::ostringstream oss;

    oss << std::put_time(&bt, format.c_str()); // HH:MM:SS
    oss << '.' << std::setfill('0') << std::setw(3) << ms.count();

    return oss.str();
}

void Logger::log(const std::string &message, unsigned int level)
{
    if (level <= m_uiCurrentLevel)
    {
        std::cout << Color::Compatibility::Text::LightGray << "[" << Color::Text::Aqua << Color::Formatting::Bold << get_time("%d-%m-%Y %H:%M:%S") << Color::Reset << Color::Compatibility::Text::LightGray << "] ";
        switch (level)
        {
        case Error:
            std::cout << Color::Compatibility::Text::LightGray << "[ " << Color::Compatibility::Text::Red << Color::Formatting::Bold << "Error" << Color::Reset << Color::Compatibility::Text::LightGray << "   ] " << Color::Compatibility::Text::Red << message << std::endl;
            break;
        case Warning:
            std::cout << Color::Compatibility::Text::LightGray << "[ " << Color::Compatibility::Text::Yellow << Color::Formatting::Bold << "Warning" << Color::Reset << Color::Compatibility::Text::LightGray << " ] " << Color::Compatibility::Text::Yellow << message << std::endl;
            break;
        case Information:
            std::cout << Color::Compatibility::Text::LightGray << "[ " << Color::Compatibility::Text::Green << Color::Formatting::Bold << "Info" << Color::Reset << Color::Compatibility::Text::LightGray << "    ] " << Color::Compatibility::Text::Green << message << std::endl;
            break;

        default:
            if (m_Registered.count(level))
            {
                std::cerr << m_Registered[level] << message << Color::Reset << std::endl;
            }
            break;
        }
        std::cout << Color::Reset;
    }
}
void Logger::add(const std::string &format, unsigned int index)
{
    m_Registered.insert(std::make_pair(index, format));
}

void Logger::set_log_level(unsigned int level)
{
    m_uiCurrentLevel = level;
}