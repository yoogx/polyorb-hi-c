#include <deployment.h>

#ifdef __PO_HI_NEED_DRIVER_EXARM_NI_6071E_ANALOG

#include <po_hi_types.h>

void __po_hi_c_driver_exarm_ni_6071e_analog_init (__po_hi_device_id device_id)
{
   return;
}
   
void __po_hi_c_driver_exarm_ni_6071e_analog_poller 
   (double* data1, double* data2, double* data3, double* data4,
    double* data5, double* data6, double* data7, double* data8,
    double* data9, double* data10, double* data11, double* data12,
    double* data13, double* data14, double* data15, double* data16)
{
   *data1 = 1;
   return;
}

#endif
