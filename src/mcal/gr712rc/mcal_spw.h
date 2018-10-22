/**
 * @file mcal_spw.h
 * @brief Spacewire comunication.
 * @description Manages de spacewire interface of the sam4s
 * @note Documentation on schematic pag. 10
 */

#ifndef _MCAL_GRSPW_GR712RC_ESC_H_
#define _MCAL_GRSPW_GR712RC_ESC_H_

#include <cstdint>
#include <mcal_cpu.h>
#include <mcal_reg_access.h>
#include <algorithm>


namespace mcal
{
namespace spw
{

typedef void config_type;

//void init(const config_type*);

template <typename port_type,// std::uint32_t
          typename bval_type,// std::uint8_t
          port_type port>
class  spw_communication
{
 public:
  typedef std::uint32_t addr_type;
  typedef std::uint32_t reg_type;
  /*
    typedef array<std::uint32_t,2> recv_descriptor_type;
    typedef array<std::uint32_t,4> send_descriptor_type;

    typedef array<std::uint32_t,16> header_buffer_type;
    typedef array<std::uint32_t,256> data_buffer_type;
    typedef array<std::uint32_t,4> packet_buffer_type;
  */
  typedef std::uint32_t *recv_descriptor_type;
  typedef std::uint32_t *send_descriptor_type;

  typedef std::uint32_t *header_buffer_type;
  typedef std::uint32_t *data_buffer_type;
  typedef std::uint32_t *packet_buffer_type;


  /**
   * @brief Init the Spacewire IP Core.
   */
  spw_communication() : send_is_active(false)
  {


    // Set Packet Maximun Length. 16 MB = 16777216 = 0x1000000
    //                             1 KB = 1024     = 0x400
    mcal::reg::access<addr_type,
                      reg_type,
                      dma_maxlen_register,
                      static_cast<std::uint32_t>(UINT32_C(0x00000400))>::reg_set();

    // Set the base addr of the Spacewire Recv Descriptor Table.
    configure_recv_descriptors( number_of_recv_desciptor);
    mcal::reg::access<addr_type,
                      reg_type,
                      dma_rx_descriptor_register,
                      recv_descriptor_table_base>::reg_set();

    // Set the base addr of the Spacewire Transmit Descriptor Table.
    configure_send_descriptors( number_of_send_desciptor);
    mcal::reg::access<addr_type,
                      reg_type,
                      dma_tx_descriptor_register,
                      send_descriptor_table_base>::reg_set();
    
    // Set Node Address to 
    mcal::reg::access<addr_type,
                      reg_type,
                      node_addr_register,
                      spw_node_addr>::reg_set();

    // Set Node Address to 
    mcal::reg::access<addr_type,
                      reg_type,
                      baudrate_register,
                      0x0909>::reg_set();

    mcal::reg::access<addr_type,
                      reg_type,
                      ctrl_register,
                      0x0022>::reg_set();


  }

  bool link_state()
  {
    return ( (get_link_status() >> 21) & 0x7 );
  }

  std::uint32_t get_link_status()
  {
    const std::uint32_t link_status =  mcal::reg::access<addr_type,
                                                         reg_type,
                                                         status_register>::reg_get();

    return link_status;
  }

