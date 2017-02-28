#include "Errors_env.h"
#include "Log.h"
#include "Pcx_file_RGB_palette_idxs_seq_br.h"
#include "Pcx_header_r.h"
#include "Seq_block.h"

using namespace std;

namespace layer2
{
  namespace img
  {
    //--PUBLIC--
    //--constructors
    Pcx_file_RGB_palette_idxs_seq_br::Pcx_file_RGB_palette_idxs_seq_br(): 
      reads_points(0),
      total_points(0)
    {
      LOG_DEBUG(L2,"[>>]");
      LOG_DEBUG(L2,"[<<]");
    }
    
    void Pcx_file_RGB_palette_idxs_seq_br::load_file(const char *file_name, i32 &out_error)
    {
      LOG_DEBUG(L2,"[>>]");      

      //calculate total points
      {
        layer1::img::Pcx_header_r pcx_header;
        pcx_header.load_header(file_name, out_error);          
        ui64 max_x= static_cast<ui64>(pcx_header.get_max_x() + 1);
        ui64 max_y= static_cast<ui64>(pcx_header.get_max_y() + 1);
        this->total_points= max_x * max_y;
      }
      rle_reader.load_file(file_name, out_error);
      rle_reader.add_offset_block(layer1::img::Pcx_header_r::HEADER_SIZE);
      LOG_DEBUG(L2,"[<<]");
    }

    //--override
    void Pcx_file_RGB_palette_idxs_seq_br::read_block(layer0::data::IBlock_access &out_block, 
                                                      i32 &out_error)
    {
      LOG_DEBUG(L2,"[>>]");    
      ui64 decoded_points;
      
      //load and decode rle
      {
        layer1::io::Seq_block rle_block;
        rle_reader.read_block(rle_block, out_error);     

        //ajusted rle offset, and rle block if last data in rle buffer it's a counter 
        if (layer0::util::is_rle_counter(rle_block.get_last_data()))
        {
          rle_block.add_size_offset(-1);
          rle_reader.add_offset_block(-1);        
        }
        layer0::util::decode_rle(decoded_points,
                                 rle_block.get_raw(),
                                 rle_block.get_size(),
                                 out_block.get_raw(),                               
                                 out_error);        
      }

      //ajust decoding not exceding max points, we could be read palette data 
      {
        ui64 outblock_offset= layer0::util::add_and_get_offset(this->reads_points, decoded_points, this->total_points);
        decoded_points -=outblock_offset;
        out_block.set_size(layer0::util::cast_ui64_to_ui32(decoded_points));
        this->reads_points= layer0::util::add_and_adjust_max_size(this->reads_points, decoded_points, this->total_points);
      }  
      LOG_DEBUG(L2,"[<<]");
    }
    
    //--override
    bool Pcx_file_RGB_palette_idxs_seq_br::has_more() const
    {
      LOG_DEBUG(L2,"[>>]");
      bool result= layer0::util::is_less_than(this->reads_points, this->total_points);
      LOG_DEBUG(L2,"[<<]|%d", result);
      return result;
    }

    //--destructor
    Pcx_file_RGB_palette_idxs_seq_br::~Pcx_file_RGB_palette_idxs_seq_br()
    {
      LOG_DEBUG(L2,"[>>]");
      LOG_DEBUG(L2,"[<<]");
    }
  }
}

