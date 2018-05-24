#include <po_hi_gqueue.h>
#include <po_hi_types.h>
#include <request.h>
#include <deployment.h>
#include "subprograms.h"
#include <po_hi_task.h>
#include <po_hi_main.h>
#include <types.h>
#include <activity.h>
#include <po_hi_transport.h>
/*****************************************************/
/*  This file was automatically generated by Ocarina */
/*  Do NOT hand-modify this file, as your            */
/*  changes will be lost when you re-run Ocarina     */
/*****************************************************/
__po_hi_port_id_t __po_hi_consumer_woffsets[__po_hi_consumer_nb_ports];
__po_hi_port_id_t __po_hi_consumer_offsets[__po_hi_consumer_nb_ports];
__po_hi_port_id_t __po_hi_consumer_used_size[__po_hi_consumer_nb_ports];
__po_hi_port_id_t __po_hi_consumer_empties[__po_hi_consumer_nb_ports];
__po_hi_port_id_t __po_hi_consumer_first[__po_hi_consumer_nb_ports];
__po_hi_request_t __po_hi_consumer_recent[__po_hi_consumer_nb_ports];
__po_hi_port_t __po_hi_consumer_queue[0 * sizeof (__po_hi_request_t)];
__po_hi_uint16_t __po_hi_consumer_total_fifo_size = 0;
__po_hi_local_port_t __po_hi_consumer_history[0];
__po_hi_port_id_t __po_hi_consumer_n_dest[__po_hi_consumer_nb_ports] = {0};
__po_hi_port_id_t __po_hi_consumer_fifo_size[__po_hi_consumer_nb_ports] = {__PO_HI_GQUEUE_FIFO_INDATA};
__po_hi_port_t* __po_hi_consumer_destinations[__po_hi_consumer_nb_ports] = {NULL};

/*!
 * \fn void consumer_deliver (__po_hi_request_t* request)
 * \brief Function that delivers requests to the task consumer
 *
 * When the generated application received a request, it calls a main delivery
 *  function that redirects to localfunctions for each task. This function 
 * (consumer_deliver) stores the incoming request for the taskconsumer
 */
void consumer_deliver 
    (__po_hi_request_t* request)
{

  switch (request->port)
  {
    case consumer_global_data_sink:
    {
      __po_hi_gqueue_store_in (pr_b_consumer_k, consumer_local_data_sink, request);

      break;
    }
    default:
    {
      break;
    }
  }
}


/*!
 * \fn void* consumer_job (void)
 * \brief Function executed by the task consumer
 *
 * This function is executed as soon as the task  is created. It performs the 
 * following operations:  Receive incoming data,  Execute tasks subprograms,  
 * Send output data.
 */
/*  Periodic task : Consumer*/
/*  Get the IN ports values*/
void* consumer_job (void)
{
  static __po_hi_request_t data_sink_request;

  __po_hi_gqueue_init (pr_b_consumer_k, __po_hi_consumer_nb_ports, __po_hi_consumer_queue, __po_hi_consumer_fifo_size, __po_hi_consumer_first, __po_hi_consumer_offsets, __po_hi_consumer_woffsets, __po_hi_consumer_n_dest, __po_hi_consumer_destinations, __po_hi_consumer_used_size, __po_hi_consumer_history, __po_hi_consumer_recent, __po_hi_consumer_empties, __po_hi_consumer_total_fifo_size);
  
/*!
 * Waiting for other tasks initialization
 */
  __po_hi_wait_initialization ();
  __po_hi_compute_next_period (pr_b_consumer_k);
  
/*!
 * Waiting for the first dispatch instant
 */
  __po_hi_wait_for_next_period (pr_b_consumer_k);
  
/*!
 * Task body
 */
  while (1)
  {
    /* :: Yes if commentary :: */if (__po_hi_gqueue_get_count (pr_b_consumer_k, consumer_local_data_sink))
    {
          __po_hi_gqueue_get_value (pr_b_consumer_k, consumer_local_data_sink, &(data_sink_request));
      __po_hi_gqueue_next_value (pr_b_consumer_k, consumer_local_data_sink);

    }
    /*  Call implementation*/
    software__consume_spg (data_sink_request.vars.consumer_global_data_sink.consumer_global_data_sink);
    __po_hi_wait_for_next_period (pr_b_consumer_k);
  }
}

