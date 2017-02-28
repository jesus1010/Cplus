#include <cstring>
#include <cstdlib>

#include "Util.h"
#include "Errors_env.h"
#include "Log.h"

//Visual studio definitions
#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
#define _CRT_SECURE_NO_WARNINGS
#pragma warning( disable : 4996)
#endif

namespace layer0
{
  namespace util
  {
    //--HELPERS FUNCTIONS--
    bool is_null(const void *ptr)
    {
      LOG_DEBUG(L0,"[>>]");
      LOG_DEBUG(L0,"P1[%p]", ptr);

      bool result= (ptr == NULL);
      if (result)
      {
        LOG_WARNING(L0,"Pointer is null");
      }
      LOG_DEBUG(L0,"[<<]|%d", (ui8)result);
      return result;
    }

    bool is_ok_state(FILE *in_file)
    {
      LOG_DEBUG(L0,"[>>]");
      LOG_DEBUG(L0,"P1[%p]",(void*)in_file);

      if (in_file == NULL)
      {      
        LOG_WARNING(L0,"[<<]|Null FILE pointer is in error state.") 
        return false;
      }

      bool result= (ferror(in_file) == 0);
      if (!result)
      {
        LOG_WARNING(L0,"[<<]|FILE pointer is in error state.");
      }

      LOG_DEBUG(L0,"[<<]|%d", (ui8)result);
      return result;
    }

    char* get_argument(i32 in_argc, char **in_argv, ui32 pos)
    { 
      LOG_DEBUG(L0,"[>>]");
      LOG_DEBUG(L0,"P1[%d]", in_argc);
      LOG_DEBUG(L0,"P2[%p]", (void*)in_argv);
      LOG_DEBUG(L0,"P3[%d]", pos);

      if (in_argv == NULL)
      {
        LOG_WARNING(L0,"[<<]|Array of parameter is NULL"); 
        return NULL;
      }

      char *argument= NULL;  
      if ((ui32)in_argc >= pos + 1)
      {
        argument = in_argv[pos];
      }
      else 
      {
        LOG_ERROR(L0,"Incorrect number of arguments|%d|expected|%d", in_argc, pos + 1);
      }
      LOG_DEBUG(L0,"[<<]|%p", argument);
      return argument;
    }

    FILE* open_file(const char *file_name, const char *mode, i32 &out_error)
    {
      LOG_DEBUG(L0,"[>>]");
      LOG_DEBUG(L0,"P1[%p]",(const void*)file_name);
      LOG_DEBUG(L0,"P2[%p]",(const void*)mode);
      LOG_DEBUG(L0,"P3_out");
     
      if (out_error != error::_NO_ERROR)
      {
        LOG_WARNING(L0,"[<<]|result is set with a error code, exit..."); 
        return NULL;
      }

      out_error= error::_NO_ERROR;
      if (file_name == NULL)
      {
        LOG_WARNING(L0,"[<<]|File name is NULL"); 
        out_error= error::NULL_FILE_NAME;
        return NULL;
      }

      if (mode == NULL)
      {
        LOG_WARNING(L0,"[<<]|String file open mode is NULL"); 
        out_error= error::NULL_FILE_OPEN_MODE;
        return NULL;
      }

      LOG_DEBUG(L0,"Opening file|%s|%s|", file_name, mode);
      FILE* file_data= fopen (file_name, mode);
      if (file_data != NULL && ferror(file_data) != 0)
      {
        LOG_ERROR(L0,"fail Creating file");
        LOG_DEBUG(L0,"Code ferror code|%d", ferror(file_data));
        out_error= error::FAIL_OPEN_FILE; 
        file_data= NULL;
      }
      LOG_DEBUG(L0,"File (name)|%s", file_name);
      LOG_DEBUG(L0,"File (mode)|%s", mode);
      LOG_DEBUG(L0,"[<<]|%p", (void*)file_data);
      return file_data;
    }

