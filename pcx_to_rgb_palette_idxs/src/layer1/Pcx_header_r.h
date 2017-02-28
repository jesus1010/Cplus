#ifndef _8B0DB500_FE6F11E1A21F0800200C9A61
#define _8B0DB500_FE6F11E1A21F0800200C9A61

#include "Types.h"
#include "Util.h"
#include "Log.h"

/**
 * Pcx header reader.
 */
namespace layer1
{
  namespace img
  {

    class Pcx_header_r
    {
      public:
        static const ui16 HEADER_SIZE= 128; // size in bytes
        static const ui8 HEADER_OFFSET= 0; // size in bytes
        static const ui8 PCX_ID_OFFSET= 0; // size in bytes
        static const ui8 PCX_ID= 0x0a; // size in bytes
        static const ui8 DIR_BITS_PER_PIXEL= 3;
        static const ui8 DIR_MIN_X= 4;
        static const ui8 DIR_MIN_Y= 6;
        static const ui8 DIR_MAX_X= 8;
        static const ui8 DIR_MAX_Y= 10;
        static const ui8 DIR_NUMBER_PLANES= 65;
        static const ui8 DIR_B_PLANE_LINE= 66; // bytes per plane line

        //--CONSTRUCTORS--
        explicit Pcx_header_r();
        
        //--DESTRUCTORS--
        virtual ~Pcx_header_r();

        //--CUSTOM METHODS--
        void load_header(const char *file_name, i32 &out_error);
        ui8 get_bits_per_pixel() const {return this->bits_per_pixel;}
        ui8 get_number_planes() const {return this->number_planes;}
        ui16 get_min_x() const {return this->min_x;}
        ui16 get_min_y() const {return this->min_y;}
        ui16 get_max_x() const {return this->max_x;}
        ui16 get_max_y() const {return this->max_y;}

      private:
        ui8 bits_per_pixel;
        ui8 number_planes;
        ui16 b_plane_line;
        ui16 min_x;
        ui16 min_y;
        ui16 max_x;
        ui16 max_y;

        DISABLE_COPY_CONSTRUCTOR(Pcx_header_r);
        DISABLE_EQUAL_OPERATOR(Pcx_header_r); 
     };
   }
}
#endif

