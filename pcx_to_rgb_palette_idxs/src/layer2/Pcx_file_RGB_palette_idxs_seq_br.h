#ifndef _2cbb5330_6101_11e2_9ab6_0800273fac03
#define _2cbb5330_6101_11e2_9ab6_0800273fac03

#include <string>

#include "Util.h"
#include "Types.h"
#include "IRGB_palette_idxs_seq_block_r.h"
#include "File_seq_block_r.h"
#include "IBlock_access.h"

namespace layer2
{
  namespace img
  {
    class Pcx_file_RGB_palette_idxs_seq_br: public IRGB_palette_idxs_seq_block_r
    {
      public:
        //--CONSTRUCTORS--
        explicit Pcx_file_RGB_palette_idxs_seq_br();

        //--DESTRUCTOR--
        ~Pcx_file_RGB_palette_idxs_seq_br();

        void load_file(const char *file_name, i32 &out_error);

        void read_block(layer0::data::IBlock_access &out_block, 
                        i32 &out_error) override;

        inline ui64 get_total_points() const override {return this->total_points;}

        bool has_more() const override;

     private:
        ui64 reads_points;
        ui64 total_points;
        layer1::io::File_seq_block_r rle_reader;

        DISABLE_EQUAL_OPERATOR(Pcx_file_RGB_palette_idxs_seq_br);
        DISABLE_COPY_CONSTRUCTOR(Pcx_file_RGB_palette_idxs_seq_br);
    };    
  }
}
#endif
