#include "Errors_env.h"
#include "Pcx_header_r.h"

using namespace std;
namespace layer1
{
  namespace img
  {
    //--PUBLIC--
    Pcx_header_r::Pcx_header_r():
      bits_per_pixel(0), 
      number_planes(0), 
      b_plane_line(0), 
      min_x(0), 
      min_y(0),
      max_x(0), 
      max_y(0)
    {
      LOG_DEBUG(L1,"[>>]");
      LOG_DEBUG(L1,"[<<]");
    }

    void Pcx_header_r::load_header(const char *file_name, i32 &out_error)
    {
      LOG_DEBUG(L1,"[>>]");

      i8 rawHeader[Pcx_header_r::HEADER_SIZE];
      
      //read raw header and check
      {
        layer0::util::clear_mem(rawHeader, Pcx_header_r::HEADER_SIZE);
        FILE *file_ptr= layer0::util::open_file(file_name, "rb", out_error);

        ui64 file_size;
        layer0::util::get_size(file_name, file_size, out_error);

        ui64 block_bytes_reads;
        layer0::util::read_block(file_ptr,
                               rawHeader,
                               Pcx_header_r::HEADER_SIZE,
                               Pcx_header_r::HEADER_OFFSET,
                               file_size,
                               block_bytes_reads,
                               out_error);
      
        layer0::util::check_pcx_header_size(block_bytes_reads, Pcx_header_r::HEADER_SIZE, out_error);
      
        i8 pcx_id_read= rawHeader[Pcx_header_r::PCX_ID_OFFSET];
        layer0::util::check_pcx_header_id(pcx_id_read, Pcx_header_r::PCX_ID, out_error);
        layer0::util::close_file(&(file_ptr));      
      }

      // load attributes
      this->b_plane_line= static_cast<ui8>((rawHeader[Pcx_header_r::DIR_B_PLANE_LINE + 1 ] << 8) 
                          + (rawHeader[Pcx_header_r::DIR_B_PLANE_LINE]));
      this->bits_per_pixel= static_cast<ui8>(rawHeader[Pcx_header_r::DIR_BITS_PER_PIXEL]);
      this->number_planes= static_cast<ui8>(rawHeader[Pcx_header_r::DIR_NUMBER_PLANES]);
      this->min_x= static_cast<ui16>((rawHeader[Pcx_header_r::DIR_MIN_X + 1] << 8) + rawHeader[Pcx_header_r::DIR_MIN_X]);
      this->min_y= static_cast<ui16>((rawHeader[Pcx_header_r::DIR_MIN_Y + 1] << 8) + rawHeader[Pcx_header_r::DIR_MIN_Y]);
      this->max_x= static_cast<ui16>((rawHeader[Pcx_header_r::DIR_MAX_X + 1] << 8) + rawHeader[Pcx_header_r::DIR_MAX_X]);
      this->max_y= static_cast<ui16>((rawHeader[Pcx_header_r::DIR_MAX_Y + 1] << 8) + rawHeader[Pcx_header_r::DIR_MAX_Y]);
      
      LOG_DEBUG(L1,"[<<]");
    }

    Pcx_header_r::~Pcx_header_r()
    {
      LOG_DEBUG(L1,"[>>]");
      LOG_DEBUG(L1,"[<<]");
    }  
  } 
}

