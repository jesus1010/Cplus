#include "Log.h"
#include <cassert>

#include "Errors_env.h"
#include "File_seq_block_r.h"
#include "Seq_block.h"
#include "Types.h"
#include "Util.h"
#include <string>

/**
 * Program entry point
 */
int main(int argc, char **argv)
{ 
  CONSOLE_MSG("-------------------------------------------------------------\n");   
  CONSOLE_MSG(">>INIT TEST:File_seq_block_r\n");
  CONSOLE_MSG("-------------------------------------------------------------\n");   

  //const char* TEST_FILE= "resources/test_256_128_128_ff0000.pcx";
  CONSOLE("Total arguments:%d\n", argc); 

  const char *TEST_CMD= (argc >= 2)?argv[1]: NULL;

  layer1::io::File_seq_block_r file_seq_br;
  layer1::io::Seq_block buffer;

  i32 read_status= layer0::error::_NO_ERROR;
  file_seq_br.load_file(TEST_CMD, read_status);

  if (read_status != layer0::error::_NO_ERROR)
  {
    CONSOLE_MSG("Error, Input file not found!\n");    
  }

  CONSOLE("File test:%s\n", TEST_CMD); 

  ui32 total_reads= 0;
  while(file_seq_br.has_more())
  {
    file_seq_br.read_block(buffer, read_status);
    total_reads += buffer.get_size();
    CONSOLE("Total read: %d\n", buffer.get_size()); 
  }

  CONSOLE("\nTotal reads:%d\n", total_reads); 
  CONSOLE("File size:%ld\n", file_seq_br.get_size()); 

  CONSOLE_MSG("-------------------------------------------------------------\n");   
  CONSOLE_MSG("<<END TEST:File_seq_block_r\n");
  CONSOLE_MSG("-------------------------------------------------------------\n");   
  return 0;
}

