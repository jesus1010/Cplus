#ifndef _81bb5330_6101_11e2_9ab6_0800273faca1
#define _81bb5330_6101_11e2_9ab6_0800273faca1

#include "Util.h"
#include "Types.h"
#include "Seq_palette_RGB_idx_block.h"
#include "IBlock_access.h"

/**
 * RGB palette indexes sequential block reader definition.
 */
namespace layer2
 {
   namespace img
   {
    //--INTERFACE
    class IRGB_palette_idxs_seq_block_r
    {
      public:
        /**
         * Start with rgb palette index of pixel 0 
         */
        virtual void read_block(layer0::data::IBlock_access &out_block, 
                                i32 &out_error)= 0;
        virtual ui64 get_total_points() const  =0;
        virtual bool has_more() const= 0; 
       
        //--DESTRUCTOR
        virtual ~IRGB_palette_idxs_seq_block_r()
        {
          LOG_DEBUG(L2,"[>>]");
          LOG_DEBUG(L2,"[<<]");          
        }
    };
  }
}
#endif

