/*
 * This is a part of PolyORB-HI-C distribution, a minimal
 * middleware written for generated code from AADL models.
 * You should use it with the Ocarina toolsuite.
 *
 * For more informations, please visit http://ocarina.enst.fr
 *
 * Copyright (C) 2010-2011, European Space Agency (ESA).
 */


#include <deployment.h>
/* included files from the generated code */

#include <po_hi_config.h>
#include <po_hi_common.h>
#include <po_hi_returns.h>
#include <po_hi_task.h>
#include <po_hi_debug.h>
#include <po_hi_protected.h>
/* included files from PolyORB-HI-C */

#if defined (POSIX) || defined (RTEMS_POSIX) || defined (XENO_POSIX)
#include <pthread.h>
/* POSIX files */

pthread_cond_t cond_init;
pthread_mutex_t mutex_init;
#endif

#ifdef RTEMS_PURE
rtems_id __po_hi_main_initialization_barrier;
#endif

#if defined (XENO_NATIVE)
#include <native/cond.h>
#include <native/mutex.h>
RT_COND   cond_init;
RT_MUTEX  mutex_init;

RT_TASK*  main_task_id;
/*
 * If we use the XENO_NATIVE skin, then, the main task
 * is considered as non real-time and cannot lock
 * mutexes that are used by real-time threads.
 * Then, we need to differenciate operations
 * between the main task and the other tasks.
 *
 * For that reason, the main task does not wait for
 * the initialization of the other tasks. The 
 * __po_hi_wait_initialization just passes when it is
 * called from the main task. To do that, we need
 * to differentiate the main task from the other,
 * we do that by getting the main task descriptor
 * address in the main_task_id variable.
 *
 * Moreover, when using the XENO_NATIVE API, we
 * remove one task to initialize (the main task).
 * Only generated/created tasks wait for their mutual
 * initialization.
 */
#endif



int __po_hi_initialized_tasks = 0;
/* The barrier is initialized with __PO_HI_NB_TASKS +1
 * members, because the main function must pass the barrier.
 *
 * Be careful: for the XENO_NATIVE API, we decrement
 * the __po_hi_nb_tasks_to_init variable since the main task
 * does not wait for the other tasks to be initialized.
 */
int __po_hi_nb_tasks_to_init = __PO_HI_NB_TASKS + 1;

void __po_hi_initialize_add_task ()
{
      __DEBUGMSG ("[MAIN] Add a task to initialize\n");
      __po_hi_nb_tasks_to_init++;
}


int __po_hi_initialize_early ()
{
#if defined (XENO_POSIX) || defined (XENO_NATIVE)
   /*
    * Once initialization has been done, we avoid ALL 
    * potential paging operations that can introduce
    * some indeterministic timing behavior.
    */

   #include <sys/mman.h>
   mlockall (MCL_CURRENT|MCL_FUTURE);
#endif

#if defined (XENO_NATIVE)
   main_task_id = rt_task_self ();

   __po_hi_nb_tasks_to_init--;
   /*
    * If we are using the XENO_NATIVE skin, we need
    * to differentiate the main task (that is non real-time)
    * from the others since the main task cannot use
    * the services and operates on resources of real-time tasks.
    * In addition, we decrement the amount of tasks to
    * initialize since the main task does not wait
    * for the initialization of the other tasks.
    */
#endif

#if defined (POSIX) || defined (RTEMS_POSIX) || defined (XENO_POSIX)
   pthread_mutexattr_t mutex_attr;
   if (pthread_mutexattr_init (&mutex_attr) != 0)
   {
      __DEBUGMSG ("[MAIN] Unable to init mutex attributes\n");
   }

#ifdef RTEMS_POSIX
   if (pthread_mutexattr_setprioceiling (&mutex_attr, 50) != 0)
   {
      __DEBUGMSG ("[MAIN] Unable to set priority ceiling on mutex\n");
   }
#endif

   if (pthread_mutex_init (&mutex_init, &mutex_attr) != 0 )
    {
      __DEBUGMSG ("[MAIN] Unable to init pthread_mutex\n");
      return (__PO_HI_ERROR_PTHREAD_MUTEX);
    }

  __DEBUGMSG ("[MAIN] Have %d tasks to init\n", __po_hi_nb_tasks_to_init);

  if (pthread_cond_init (&cond_init, NULL) != 0)
  {
     return (__PO_HI_ERROR_PTHREAD_COND);
  }
#endif

#if defined (XENO_NATIVE)
   if (rt_cond_create (&cond_init, NULL))
   {
      __DEBUGMSG ("[MAIN] Unable to init the initialization condition variable \n");
      return (__PO_HI_ERROR_PTHREAD_MUTEX);
   }

  if (rt_mutex_create (&mutex_init, NULL) != 0)
  {
      __DEBUGMSG ("[MAIN] Unable to init the initialization mutex variable \n");
     return (__PO_HI_ERROR_PTHREAD_COND);
  }
#endif


#if defined (RTEMS_POSIX) || defined (RTEMS_PURE)
#include <rtems/rtems/clock.h>
  rtems_status_code ret;
  rtems_time_of_day time;

  time.year   = 1988;
  time.month  = 12;
  time.day    = 31;
  time.hour   = 9;
  time.minute = 1;
  time.second = 10;
  time.ticks  = 0;

  ret = rtems_clock_set( &time );
  if (ret != RTEMS_SUCCESSFUL)
  {
     __DEBUGMSG ("[MAIN] Cannot set the clock\n");
     return __PO_HI_ERROR_CLOCK;
  }
#endif

#ifdef RTEMS_PURE
  __DEBUGMSG ("[MAIN] Create a barrier that wait for %d tasks\n", __po_hi_nb_tasks_to_init);
   
  ret = rtems_barrier_create (rtems_build_name ('B', 'A', 'R', 'M'), RTEMS_BARRIER_AUTOMATIC_RELEASE, __po_hi_nb_tasks_to_init, &__po_hi_main_initialization_barrier);
  if (ret != RTEMS_SUCCESSFUL)
  {
     __DEBUGMSG ("[MAIN] Cannot create the main barrier, return code=%d\n", ret);
  }
#endif

  __po_hi_initialize_tasking ();

  /* Initialize protected objects */
#if __PO_HI_NB_PROTECTED > 0
  __po_hi_protected_init();
#endif


   return (__PO_HI_SUCCESS);
}

