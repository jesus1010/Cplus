#ifndef _b37cfe44_6101_11e2_9672_0800273fac01
#define _b37cfe44_6101_11e2_9672_0800273fac01

#define DISABLE_COPY_CONSTRUCTOR(name) name(const name &src)
#define DISABLE_EQUAL_OPERATOR(name) name& operator=(const name &src)
#define DISABLE_DEFAULT_CONSTRUCTOR(name) name()

#include <cstdio>
#include <sys/stat.h>
#include <string>

#if !defined(_MSC_VER) || !defined(_MSC_EXTENSIONS)
#include <sys/time.h>
#endif

#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
#include <windows.h>
#endif

#include <time.h>
#include "Types.h"
/**
 * Generic utils functions
 */
namespace layer0
{
  namespace util
  {
    // RLE compresion/decompresion constants
    const ui8 RLE_COUNTER_ID= 0xC0;
    const ui8 RLE_COUNTER_MASK_ID= 0xC0;
    const ui8 RLE_COUNTER_MASK_DATA= 0x3F;

    /**
     * [Return]: true is null
     */
    bool is_null(const void *ptr);

    /**
     * [Return]: true is ok
     */
    bool is_ok_state(FILE *in_file);

    /**
     * [Return]: NULL, on error case
     */ 
    char* get_argument(i32 argc, char **argv, ui32 pos);

    /**
      * [Return]: return NULL on error case.
      */
    FILE* open_file(const char *file_name, const char *mode, i32 &out_error);


    void close_file(FILE **data_file);

    /**
     * [Return]: return -1 on error case.
     */ 
    i64 get_position(FILE *file_data);

    /**
     * [Return]: return -1 on error case.
     */ 
    i32 set_position(FILE *file_data, i64 file_pos);

    /**
     * [Return]: return -1 on error case.
     */ 
    i32 set_end_position(FILE *file_data);

    /**
     * [Return]: -1 on error case.
     */
    i32 get_size(const char *file_name, ui64 &out_size, i32 &out_error);

    /**
     * [Return]: -1 on error case.
     */
    i32 read_block(FILE *file_data,
                     const i8 *block_buffer,
                     ui64 block_size,
                     ui64 block_offset,
                     ui64 total_size_block,
                     ui64 &out_total_reads,
                     i32 &out_error);

    void print_memory_pointer(void **mem_ptr);

    void free_mem(void **mem_ptr);

    void clear_mem(i8 *block_buffer, ui64 block_size);

    void check_pcx_header_size(ui64 actual_size, ui64 total_size, i32 &out_error);
    void check_pcx_header_id(i8 actual_id, i8 id, i32 &out_error);
    void decode_rle(ui64 &decoded_points,
                    i8 *rle_data,
                    ui32 rle_size,
                    i8 *out_buffer,
                    i32 &out_error);


    bool is_rle_counter(i8 value);
    bool is_less_than(ui64 op1, ui64 op2);
    i32 cast_ui32_to_i32(ui32 op);
    ui64 cast_i32_to_ui64(i32 op);
    ui32 cast_ui64_to_ui32(ui64 op);

    ui64 add_and_adjust_max_size(ui64 op1, ui64 op2, ui64 max_size);
    ui64 add_and_get_offset(ui64 op1, ui64 op2, ui64 max_size);
    void get_date_with_ms(char *out_date);
    FILE* open_log_file(const char *file_name, const char *mode);


  }
}
#endif
