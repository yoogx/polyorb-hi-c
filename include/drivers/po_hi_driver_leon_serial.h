/*
 * This is a part of PolyORB-HI-C distribution, a minimal
 * middleware written for generated code from AADL models.
 * You should use it with the Ocarina toolsuite.
 *
 * For more informations, please visit http://assert-project.net/taste
 *
 * Copyright (C) 2011-2012 ESA & ISAE.
 */


#ifndef __PO_HI_DRIVER_LEON_SERIAL_H__
#define __PO_HI_DRIVER_LEON_SERIAL_H__

#ifdef __PO_HI_NEED_DRIVER_SERIAL_LEON

void __po_hi_c_driver_serial_leon_poller (const __po_hi_device_id dev_id);

void __po_hi_c_driver_serial_leon_init (__po_hi_device_id id);

int  __po_hi_c_driver_serial_leon_sender (__po_hi_task_id task, __po_hi_port_t port);

#endif

#endif
