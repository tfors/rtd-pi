TOP=../../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#==================================================
# build a support library

LIBRARY_IOC += asynSPIDriver

# xxxRecord.h will be created from xxxRecord.dbd
#DBDINC += xxxRecord
# install asynSPIDriver.dbd into <top>/dbd
# DBD += asynSPIDriver.dbd

# specify all source files to be compiled and added to the library
asynSPIDriver_SRCS += asynSPIDriver.cpp

INC += asynSPIDriver.h

asynSPIDriver_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