    void close_file(FILE **file_data)
    {
      LOG_DEBUG(L0,"[>>]");
      LOG_DEBUG(L0,"P1[%p]", (void*)file_data);

      if (file_data == NULL)
      {
        LOG_WARNING(L0,"[<<]|**File is NULL"); 
	      return;
      }

      if (*file_data == NULL)
      {
        LOG_WARNING(L0,"[<<]|File pointer is NULL"); 
	      return;
      }

      LOG_DEBUG(L0,"File pointer address|%p", (void*)*file_data);

      i32 code= fclose (*file_data);
      if (code != 0)
      {
        LOG_ERROR(L0,"closing file");
        if (file_data)
        {
          LOG_DEBUG(L0,"Code ferror|%d", ferror(*file_data));
        }

      }
      *file_data= NULL;

      LOG_DEBUG(L0,"[<<]");
    }

    void free_mem(void **mem_ptr)
    {
      LOG_DEBUG(L0,"[>>]");
      LOG_DEBUG(L0,"P1[%p]", *mem_ptr);

      if (mem_ptr == NULL)
      {
        LOG_WARNING(L0,"Memory pointer is NULL"); 
      }

      free(*mem_ptr);
      *mem_ptr= NULL;

      LOG_DEBUG(L0,"[<<]");
    }

    void print_memory_pointer(void **mem_ptr)
    {
      LOG_DEBUG(L0,"[>>]");
      LOG_DEBUG(L0,"P1[%p]", *mem_ptr);
      LOG_DEBUG(L0,"[<<]");
    }

    i64 get_position(FILE *file_data)
    {
      LOG_DEBUG(L0,"[>>]");
      LOG_DEBUG(L0,"P1[%p]", (void*)file_data);

      if (file_data == NULL)
      {
        LOG_WARNING(L0,"[<<]|File name is NULL"); 
        return -1;
      }

      i64 current_pos= ftell(file_data);
      if (current_pos < 0)
      {
        LOG_ERROR(L0,"fails getting file position indicator");
        if (file_data)
        {
          LOG_DEBUG(L0,"Code ferror|%d", ferror(file_data));
        }
      }
      LOG_DEBUG(L0,"[<<]|%lli", current_pos);
      return current_pos;
    }

    i32 set_position(FILE *file_data, i64 file_pos)
    {
      LOG_DEBUG(L0,"[>>]");
      LOG_DEBUG(L0,"P1[%p]", (void*)file_data);
      LOG_DEBUG(L0,"P2[%lli]", file_pos);

      if (file_data == NULL)
      {
        LOG_WARNING(L0,"[<<]|File name is NULL"); 
        return -1;
      }

      i32 error_code= 0; // no error
      if (fseek(file_data, file_pos, SEEK_SET))
      { 
        LOG_ERROR(L0,"fails seeking file position indicator, SEEK_SET");
        if (file_data)
        {
           LOG_DEBUG(L0,"Code ferror|%d", ferror(file_data));
        }
        error_code= -1;
      }
      LOG_DEBUG(L0,"[<<]|%d", (i32) error_code);
      return error_code;
    }

    i32 set_end_position(FILE *file_data)
    {
      LOG_DEBUG(L0,"[>>]");
      LOG_DEBUG(L0,"P1[%p]", (void*)file_data);

      if (file_data == NULL)
      {
        LOG_WARNING(L0,"[<<]|File data is NULL"); 
        return -1;
      }

      i32 error_code= 0;
      if (fseek(file_data, 0L, SEEK_END))
      {
        LOG_ERROR(L0,"fails seeking file position indicator, SEEK_END");
        if (file_data)
        {
          LOG_DEBUG(L0,"Code ferror|%d", ferror(file_data));
        }
        error_code= -1;
      }
      LOG_DEBUG(L0,"[<<]|%d", (i32) error_code);
      return error_code;
    }
    
