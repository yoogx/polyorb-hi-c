------------------------------------------------------------------------------
--                                                                          --
--                          PolyORB HI COMPONENTS                           --
--                                                                          --
--              D E V I C E C O N F I G _ S P W _ O B J 2 3 4               --
--                                                                          --
--                                 S p e c                                  --
--                                                                          --
--                     Copyright (C) 2015 ESA & ISAE.                       --
--                                                                          --
-- PolyORB-HI is free software; you can redistribute it and/or modify under --
-- terms of the  GNU General Public License as published  by the Free Soft- --
-- ware  Foundation;  either version 3,  or (at your option) any later ver- --
-- sion. PolyORB-HI is distributed in the hope that it will be useful, but  --
-- WITHOUT ANY WARRANTY; without even the implied warranty of               --
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                     --
--                                                                          --
-- As a special exception under Section 7 of GPL version 3, you are granted --
-- additional permissions described in the GCC Runtime Library Exception,   --
-- version 3.1, as published by the Free Software Foundation.               --
--                                                                          --
-- You should have received a copy of the GNU General Public License and    --
-- a copy of the GCC Runtime Library Exception along with this program;     --
-- see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see    --
-- <http://www.gnu.org/licenses/>.                                          --
--                                                                          --
--              PolyORB-HI/Ada is maintained by the TASTE project           --
--                      (taste-users@lists.tuxfamily.org)                   --
--                                                                          --
------------------------------------------------------------------------------

pragma Style_Checks (Off); -- turn off style checks
-- Code automatically generated by asn1scc tool
-- Date was: 04/28/2011
-- Time was: 13:55:57

WITH Ada.Strings.Fixed;
USE ADA.Strings.Fixed;

WITH Interfaces;
USE Interfaces;

WITH Ada.Characters.latin_1;


WITH AdaAsn1RTL;
USE AdaAsn1RTL;
with POHICDRIVER_SPACEWIRE;
use POHICDRIVER_SPACEWIRE;

package DeviceConfig_spw_obj234 is



pohidrv_spw_obj234_cv:aliased Spacewire_Conf_T:=(devname => "/dev/grspwrasta0" & 4*Character'Val(0) & Character'Val(0),
nodeaddr => 22,
corefreq => 30000,
clockdiv => 0,
remove_prot_id => FALSE,
rxblock => FALSE,
txblock => FALSE, 
exist => (corefreq => 1, clockdiv => 0, remove_prot_id => 0, rxblock => 0, txblock => 0));

--END;
end DeviceConfig_spw_obj234;
