#ifndef _94bb7330_6171_11e2_98b6_0820273fac00
#define _94bb7330_6171_11e2_98b6_0820273fac00

#include <string>

#include "Types.h"
#include "Log.h"
#include "IBlock_access.h"

/**
 * Seq block reader definition.
 */
namespace layer1
{
  namespace io
  {
    //--INTERFACE--
    class ISeq_block_reader
    {
      public:

        /**
         * Set index offset block to 0
         */
        virtual void reset_offset_block()= 0;

        /**
         * Starts write offset 0
         * [Return]:total reads bytes.
         */
        virtual void read_block(layer0::data::IBlock_access &block_result, i32 &out_error)= 0;

        virtual bool has_more() const =0;

        virtual ui64 get_size() const = 0;

        virtual void add_offset_block(i32 offset)= 0;

        virtual ui64 get_actual_offset() const =0;
        
        //--DESTRUCTOR--
        virtual ~ISeq_block_reader()
        {
          LOG_DEBUG(L1,"[>>]");
          LOG_DEBUG(L1,"[<<]");
        }
    };
  }
}
#endif
