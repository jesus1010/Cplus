
#include <cassert>
#include <string>

#include "Errors_env.h"
#include "Types.h"
#include "Util.h"
#include "Log.h"

#include "Pcx_file_RGB_palette_idxs_seq_br.h"

using namespace std;
namespace
{
  char *ARGUMENT_TEST_FILE;  

  void basic_test(i32 read_status);
  void basic_test(i32 read_status)
  {
    CONSOLE_MSG("-------------------------------------------------------------\n");   
    CONSOLE_MSG(">>INIT TEST:Pcx_file_RGB_palette_idxs_seq_br::basic_test\n");
    CONSOLE_MSG("-------------------------------------------------------------\n");   

    layer2::img::Pcx_file_RGB_palette_idxs_seq_br pcx_idx_br;
    layer2::img::Seq_palette_RGB_idx_block buffer;

    CONSOLE("File test:%s\n", ARGUMENT_TEST_FILE); 
    pcx_idx_br.load_file(ARGUMENT_TEST_FILE,read_status);
    ui32 total_reads= 0;
    ui64 block_idx= 0;
    while((read_status == layer0::error::_NO_ERROR)  && pcx_idx_br.has_more())
    {
      pcx_idx_br.read_block(buffer, read_status);
      total_reads += buffer.get_size();
      CONSOLE("Block read[%lli]: %d\n", block_idx++, buffer.get_size()); 
    }

    if (read_status != layer0::error::_NO_ERROR)
    {
      CONSOLE_MSG("\n"); 
      CONSOLE_MSG("Error processing file!\n");    
      CONSOLE("\nError code:%d\n", read_status); 
    }
    CONSOLE("\nTotal img points:%lli", pcx_idx_br.get_total_points()); 
    CONSOLE("\nTotal reads points:%lli\n", static_cast<ui64>(total_reads)); 
    CONSOLE_MSG("-------------------------------------------------------------\n");   
    CONSOLE_MSG("<<END TEST:Pcx_file_RGB_palette_idxs_seq_br::basic_test\n");
    CONSOLE_MSG("-------------------------------------------------------------\n");   
  }
}

int main(int argc, char **argv)
{ 
  CONSOLE_MSG("-------------------------------------------------------------\n");   
  CONSOLE_MSG(">>INIT TEST:Pcx_file_RGB_palette_idxs_seq_br\n");
  CONSOLE_MSG("-------------------------------------------------------------\n");   
  CONSOLE("Total arguments:%d\n", argc); 

  // log config
  //ENABLE_FILE_LOG();
  //ENABLE_CONSOLE_LOG();
  //SET_LOG_LEVEL(layer0::log::DEBUG_LV);
  
  i32 read_status= layer0::error::_NO_ERROR;
  if (IS_LOG_FILE_ENABLE())
  {
    string log_file(argv[0] + string(".log"));
    CONSOLE("Creating log file:%s\n", log_file.c_str());   
    SET_LOG_FILE(layer0::util::open_log_file(log_file.c_str(), "w")); 
  }
  ARGUMENT_TEST_FILE= (argc >= 2)?argv[1]: NULL;

  basic_test(read_status);

  CONSOLE_MSG("-------------------------------------------------------------\n");   
  CONSOLE_MSG("<<END TEST:Pcx_file_RGB_palette_idxs_seq_br\n");
  CONSOLE_MSG("-------------------------------------------------------------\n");   

  layer0::util::close_file(&layer0::log::g_log_file);
  return 0;
}

