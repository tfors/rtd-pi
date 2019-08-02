#!../../bin/linux-arm/rtd

## You may have to change rtd to something else
## everywhere it appears in this file

#< envPaths

## Register all support components
dbLoadDatabase("../../dbd/rtd.dbd",0,0)
rtd_registerRecordDeviceDriver(pdbbase) 

## Load record instances
dbLoadRecords("../../db/max31865.db","P=pi,R=:")
dbLoadRecords("../../db/microdot.db","P=pi,R=:")

iocInit()

## Start any sequence programs
#seq sncrtd,"user=pi"