__po_hi_port_t __po_hi_result_producer_data_source_local_destinations[1] = {result_consumer_global_data_sink};
__po_hi_port_id_t __po_hi_result_producer_woffsets[__po_hi_result_producer_nb_ports];
__po_hi_port_id_t __po_hi_result_producer_offsets[__po_hi_result_producer_nb_ports];
__po_hi_port_id_t __po_hi_result_producer_used_size[__po_hi_result_producer_nb_ports];
__po_hi_port_id_t __po_hi_result_producer_empties[__po_hi_result_producer_nb_ports];
__po_hi_port_id_t __po_hi_result_producer_first[__po_hi_result_producer_nb_ports];
__po_hi_request_t __po_hi_result_producer_recent[__po_hi_result_producer_nb_ports];
__po_hi_port_t __po_hi_result_producer_queue[0 * sizeof (__po_hi_request_t)];
__po_hi_uint16_t __po_hi_result_producer_total_fifo_size = 0;
__po_hi_local_port_t __po_hi_result_producer_history[0];
__po_hi_port_id_t __po_hi_result_producer_n_dest[__po_hi_result_producer_nb_ports] = {1};
__po_hi_port_id_t __po_hi_result_producer_fifo_size[__po_hi_result_producer_nb_ports] = {__PO_HI_GQUEUE_FIFO_OUT};
__po_hi_port_t* __po_hi_result_producer_destinations[__po_hi_result_producer_nb_ports] = {__po_hi_result_producer_data_source_local_destinations};

/*!
 * \fn void* result_producer_job (void)
 * \brief Function executed by the task result_producer
 *
 * This function is executed as soon as the task  is created. It performs the 
 * following operations:  Receive incoming data,  Execute tasks subprograms,  
 * Send output data.
 */
/*  Periodic task : Result_Producer*/
void* result_producer_job (void)
{
  static software__alpha_type data_source_request_var;
  static __po_hi_request_t data_source_request;
  __po_hi_int32_t error;

  __po_hi_gqueue_init (pr_b_result_producer_k, __po_hi_result_producer_nb_ports, __po_hi_result_producer_queue, __po_hi_result_producer_fifo_size, __po_hi_result_producer_first, __po_hi_result_producer_offsets, __po_hi_result_producer_woffsets, __po_hi_result_producer_n_dest, __po_hi_result_producer_destinations, __po_hi_result_producer_used_size, __po_hi_result_producer_history, __po_hi_result_producer_recent, __po_hi_result_producer_empties, __po_hi_result_producer_total_fifo_size);
  
/*!
 * Waiting for other tasks initialization
 */
  __po_hi_wait_initialization ();
  __po_hi_compute_next_period (pr_b_result_producer_k);
  
/*!
 * Waiting for the first dispatch instant
 */
  __po_hi_wait_for_next_period (pr_b_result_producer_k);
  
/*!
 * Task body
 */
  while (1)
  {
    /*  Call implementation*/
    software__produce_spg (&(data_source_request_var));
    /*  Set the OUT port values*/
    data_source_request.vars.result_producer_global_data_source.result_producer_global_data_source = data_source_request_var;
    data_source_request.port = result_producer_global_data_source;
    __po_hi_gqueue_store_out (pr_b_result_producer_k, result_producer_local_data_source, &(data_source_request));
    /*  Send the OUT ports*/
    error =
     __po_hi_send_output (pr_b_result_producer_k, result_producer_global_data_source);
    __po_hi_wait_for_next_period (pr_b_result_producer_k);
  }
}


/*!
 * \fn void __po_hi_main_deliver (__po_hi_request_t* request)
 * \brief Used to deliver request to the appropriate ports
 *
 * This function takes a request as argument (\arg request) and calls the 
 * appropriate function for its delivery.To specify which function should be 
 * called, it extracts the receiver entity using the destination port.
 */
void __po_hi_main_deliver 
    (__po_hi_request_t* request)
{
  __po_hi_entity_t entity;

  entity = __po_hi_get_entity_from_global_port (request->port);
  switch (entity)
  {
    case pr_b_consumer_k_entity:
    {
      consumer_deliver (request);

      break;
    }
    default:
    {
      break;
    }
  }
}

