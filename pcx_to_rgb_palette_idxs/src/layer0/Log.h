#ifndef _4f969976_6101_11e2_a017_0800273fac14
#define _4f969976_6101_11e2_a017_0800273fac14

#include <cstring>
#include <cstdio>
#include <iostream>
#include <cassert>
#include <atomic>

#include "Types.h"
#include "Util.h"

namespace layer0
{
  namespace log
  {
    enum log_level
    {
      DISABLE_LV= -1,
      INFO_LV,
      WARNING_LV,
      ERROR_LV, 
      FATAL_LV,
      DEBUG_LV
    };

    extern bool g_runtime_debug;
    extern bool g_console_debug;
    extern bool g_log_file_mode;
    extern FILE *g_log_file;
    extern bool g_flush_log_file_mode;
    extern log_level g_log_level;
    extern std::atomic_flag lock;
  }
}

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define S1(x) #x
#define S2(x) S1(x)
#define LINE __FILE__ ":" S2(__LINE__)

#define LOG(tag_level, log_lv, layer_tag, ...) {\
                                   if ((log_lv != layer0::log::DISABLE_LV) && (log_lv <= layer0::log::g_log_level))\
                                   {\
                                      while(layer0::log::lock.test_and_set(std::memory_order_acquire));\
                                      char time[32];\
                                      layer0::util::get_date_with_ms(time);\
                                      if (layer0::log::g_console_debug)\
                                      {\
                                        fprintf(stderr, "[%s] ", time);fflush(stderr);\
                                        fprintf(stderr, " [%s] ", tag_level);fflush(stderr);\
                                        fprintf(stderr, "%s", layer_tag);fflush(stderr);\
                                        fprintf(stderr, "[%s", __FILENAME__);fflush(stderr);\
                                        fprintf(stderr, "->%s", __FUNCTION__);fflush(stderr);\
                                        fprintf(stderr, ":%d]|", __LINE__);fflush(stderr);\
                                        fprintf(stderr, ##__VA_ARGS__);fflush(stderr);\
                                        fprintf(stderr, "\n"); fflush(stderr);\
                                      }\
                                      if(layer0::log::g_log_file_mode && layer0::log::g_log_file != NULL)\
                                      {\
                                        fprintf(layer0::log::g_log_file, "[%s] ", time);if(layer0::log::g_flush_log_file_mode)fflush(layer0::log::g_log_file);\
                                        fprintf(layer0::log::g_log_file, " [%s] ", tag_level);if(layer0::log::g_flush_log_file_mode)fflush(layer0::log::g_log_file);\
                                        fprintf(layer0::log::g_log_file, "%s", layer_tag);if(layer0::log::g_flush_log_file_mode)fflush(layer0::log::g_log_file);\
                                        fprintf(layer0::log::g_log_file, "[%s", __FILENAME__);if(layer0::log::g_flush_log_file_mode)fflush(layer0::log::g_log_file);\
                                        fprintf(layer0::log::g_log_file, "->%s", __FUNCTION__);if(layer0::log::g_flush_log_file_mode)fflush(layer0::log::g_log_file);\
                                        fprintf(layer0::log::g_log_file, ":%d]|", __LINE__);if(layer0::log::g_flush_log_file_mode)fflush(layer0::log::g_log_file);\
                                        fprintf(layer0::log::g_log_file, ##__VA_ARGS__);if(layer0::log::g_flush_log_file_mode)fflush(layer0::log::g_log_file);\
                                        fprintf(layer0::log::g_log_file, "\n");if(layer0::log::g_flush_log_file_mode)fflush(layer0::log::g_log_file);\
                                        fflush(layer0::log::g_log_file);\
                                      }\
                                      layer0::log::lock.clear(std::memory_order_release);\
                                    }\
                                  }

#define L0 "[    L0]"
#define L1 "[  L1]"                
#define L2 "[L2]"                 

#define SET_LOG_LEVEL(log_level) layer0::log::g_log_level= log_level
#define SET_LOG_FILE(log_file) layer0::log::g_log_file= log_file
#define IS_LOG_FILE_ENABLE() layer0::log::g_log_file_mode
#define IS_LOG_CONSOLE_ENABLE() layer0::log::g_console_debug                                  
#define ENABLE_CONSOLE_LOG() layer0::log::g_console_debug= true
#define DISABLE_CONSOLE_LOG() layer0::log::g_console_debug= false
#define ENABLE_FILE_LOG() layer0::log::g_log_file_mode= true
#define DISABLE_FILE_LOG() layer0::log::g_log_file_mode= false
#define ENABLE_FLUSH_ON_FILE_LOG() layer0::log::g_log_file_mode= true
#define DISABLE_FLUSH_ON_FILE_LOG() layer0::log::g_log_file_mode= false                                  

#define LOG_INFO(tab, ...) LOG("INFO ", layer0::log::INFO_LV, tab, ##__VA_ARGS__)
#define LOG_WARNING(tab, ...) LOG("WARN ", layer0::log::WARNING_LV, tab, ##__VA_ARGS__)
#define LOG_ERROR(tab, ...) LOG("ERROR", layer0::log::ERROR_LV, tab, ##__VA_ARGS__)
#define LOG_FATAL(tab, ...) LOG("FATAL", layer0::log::FATAL_LV, tab, ##__VA_ARGS__)

#ifdef DEBUG_OUTPUT
  #define LOG_DEBUG(tab, ...) LOG("DEBUG", layer0::log::DEBUG_LV, tab, ##__VA_ARGS__)
#else
  #define LOG_DEBUG(...) {}
#endif                                  

//------------------------------------------------------------------------------
//No log macros                                  
#define CONSOLE_MSG(inMsg) {fprintf(stderr, inMsg);fflush(stderr);}
#define CONSOLE(inMsg, ...) {fprintf(stderr, inMsg,##__VA_ARGS__);fflush(stderr);}
#define INFO_MSG(inMsg, ...) {fprintf(stderr, "[INFO]" " " inMsg " " "\n",##__VA_ARGS__);fflush(stdout);}
#endif