/*
 * The __po_hi_initialize function is only called
 * by the main thread (the one that executes the traditional
 * main() function.
 */
int __po_hi_initialize ()
{
#ifdef XM3_RTEMS_MODE
   #include <deployment.h>
   #include <po_hi_types.h>
   #include <xm.h>

   extern __po_hi_node_t         __po_hi_mynode;
   extern __po_hi_entity_t       __po_hi_port_global_to_entity[__PO_HI_NB_PORTS];
   extern __po_hi_node_t         __po_hi_entity_table[__PO_HI_NB_ENTITIES];
   extern __po_hi_port_kind_t    __po_hi_port_global_kind[__PO_HI_NB_PORTS];
   extern char*                  __po_hi_port_global_model_names[__PO_HI_NB_PORTS];

   __po_hi_port_t tmp;

   for (tmp = 0 ; tmp < __PO_HI_NB_PORTS ; tmp++)
   {
      if ((__po_hi_entity_table[__po_hi_port_global_to_entity[tmp]] == __po_hi_mynode) &&
          ( (__po_hi_port_global_kind[tmp] ==  __PO_HI_IN_DATA_INTER_PROCESS) ||
            (__po_hi_port_global_kind[tmp] ==  __PO_HI_OUT_DATA_INTER_PROCESS) ||
            (__po_hi_port_global_kind[tmp] ==  __PO_HI_IN_EVENT_DATA_INTER_PROCESS) ||
            (__po_hi_port_global_kind[tmp] ==  __PO_HI_OUT_EVENT_DATA_INTER_PROCESS)
          ))
      {
         __DEBUGMSG ("[MAIN] Should init port %d\n", tmp);
         switch (__po_hi_port_global_kind[tmp])
         {
            case __PO_HI_IN_DATA_INTER_PROCESS:
               if (XM_create_sampling_port (__po_hi_port_global_model_names [tmp], 8, XM_DESTINATION_PORT) < 0)
               {
                  __DEBUGMSG ("[MAIN] Sampling destination port %d cannot be created !\n", tmp);
               }
               break;

            case __PO_HI_OUT_DATA_INTER_PROCESS:
               if (XM_create_sampling_port (__po_hi_port_global_model_names [tmp], 8, XM_SOURCE_PORT) < 0)
               {
                  __DEBUGMSG ("[MAIN] Sampling source port %d cannot be created !\n", tmp);
               }
               break;

            case __PO_HI_IN_EVENT_DATA_INTER_PROCESS:
               if (XM_create_queuing_port (__po_hi_port_global_model_names [tmp], 1, 8, XM_DESTINATION_PORT) < 0)
               {
                  __DEBUGMSG ("[MAIN] Queuing destination port %d cannot be created !\n", tmp);
               }
               break;

            case __PO_HI_OUT_EVENT_DATA_INTER_PROCESS:
               if (XM_create_queuing_port (__po_hi_port_global_model_names [tmp], 1, 8, XM_SOURCE_PORT) < 0)
               {
                  __DEBUGMSG ("[MAIN] Queuing source port %d cannot be created !\n", tmp);
               }
               break;

            default:
               __DEBUGMSG ("[MAIN] Port kind not handled at this time for port %d\n", tmp);
               break;
         }

      }
   }
#endif
  return (__PO_HI_SUCCESS);
}

