TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC = rtd
# rtd.dbd will be created and installed
DBD += rtd.dbd

# rtd.dbd will be made up from these files:
rtd_DBD += base.dbd

# Include dbd files from all support applications:
rtd_DBD += max31865.dbd
rtd_DBD += menuScan.dbd

# Add all the support libraries needed by this IOC
rtd_LIBS += max31865

# rtd_registerRecordDeviceDriver.cpp derives from rtd.dbd
rtd_SRCS += rtd_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
rtd_SRCS_DEFAULT += rtdMain.cpp
rtd_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#rtd_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
rtd_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