  /**
   * @brief Add data to the actual descriptor and enable the transfer.
   */
  bool send(const bval_type byte_to_send)
  {

    if ( send_is_active )
    {
      return false;
    }
    else{
      send_is_active = true;

      // Get the descriptor in use.
      const std::uint32_t send_descriptor_address =  mcal::reg::access<addr_type,
                                                                       reg_type,
                                                                       dma_tx_descriptor_register>::reg_get();

      const std::uint32_t desc_number = (send_descriptor_address & 0x3FF) >> 4;

      // Fill the header and data.
      send_descriptor_type desc_ptr =  send_descriptor_table + 4*desc_number;

      std::uint32_t * hbuff = reinterpret_cast<std::uint32_t *>(* (desc_ptr+1)); // Stores the pointer to the header_buffer.
      std::uint32_t * dbuff = reinterpret_cast<std::uint32_t *>(* (desc_ptr+3));
      std::uint32_t dbuff_size = (* (desc_ptr+2)); //0x400;Size of the data max.
      std::uint32_t hbuff_size = 10;

      for (std::uint32_t it = 0; it< 4; ++it)
      {
        *hbuff = 0xABACAD00 | it;
        hbuff ++;
      }

      *dbuff = byte_to_send;

      if (desc_number < (number_of_send_desciptor-1) ) 
        (* desc_ptr ) = 0x0031000 | hbuff_size;
      else
        (* desc_ptr ) = 0x0033000 | hbuff_size;
      /*
      mcal::reg::dynamic_access<addr_type,
                                reg_type>::reg_set(data_buffer, static_cast<bval_type>(byte_to_send));
*/

    // enable the transmision of the actual descriptor.
    mcal::reg::access<addr_type,
                      reg_type,
                      dma_ctrl_register,
                      static_cast<std::uint32_t>(UINT32_C(0x00000001))>::reg_or();

      send_is_active = false;
    }
    return true;
  }

  template<typename send_iterator_type>
  bool send_n(send_iterator_type first,
              send_iterator_type last)
  {
    bool send_result = true;

    typedef typename
        std::iterator_traits<send_iterator_type>::value_type
        send_value_type;

    const send_value_type value(*first);
    std::uint32_t dbuff_size = sizeof(send_value_type)*(last-first);

    send_is_active = true;

      // Get the descriptor in use.
    const std::uint32_t send_descriptor_address =  mcal::reg::access<addr_type,
                                                                     reg_type,
                                                                     dma_tx_descriptor_register>::reg_get();

    const std::uint32_t desc_number = (send_descriptor_address & 0x3FF) >> 4;

    // Fill the descriptor data, control, header_ptr and data_ptr.
    send_descriptor_type desc_ptr =  send_descriptor_table + 4*desc_number;

    std::uint32_t hbuff_size = 8;
    (* (desc_ptr+1)) = reinterpret_cast<std::uint32_t>(first);   //Header is the first 16Bytes of the buffer.
    (* (desc_ptr+2)) = dbuff_size-0x10; //0x400;Size of the data max.
    (* (desc_ptr+3)) = reinterpret_cast<std::uint32_t>(first+0x10); //Data is the rest of the packet.

    if (desc_number < (number_of_send_desciptor-1) ) 
      (* desc_ptr ) = 0x0031000 | hbuff_size;
    else
      (* desc_ptr ) = 0x0033000 | hbuff_size;


    // enable the transmision of the actual descriptor.
    mcal::reg::access<addr_type,
                      reg_type,
                      dma_ctrl_register,
                      static_cast<std::uint32_t>(UINT32_C(0x00000001))>::reg_or();
    send_is_active = false;

    return send_result;
  }

  bool recv(bval_type &byte_to_recv)
  {
    /*
    byte_to_recv = mcal::reg::access<addr_type,
                                     reg_type,
                                     input_data_register>::reg_get();

*/
      for (int i=0; i < 1000; ++i)
        for (int j=0; j< 100; ++j)
        {
          mcal::cpu::nop();
        }


    return true;
  }

  //Checks if there is data to receive.
  bool receive_ready()
  {
    reg_type recv_desc_status = 0x123; /*mcal::reg::access<addr_type,
                                             reg_type,
                                             uart_status_register>::reg_get();*/
    return (recv_desc_status & (0x1 << 0));
  }

  
  /** 
   * @return Address of the descriptor table.
   */
  bool configure_send_descriptors(std::uint32_t number_descriptors)
  {
    std::uint32_t desc_number;
    send_descriptor_type desc_it =  send_descriptor_table;

    desc_number = 0;
    while( desc_number < (number_descriptors-1))
    {
      (* desc_it )    = 0x003000F;
      (* (desc_it+1)) = header_buffer_base_addr + desc_number*header_max_length;
      (* (desc_it+2)) = 0x4; //0x400;
      (* (desc_it+3)) = data_buffer_base_addr + desc_number*data_max_length;

      desc_it += 4;
      desc_number ++;
    }

    (* desc_it ) = 0x003200F;
    (* (desc_it+1)) = header_buffer_base_addr + desc_number*header_max_length;
    (* (desc_it+2)) = 0x4; //0x400;
    (* (desc_it+3)) = data_buffer_base_addr + desc_number*data_max_length;
      

    return true;
  }

