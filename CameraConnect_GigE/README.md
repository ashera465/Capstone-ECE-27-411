# GiGE_Conn
This is code to connect to a camera via GigE Protocol,using the Aravis Open Source API.

# Requirements
To make changes to source code, this uses aravis 0.8 which will need to be installed. The current make file uses meson and ninja in python
to build the aravis sdk. 

It is also reliant on some glib dlls and may fail if Make can't find them. 
Also some glib exe may be blocked by an Application Control Policy.
For some reason a lot of msys exe files are not certified by Microsoft, so the antivirus defender blocks it.
Just add the msys folder to the exclusions.
