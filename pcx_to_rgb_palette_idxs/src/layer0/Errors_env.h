#ifndef _5cbb5393_6101_1142_9ab6_0800273fac00
#define _5cbb5393_6101_1142_9ab6_0800273fac00

#include "Util.h"

/**
 * All application errors defitions.
 */
namespace layer0
{
  namespace error
  {   
    enum error_codes
    {
      //general errors
      _ERROR= -1,
      _NO_ERROR,
      NULL_PTR,
      INDEX_OUT_OF_BOUND,

      // file errors
      NULL_PTR_FILE,
      NULL_FILE_NAME,
      NULL_FILE_OPEN_MODE,
      FAIL_OPEN_FILE,
      FAIL_STATUS_FILE,
      FAIL_READ_FILE,
      FAIL_SEEK_OFFSET_FILE,

      //PCX file
      PCX_HEADER_SIZE_NOT_VALID,
      PCX_HEADER_ID_NOT_VALID,
      PCX_ALL_IMG_POINTS_DECODED
    };

    /*
    static const char* get_txt_code(INT32 error_code);
    static const char* get_descript(INT32 error_code);
    */
  }
}  
#endif

