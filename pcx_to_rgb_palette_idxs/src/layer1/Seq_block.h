#ifndef _9ccb5331_6101_81e2_4ab6_0800573fac00
#define _9ccb5331_6101_81e2_4ab6_0800573fac00

#include "Types.h"
#include "IBlock_access.h"

namespace layer1
{
  namespace io
  {
    class Seq_block: public layer0::data::IBlock_access
    {
      public:       

        //--CONSTRUCTORS--
        explicit Seq_block() throw():size(0) 
        {
          LOG_DEBUG(L1,"[>>]");
          LOG_DEBUG(L1,"[<<]");
        }

        //--DESTRUCTOR--
        ~Seq_block()
        {
          LOG_DEBUG(L1,"[>>]");
          LOG_DEBUG(L1,"[<<]");
        }

        //--OPERATIONS--
        inline i8 operator[](ui8 idx) {return this->buffer[idx];} 

        inline i8* get_raw() override {return this->buffer;}     

        inline ui32 get_size() const override {return this->size;}

        inline ui32 get_capacity() const override {return UCHAR_MAX + 1;}
        
        inline void set_size(ui32 in_size) override {this->size = in_size;}

        inline void add_size_offset(i32 offset) override {this->size= static_cast<ui32>(offset + static_cast<i32>(size));}

        inline i8 get_last_data() const override {return buffer[(this->size - 1) & 0xFF];}

      private:          
        ui32 size;       
        i8 buffer[UCHAR_MAX + 1];

        DISABLE_EQUAL_OPERATOR(Seq_block);
        DISABLE_COPY_CONSTRUCTOR(Seq_block);
    };    
  }
}
#endif

