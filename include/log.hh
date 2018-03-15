// Copyright Aeva 2017
#pragma once

#include <iostream>
#include <exception>

#define LOG std::cout

// grabbed from here:
// https://stackoverflow.com/questions/3767869/adding-message-to-assert
#define ASSERT(condition, message) \
  do { \
    if (! (condition)) { \
      std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                << " line " << __LINE__ << ": " << message << std::endl; \
      std::terminate(); \
    } \
  } while (false)
