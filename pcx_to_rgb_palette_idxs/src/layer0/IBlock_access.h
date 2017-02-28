#ifndef _1B0DB500_FE6F11E1A21F0100400C9A62
#define _1B0DB500_FE6F11E1A21F0100400C9A62

#include "Types.h"
#include "Log.h"

namespace layer0
{
  namespace data
  {
    class IBlock_access
    {   
      public:
        virtual i8* get_raw()=0;     
        virtual ui32 get_size() const=0;
        virtual ui32 get_capacity() const=0;
        virtual void set_size(ui32 in_size)=0;
        virtual void add_size_offset(i32 offset)=0;
        virtual i8 get_last_data() const=0;

        virtual ~IBlock_access()
        {
          LOG_DEBUG(L0,"[>>]");
          LOG_DEBUG(L0,"[<<]");
        }
    };
  }
}

#endif