    i32 get_size(const char *file_name, ui64 &out_size, i32 &out_error)
    {
      LOG_DEBUG(L0,"[>>]");
      LOG_DEBUG(L0,"P1[%p]", (const void*)file_name);
      LOG_DEBUG(L0,"P2_out");
      LOG_DEBUG(L0,"P3_out");
      out_size= 0;

      if (out_error != error::_NO_ERROR)
      {
        LOG_ERROR(L0,"[<<]|result is set with a error code, exit..."); 
        return -1;
      }

      out_error= error::_NO_ERROR;
      if (file_name == NULL)
      {
        LOG_WARNING(L0,"[<<]|File name is NULL"); 
        out_error= error::NULL_FILE_NAME;
        return -1;
      }

      struct stat st;
      if (stat(file_name, &st) == 0)
      {
        if (st.st_size < 0)
        {
          LOG_WARNING(L0,"Converting signed type to unsigned!!!"); 
        }

        out_size= static_cast<ui64>(st.st_size);
      }
      else
      {
        LOG_ERROR(L0,"[<<]|getting file size");
        out_error= error::FAIL_STATUS_FILE;
        return -1;
      }
      LOG_DEBUG(L0,"File name|%s", file_name);
      LOG_DEBUG(L0,"[<<]|%lli", out_size);
      return 0;
    }

    i32 read_block(FILE *file_data,
                     const i8 *block_buffer,
                     ui64 block_size,
                     ui64 block_offset,
                     ui64 total_size_block,
                     ui64 &out_total_reads,
                     i32 &out_error)
    {
      LOG_DEBUG(L0,"[>>]");
      LOG_DEBUG(L0,"P1[%p]", (void*)file_data);
      LOG_DEBUG(L0,"P2[%p]", (const void*)block_buffer);
      LOG_DEBUG(L0,"P3[%lli]", block_size);
      LOG_DEBUG(L0,"P4[%lli]", block_offset);
      LOG_DEBUG(L0,"P5[%lli]", total_size_block);
      LOG_DEBUG(L0,"P6_out");
      LOG_DEBUG(L0,"P7_out");

      out_total_reads= 0;
      if (out_error != error::_NO_ERROR)
      {
        LOG_WARNING(L0,"[<<]|result is set with a error code, exit..."); 
        return -1;
      }

      out_error = error::_NO_ERROR;
      if (file_data == NULL)
      {
        LOG_WARNING(L0,"[<<]|File data is NULL"); 
        out_error = error::NULL_PTR_FILE;
        return -1;
      }

      if (block_offset >= total_size_block)
      {
        LOG_WARNING(L0,"[<<]|block offset out of block"); 
        out_error = error::INDEX_OUT_OF_BOUND;
        return -1;
      }

      if (block_buffer == NULL)
      {
        LOG_WARNING(L0,"[<<]|Buffer data is NULL"); 
        out_error = error::NULL_PTR;
        return -1;
      }

      if (block_offset > LONG_MAX)
      {
        LOG_WARNING(L0,"Oveflow detected in conversion"); 
      }

      if (fseek(file_data, static_cast<long int>(block_offset), SEEK_SET))
      {
        LOG_ERROR(L0,"fails seeking file position indicator, SEEK_SET");
        if (file_data)
        {
           LOG_DEBUG(L0,"Code ferror|%d", ferror(file_data));
           out_error = error::FAIL_SEEK_OFFSET_FILE;
        }
        return -1;
      }

      out_total_reads= static_cast<ui64>(fread((void*)const_cast<i8*>(block_buffer), \
                             1, \
                             block_size, \
                             file_data));

      if (file_data != NULL && ferror(file_data) != 0)
      {
        LOG_ERROR(L0,"fail reading block(total reads bytes)|%lli", out_total_reads);
        out_error = error::FAIL_READ_FILE;
        return -1;
      }
      LOG_DEBUG(L0,"[<<]|%lli", out_total_reads);
      return 0;
    }

    void check_pcx_header_size(ui64 actual_size, ui64 total_size, i32 &out_error)
    {
      LOG_DEBUG(L0,"[>>]");
      LOG_DEBUG(L0,"P1[%lli]", actual_size);
      LOG_DEBUG(L0,"P2[%lli]", total_size);
      LOG_DEBUG(L0,"P3_out");

      if (out_error != error::_NO_ERROR)
      {
        LOG_WARNING(L0,"[<<]|error result is set with a error code, exit..."); 
        return;
      }

      if (actual_size != total_size)
      {
        LOG_ERROR(L0,"[<<]|Pcx header size not valid|%lli", actual_size); 
        out_error = error::PCX_HEADER_SIZE_NOT_VALID;  
      }
      LOG_DEBUG(L0,"[<<]");
    }