  // Esta funcion deberia hacer su trabajo mediante, iteradores.
  // It should return the address of the recv_descritor table, after build it.
  bool configure_recv_descriptors(std::uint32_t number_descriptors)
  {

    std::uint32_t it = 0;
    std::uint32_t desc_number;
    recv_descriptor_type desc_it =  recv_descriptor_table;

    desc_number = 0;
    while( desc_number < (number_descriptors-1))
    {
      (* desc_it )    = 0x02000000;
      (* (desc_it+1)) = packet_buffer_base_addr + desc_number*packet_max_length;

      desc_it += 2;
      desc_number ++;
    }

    (* desc_it ) = 0x003300F;
    (* (desc_it+1)) = packet_buffer_base_addr + desc_number*packet_max_length;

    return true;
  }

 private:

  bool send_is_active;

  static constexpr std::uint32_t packet_max_length = 0x400UL; // 1024 Bytes.
  static constexpr std::uint32_t header_max_length = 0x10UL; // 16 Bytes.
  static constexpr std::uint32_t data_max_length   = 0x400UL; // 1024 Bytes.

  static constexpr std::uint32_t recv_descriptor_table_base = 0x40001000; // Max Descriptor : 128*8 = 1024
  static constexpr std::uint32_t send_descriptor_table_base = 0x40002000;
  static constexpr std::uint32_t header_buffer_base_addr    = 0x40010000;
  static constexpr std::uint32_t data_buffer_base_addr      = 0x40020000;
  static constexpr std::uint32_t packet_buffer_base_addr    = 0x40030000;

  static constexpr std::uint32_t number_of_recv_desciptor   = 5;
  static constexpr std::uint32_t number_of_send_desciptor   = 5;

  static constexpr std::uint32_t spw_node_addr = 0xFE;

  //Each of this should be build in base a fill using only the aligned part.
  recv_descriptor_type  recv_descriptor_table = reinterpret_cast<recv_descriptor_type>( recv_descriptor_table_base );
  send_descriptor_type  send_descriptor_table = reinterpret_cast<send_descriptor_type>( send_descriptor_table_base );
  header_buffer_type    header_buffer           = reinterpret_cast<header_buffer_type>(  header_buffer_base_addr );
  data_buffer_type      data_buffer               = reinterpret_cast<data_buffer_type>(  data_buffer_base_addr );
  packet_buffer_type    packet_buffer           = reinterpret_cast<packet_buffer_type>(  packet_buffer_base_addr );


  static constexpr addr_type ctrl_register                = addr_type(port + 0x00UL);
  static constexpr addr_type status_register              = addr_type(port + 0x04UL);

  static constexpr addr_type node_addr_register           = addr_type(port + 0x08UL);
  static constexpr addr_type baudrate_register            = addr_type(port + 0x0CUL);
  static constexpr addr_type dest_key_register            = addr_type(port + 0x10UL);
  static constexpr addr_type time_register                = addr_type(port + 0x14UL);

  static constexpr addr_type dma_ctrl_register            = addr_type(port + 0x20UL);
  static constexpr addr_type dma_maxlen_register          = addr_type(port + 0x24UL);
  static constexpr addr_type dma_tx_descriptor_register   = addr_type(port + 0x28UL);
  static constexpr addr_type dma_rx_descriptor_register   = addr_type(port + 0x2CUL);
  static constexpr addr_type dma_addr_register            = addr_type(port + 0x30UL);

};

/*
extern  spw_communication<std::uint32_t, 
                          std::uint32_t,
                          mcal::reg::grspw0_base_address> the_spw0;
*/
}
}

#endif //  _MCAL_GRSPW_GR712RC_ESC_H_