int __po_hi_wait_initialization ()
{
#if defined (POSIX) || defined (RTEMS_POSIX) || defined (XENO_POSIX)
   int cstate;
   if (pthread_setcancelstate (PTHREAD_CANCEL_ENABLE, &cstate) != 0)
   {
      __DEBUGMSG ("[MAIN] Cannot modify the cancel state\n");
   }

   if (pthread_setcanceltype (PTHREAD_CANCEL_ASYNCHRONOUS, &cstate) != 0)
   {
      __DEBUGMSG ("[MAIN] Cannot modify the cancel type\n");
   }

  if (pthread_mutex_lock (&mutex_init) != 0)
  {
    __DEBUGMSG ("[MAIN] Unable to lock the mutex\n");
    return (__PO_HI_ERROR_PTHREAD_MUTEX);
  }

  __po_hi_initialized_tasks++;

  __DEBUGMSG ("[MAIN] %d task(s) initialized (total to init =%d)\n", __po_hi_initialized_tasks, __po_hi_nb_tasks_to_init);
 
  while (__po_hi_initialized_tasks < __po_hi_nb_tasks_to_init)
  {
      pthread_cond_wait (&cond_init, &mutex_init);
  }
  pthread_cond_broadcast (&cond_init);
  pthread_mutex_unlock (&mutex_init);
  return (__PO_HI_SUCCESS);
#elif defined (RTEMS_PURE) 
  rtems_status_code ret;

  __DEBUGMSG ("[MAIN] Task wait for the barrier\n");
  ret = rtems_barrier_wait (__po_hi_main_initialization_barrier, RTEMS_WAIT);
  if (ret != RTEMS_SUCCESSFUL)
  {
     __DEBUGMSG ("[MAIN] Error while waiting for the barrier, return code=%d\n", ret);
     return (__PO_HI_ERROR_UNKNOWN);
  }
  __DEBUGMSG ("[MAIN] Task release the barrier\n");
  return (__PO_HI_SUCCESS);
#elif defined (XENO_NATIVE)
  int ret;

  if (main_task_id == rt_task_self ())
  {
     /*
      * Here, this function is called by the main thread (the one that executes
      * the main() function) so that we don't wait for the initialization of the
      * other tasks, we automatically pass through the function and immeditaly
      * return.
      */
     return (__PO_HI_SUCCESS);
  }

  ret = rt_mutex_acquire (&mutex_init, TM_INFINITE);
  if (ret != 0)
  {
   __DEBUGMSG ("[MAIN] Cannot acquire mutex (return code = %d)\n", ret);
    return (__PO_HI_ERROR_PTHREAD_MUTEX);
  }

  __po_hi_initialized_tasks++;

  __DEBUGMSG ("[MAIN] %d task(s) initialized (total to init =%d)\n", __po_hi_initialized_tasks, __po_hi_nb_tasks_to_init);
 
  while (__po_hi_initialized_tasks < __po_hi_nb_tasks_to_init)
  {
      rt_cond_wait (&cond_init, &mutex_init, TM_INFINITE);
  }
  rt_cond_broadcast (&cond_init);
  rt_mutex_release (&mutex_init);
  return (__PO_HI_SUCCESS);

#else
  return (__PO_HI_UNAVAILABLE);
#endif
}

#ifdef __PO_HI_USE_GPROF
void __po_hi_wait_end_of_instrumentation ()
{
#ifdef RTEMS_PURE
   rtems_task_wake_after (10000000 / _TOD_Microseconds_per_tick); 
#else
   #include <po_hi_time.h> 
   #include <unistd.h>

   __po_hi_time_t now;
   __po_hi_get_time (&now);
   __po_hi_delay_until (__po_hi_add_times (now, __po_hi_seconds (10)));
#endif
  __DEBUGMSG ("Call exit()\n");
  __po_hi_tasks_killall ();
   exit (1);

  __DEBUGMSG ("exit() called\n");
#ifdef RTEMS_PURE
  rtems_task_delete (rtems_self ());
#endif
}
#endif
