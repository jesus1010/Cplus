
#include "Log.h"
#include "File_seq_block_r.h"

using namespace std;

namespace layer1
{
  namespace io
  {
    //--PUBLIC--
    //--constructors
    File_seq_block_r::File_seq_block_r() throw():
      block_offset(0), file_ptr(NULL), total_size(0)
    {
       LOG_DEBUG(L1,"[>>]");
       LOG_DEBUG(L1,"[<<]");
    }

    // CUSTOM METHODS
    void File_seq_block_r::load_file(const char *file_name, i32 &out_error)
    {
      LOG_DEBUG(L1,"[>>]");

      file_ptr= layer0::util::open_file(file_name, "rb", out_error);
      layer0::util::get_size(file_name, this->total_size, out_error);

      LOG_DEBUG(L1,"[<<]");
    }

    void File_seq_block_r::reset_offset_block()
    {
      LOG_DEBUG(L1,"[>>]");

      this->block_offset= 0;

      LOG_DEBUG(L1,"[<<]|%lli", this->block_offset);
    }

    void File_seq_block_r::read_block(layer0::data::IBlock_access &block_result, i32 &out_error)
    { 
      LOG_DEBUG(L1,"[>>]");

      ui64 block_bytes_reads;
      layer0::util::read_block(this->file_ptr,
                              block_result.get_raw(),
                              block_result.get_capacity(),
                              this->block_offset,
                              this->total_size,
                              block_bytes_reads,
                              out_error);
      
      this->block_offset += block_bytes_reads;
      block_result.set_size(layer0::util::cast_ui64_to_ui32(block_bytes_reads));

      LOG_DEBUG(L1,"[<<]|%lli|", block_bytes_reads);
    }
    
    bool File_seq_block_r::has_more() const 
    {
      LOG_DEBUG(L1,"[>>]");
      
      bool result = this->block_offset < this->total_size;

      LOG_DEBUG(L1,"[<<]|%d|", result);
      return result;
    }

    ui64 File_seq_block_r::get_size() const
    {
      LOG_DEBUG(L1,"[>>]");
      LOG_DEBUG(L1,"[<<]|%lli", this->total_size);
      return this->total_size;
    }

    void File_seq_block_r::add_offset_block(i32 offset)
    {
      LOG_DEBUG(L1,"[>>]");

      i32 b_offset= layer0::util::cast_ui32_to_i32(this->block_offset);
      this->block_offset = layer0::util::cast_i32_to_ui64(b_offset + offset);

      LOG_DEBUG(L1,"[<<]|%lli|", this->block_offset);
    }
  
    ui64 File_seq_block_r::get_actual_offset() const
    {
      LOG_DEBUG(L1,"[>>]");      
      LOG_DEBUG(L1,"[<<]|%lli|", this->block_offset); 
      return this->block_offset;
    }

    // DESTRUCTOR
    File_seq_block_r::~File_seq_block_r()
    {
      LOG_DEBUG(L1,"[>>]");

      layer0::util::close_file(&(this->file_ptr));

      LOG_DEBUG(L1,"[<<]|%p", static_cast<void*>(this->file_ptr));
    }      
  }
}

