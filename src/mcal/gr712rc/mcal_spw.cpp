///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_spw.h>

void mcal::spw::init(const config_type*)
{

  // Enable cores in clock gatting unit!!!
  constexpr std::uint32_t enable_all_mask = UINT32_C(0x0000007E);
  constexpr std::uint32_t reset_all_mask  = UINT32_C(0xFFFFFF87);

  mcal::reg::access<addr_type,
                    reg_type,
                    mcal::reg::pcm_unlock_address,
                    enable_all_mask>::reg_or();

  mcal::reg::access<addr_type,
                    reg_type,
                    mcal::reg::pcm_enable_address,
                    enable_all_mask>::reg_or();

  mcal::reg::access<addr_type,
                    reg_type,
                    mcal::reg::pcm_reset_address,
                    reset_all_mask>::reg_and();

  mcal::reg::access<addr_type,
                    reg_type,
                    mcal::reg::pcm_unlock_address,
                    reset_all_mask>::reg_and();
}

