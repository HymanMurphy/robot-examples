------------------------------------------------------------------------
Integrate mBedTLS with flexR300 Visual Studio
------------------------------------------------------------------------
 
Download the latest mbedtls Library from below URL
https://tls.mbed.org/

In this example we use "mbedtls-2.3.0-apache" version.


Extract the Library "mbedtls-2.3.0-apache".


Now Open the example VS solution and create a "Library" folder under ServerExample.
Then, go to the file system inside serverExample folder and "Library" folder is already created there. Now copy the "mbedtls-2.3.0" into the Library folder.


Then, come back to the visual studio solution. Right click on Library, click on "add existing"; browse till "ServerExample\Library\mbedtls-2.3.0\include\mbedtls" and select all the header files and add them.
Now, you can see "mbedtls-2.3.0" folder structure is added under Library. Then, right click on library ("mbedtls-2.3.0->library") and "Include In Project".


Open "mbedtls\config.h" and enable "#define MBEDTLS_PLATFORM_MEMORY" (line no. 112)


Open ServerExample Properties->VC++ Directories->Include Directories, add "<Path to Library in the visual studio solution>\Library\mbedtls-2.3.0\include" as path.


Open uasdk_default_build_config.h and modify #define UASDK_INCLUDE_SECURITY from 0 to 1 and similarly "#define UASDK_USE_MBEDTLS 1".


Add the security related code in ServerExample.cpp. (example provided)


Build and Run the project, It will create pki folder in desired location. Try to connect from client, This may fail because of trust issue. 
Copy the client certificate to the "pki\DefaultApplicationGroup\trusted\certs" (from pki\DefaultApplicationGroup\rejected\certs) and restart the sever.


*Note: Use the latest provided ua_security_mbedtls.c from opcua sdk package*

-------------------------------------------------------------------------