    void check_pcx_header_id(i8 actual_id, i8 id, i32 &out_error)
    {      
      LOG_DEBUG(L0,"[>>]");
      LOG_DEBUG(L0,"P1[%d]", actual_id);
      LOG_DEBUG(L0,"P2[%d]", id);
      LOG_DEBUG(L0,"P3_out");

      if (out_error != error::_NO_ERROR)
      {
        LOG_WARNING(L0,"[<<]|result is set with a error code, exit..."); 
        return;
      }

      if (actual_id != id)
      {
        LOG_ERROR(L0,"[<<]|Pcx header id not valid|%d", id); 
        out_error = error::PCX_HEADER_ID_NOT_VALID;  
        return;
      }
      LOG_DEBUG(L0,"[<<]");
    }

    void decode_rle(ui64 &decoded_points,
                    i8 *rle_data,
                    ui32 rle_size,
                    i8 *out_buffer,
                    i32 &out_error)
    {
      LOG_DEBUG(L0,"[>>]");
      LOG_DEBUG(L0,"P1_out");
      LOG_DEBUG(L0,"P2[%p", (void*)rle_data);
      LOG_DEBUG(L0,"P3[%d", rle_size);
      LOG_DEBUG(L0,"P4[%p", (void*)out_buffer);
      LOG_DEBUG(L0,"P5_out");
  
      decoded_points= 0;  
      if (out_error != error::_NO_ERROR)
      {
        LOG_WARNING(L0,"[<<]|result is set with a error code, exit..."); 
        return;
      }

      if (rle_data == NULL)
      {
        LOG_WARNING(L0,"[<<]|rle data pointer is NULL"); 
        out_error = error::NULL_PTR;
        return;
      }

      if (out_buffer == NULL)
      {
        LOG_WARNING(L0,"[<<]|out data pointer is NULL"); 
        out_error = error::NULL_PTR;
        return;
      }

      LOG_DEBUG(L0,"INIT DECODING RLE DATA..."); 
      ui32 rle_idx= 0;
      ui8 data;
      ui8 counter;
      while(rle_idx < rle_size)             
      {
        data= static_cast<ui8>(rle_data[rle_idx]);

        //it's a counter?
        counter= 0;
        if (static_cast<ui8>(data & RLE_COUNTER_MASK_ID) == RLE_COUNTER_ID)
        {
          counter= data & RLE_COUNTER_MASK_DATA;
        }

        if (counter > 0 && ((rle_idx + 1) < rle_size))
        {
          data= static_cast<ui8>(rle_data[rle_idx++]);
          memset((out_buffer + decoded_points), data, counter);
          decoded_points += counter;                   
        }
        else
        {
          out_buffer[decoded_points++]= static_cast<i8>(data);
        }
        rle_idx++;
      }

      #ifdef DEBUG_OUTPUT             
        LOG_DEBUG(L0,"Decode points, rle idx|%lli|%d|",decoded_points, rle_idx);
      #endif
      LOG_DEBUG(L0,"[<<]");
    }    

    bool is_rle_counter(i8 value)
    {
      LOG_DEBUG(L0,"[>>]");
      LOG_DEBUG(L0,"P1[%d]", value);
      bool result = static_cast<ui8>(value & RLE_COUNTER_MASK_ID) == RLE_COUNTER_ID;
      LOG_DEBUG(L0,"[<<]|%d", result);    
      return result;  
    }

    void clear_mem(i8 *block_buffer, ui64 block_size)
    {
      LOG_DEBUG(L0,"[>>]");
      LOG_DEBUG(L0,"P1[%p]", (void*)block_buffer);
      LOG_DEBUG(L0,"P2[%lli]", block_size);

      memset(block_buffer, 0, block_size);

      LOG_DEBUG(L0,"[<<]");
    }

