#include "electionguard/exception_handler.hpp"

#include "electionguard/constants.h"
#include "electionguard/group.hpp"
#include "log.hpp"

#include <array>
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

using std::array;
using std::make_unique;
using std::move;
using std::out_of_range;
using std::string;
using std::to_string;

namespace electionguard
{
    std::string ExceptionHandler::function;
    std::string ExceptionHandler::message;
    uint64_t ExceptionHandler::code;

    string ExceptionHandler::getFunction()
    {
        getInstance().task_lock.wait();
        return ExceptionHandler::function;
    }

    string ExceptionHandler::getMessage()
    {
        getInstance().task_lock.wait();
        return ExceptionHandler::message;
    }

    uint64_t ExceptionHandler::getCode()
    {
        getInstance().task_lock.wait();
        return ExceptionHandler::code;
    }

    void ExceptionHandler::setData(const std::string &function, uint64_t code,
                                   const std::exception &e)
    {
        getInstance().task_lock.wait();
        getInstance().function = function;
        getInstance().message = e.what();
        getInstance().code = code;
    }

    void ExceptionHandler::setData(const std::string &function, uint64_t code,
                                   const std::string &message)
    {
        getInstance().task_lock.wait();
        getInstance().function = function;
        getInstance().message = message;
        getInstance().code = code;
    }
} // namespace electionguard