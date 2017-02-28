#ifndef _2ccb5331_6101_11e2_0ab6_0800573fac09
#define _2ccb5331_6101_11e2_0ab6_0800573fac09

#include "Util.h"
#include "Types.h"
#include "ISeq_block_reader.h"
#include "IBlock_access.h"

/**
 * Random block reader implementation.
 */
namespace layer1
{
  namespace io
  {
    class File_seq_block_r: public ISeq_block_reader
    {
      public:       

        //--CONSTRUCTORS--
        explicit File_seq_block_r() throw();

        //--DESTRUCTOR--
        ~File_seq_block_r();

        void load_file(const char *file_name, i32 &out_error);

        void reset_offset_block() override; 

        void add_offset_block(i32 offset) override;

        void read_block(layer0::data::IBlock_access &block_result, i32 &out_error) override;

        bool has_more() const override;

        ui64 get_size() const override;

        ui64 get_actual_offset() const override;
        
      private:
        ui64 block_offset;
        FILE *file_ptr;
        ui64 total_size;

        DISABLE_EQUAL_OPERATOR(File_seq_block_r);
        DISABLE_COPY_CONSTRUCTOR(File_seq_block_r);
    };
  }
}
#endif