    void get_date_with_ms(char *out_date)
    {

	    #if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
      SYSTEMTIME stime;
      //structure to store system time (in usual time format)
      FILETIME ltime;
      //structure to store local time (local time in 64 bits)
      FILETIME ftTimeStamp;
      GetSystemTimeAsFileTime(&ftTimeStamp); //Gets the current system time

      FileTimeToLocalFileTime(&ftTimeStamp, &ltime);//convert in local time and store in ltime
      FileTimeToSystemTime(&ltime, &stime);//convert in system time and store in stime

      sprintf(out_date, "%d-%d-%d  %d:%d:%d.%d",stime.wYear, stime.wMonth, stime.wDay\
                                               ,stime.wHour, stime.wMinute, stime.wSecond,stime.wMilliseconds);
	    #endif
		
      #if !defined(_MSC_VER) || !defined(_MSC_EXTENSIONS)
      struct timeval tv;
      struct tm* ptm;
      char time_string[40];
    
      gettimeofday(&tv, NULL);
      ptm = localtime (&tv.tv_sec);

      strftime (time_string, sizeof (time_string), "%Y-%m-%d %H:%M:%S", ptm);
      sprintf (out_date, "%s.%03ld", time_string, tv.tv_usec / 1000); 
      #endif
    }

    FILE* open_log_file(const char *file_name, const char *mode)
    {
      if (file_name == NULL)
      {
        CONSOLE_MSG("[<<]|WARNING: Log file name is NULL\n"); 
        return NULL;
      }

      if (mode == NULL)
      {
        CONSOLE_MSG("[<<]|WARNING:String file open mode is NULL\n"); 
        return NULL;
      }
      //CONSOLE("Opening log file|%s|%s|\n", file_name, mode);
      FILE* file_data= fopen (file_name, mode);
      if (file_data != NULL && ferror(file_data) != 0)
      {
        CONSOLE_MSG("ERROR:fail Creating log file\n");
        file_data= NULL;
      }
      return file_data;
    }
    
    bool is_less_than(ui64 op1, ui64 op2)
    {
      LOG_DEBUG(L0,"[>>]");
      LOG_DEBUG(L0,"P1[%lli]", op1);
      LOG_DEBUG(L0,"P2[%lli]", op2);
      bool result = op1 < op2;
      LOG_DEBUG(L0,"[<<]|%d", result);
      return result;
    }

    ui64 add_and_adjust_max_size(ui64 op1, ui64 op2, ui64 max_size)
    {
      LOG_DEBUG(L0,"[>>]");
      LOG_DEBUG(L0,"P1[%lli]", op1);
      LOG_DEBUG(L0,"P2[%lli]", op2);
      LOG_DEBUG(L0,"P3[%lli]", max_size);

      ui64 result= (op1 + op2) > max_size?max_size:(op1 + op2);

      LOG_DEBUG(L0,"[<<]|%lli", result);
      return result;
    }

    ui64 add_and_get_offset(ui64 op1, ui64 op2, ui64 max_size)
    {
      LOG_DEBUG(L0,"[>>]");
      LOG_DEBUG(L0,"P1[%lli]", op1);
      LOG_DEBUG(L0,"P2[%lli]", op2);
      LOG_DEBUG(L0,"P3[%lli]", max_size);

      ui64 result= (op1 + op2) > max_size?(op1 + op2) - max_size:0;

      LOG_DEBUG(L0,"[<<]|%lli", result);
      return result;      
    }

    i32 cast_ui32_to_i32(ui32 op)
    {
      LOG_DEBUG(L0,"[>>]");
      if (op > INT_MAX)
      {
        CONSOLE_MSG("[<<]|WARNING: overflow ui32 to i32\n"); 
      }
      return static_cast<i32>(op);
      LOG_DEBUG(L0,"[<<]");
    }

    ui64 cast_i32_to_ui64(i32 op)
    {
      LOG_DEBUG(L0,"[>>]");
      if (op < 0)
      {
        CONSOLE_MSG("[<<]|WARNING: oveflow i32 to ui64 conversion\n"); 
      }
      return static_cast<ui64>(op);
      LOG_DEBUG(L0,"[<<]");
    }

    ui32 cast_ui64_to_ui32(ui64 op)
    {
      LOG_DEBUG(L0,"[>>]");
      if (op > UINT_MAX)
      {
        CONSOLE_MSG("[<<]|WARNING: oveflow ui64 to ui32 conversion\n"); 
      }
      return static_cast<ui32>(op);
      LOG_DEBUG(L0,"[<<]");
    }

  }
}
