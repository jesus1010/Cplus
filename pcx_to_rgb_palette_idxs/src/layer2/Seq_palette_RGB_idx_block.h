#ifndef _1aab5331_6101_81e2_4ab6_4900573fac00
#define _1aab5331_6101_81e2_4ab6_4900573fac00

#include "Types.h"
#include "IBlock_access.h"

namespace layer2
{
  namespace img
  {
    class Seq_palette_RGB_idx_block: public layer0::data::IBlock_access
    {
      public:       
        //--CONSTRUCTORS--
        explicit Seq_palette_RGB_idx_block() throw():size(0) 
        {
          LOG_DEBUG(L2,"[>>]");
          LOG_DEBUG(L2,"[<<]");
        }

        //--DESTRUCTOR--
        ~Seq_palette_RGB_idx_block()
        {
          LOG_DEBUG(L2,"[>>]");
          LOG_DEBUG(L2,"[<<]");
        }

        //--OPERATIONS--
        inline i8 operator[](ui16 idx) {return this->buffer[idx];} 

        inline i8* get_raw() override {return this->buffer;}     

        inline ui32 get_size() const override {return this->size;}

        inline ui32 get_capacity() const override {return USHRT_MAX + 1;}

        inline void set_size(ui32 in_size) override {this->size = in_size;}

        inline void add_size_offset(i32 offset) override {this->size= static_cast<ui32>(offset + static_cast<i32>(size));}

        inline i8 get_last_data() const override {return buffer[(this->size - 1) & 0xFFFF];}

      private:          
        ui32 size;       
        i8 buffer[USHRT_MAX + 1];

        DISABLE_EQUAL_OPERATOR(Seq_palette_RGB_idx_block);
        DISABLE_COPY_CONSTRUCTOR(Seq_palette_RGB_idx_block);
    };    
  }
}
#endif

