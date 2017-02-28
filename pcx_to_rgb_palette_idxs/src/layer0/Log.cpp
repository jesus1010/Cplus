#include "Log.h"
namespace layer0
{
  namespace log
  {
    bool g_runtime_debug= false;
    bool g_log_file_mode= false;
    bool g_console_debug= false;
    bool g_flush_log_file_mode= false;
    FILE *g_log_file= NULL;
    log_level g_log_level= DISABLE_LV;
    std::atomic_flag lock = ATOMIC_FLAG_INIT;
  }
}
