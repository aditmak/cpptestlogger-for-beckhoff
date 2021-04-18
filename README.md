# cpptestlogger for Beckhoff using ADS Port
 
This logger was created with [spdlog library](https://github.com/gabime/spdlog) to log data from Beckhoff systems. 

## ADS introduction

The Automation Device Specification (ADS) describes a device-independent and fieldbus-independent interface governing the type of access to ADS devices. The TwinCAT system architecture allows the individual modules of the software (e.g. TwinCAT PLC, TwinCAT NC, ...) to be treated as independent devices: For every task there is a software module ("Server" or "Client"). The messages between these objects are exchanged through a consistent ADS interface by the "message router". This manages and distributes all the messages in the system and over the TCP/IP connections. TwinCAT message routers exist on every TwinCAT PC and on every Beckhoff BCxxxx Bus Controller. This allows all TwinCAT server and client programs to exchange commands and data.

## Steps to connect ADS port to logger Port

1. Create a TwinCAT 3 C++ project and select TwinCAT Module class with ADS Port. (For more information, [click here](https://infosys.beckhoff.com/english.php?content=../content/1033/tc3_c/110697995.html&id=)).
2. Add the logic to the ADS server interface. Usually, the ADS server receives an ADS message, which contains two parameters (indexGroup and indexOffset) and perhaps further data pData. These parameters are defined in modules1Ads.h. (For more information, [click here](https://infosys.beckhoff.com/english.php?content=../content/1033/tc3_c/112598795.html&id=)).
3. Save and compile the project. Create module instance and activate the TwinCAT project. 
4. Determine the ADS port of the module instance. Generally the ADS port may be pre-numbered, so that the same port is always used for this module instance or it can be kept customizable, in order to offer several module instances the option to have their own ADS port assigned on startup of the TwinCAT system. (For more information check point #5 in, [here](https://infosys.beckhoff.com/english.php?content=../content/1033/tc3_c/112598795.html&id=))

In short, go to function void Main::AdsReadWriteInd() in your main.cpp and fill in the code as mentioned below:

    case controller_PIIndexOffset1:
	    m_Trace.Log(tlInfo, FNAMEA "oid=0x%08x indexGroup=0x%08x, indexOffset=0x%08x",
	    m_objId.value, indexGroup, indexOffset);
      
	    pData = ADD REFERENCE TO THE DATA YOU WANT TO LOG; (for example, pData = &m_counter;)
      
	    AdsReadWriteRes(rAddr, invokeId, ADSERR_NOERR, sizeof(pData), pData);
	    break;



## Code Explanation

* Add the port number which is mentioned about in #4 in line 58 of cpptestlogger.cpp as shown Addr->port = 0x8888;
* nErr will [return code](https://infosys.beckhoff.com/english.php?content=../content/1033/devicemanager/374277003.html&id=) if there is any error while sending or receiving the data. 
* The data type should be match the data type mentioned in the main.cpp TwinCAT program. 
