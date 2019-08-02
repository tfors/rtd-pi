#!/usr/bin/env python

import os
import time

from epics import ca
import microdotphat as mdot

def new_temperature(**kw):
    '''
    Callback from pyepics whenever the temperature PV posts a monitor,
    we update the microdot display
    '''
    tstr = '%.1f°F' % kw['value']
    mdot.clear()
    mdot.write_string(tstr, kerning=False)
    mdot.show()

def new_brightness(**kw):
    mdot.set_brightness(kw['value'])

os.environ['PYEPICS_LIBCA'] = '/usr/local/epics/base/lib/linux-arm/libca.so'
os.environ['PATH'] += ':/usr/local/epics/base/bin/linux-arm'
mdot.set_rotate180(True)

mdot.clear()
mdot.write_string('TMP200', kerning=False)
mdot.show()

time.sleep(3)

pvs = {}

name = 'pi:Temp'
chid = ca.create_channel(name)
sub = ca.create_subscription(chid, callback=new_temperature)
pvs[name] = (chid, sub)

name = 'pi:Brightness'
chid = ca.create_channel(name)
sub = ca.create_subscription(chid, callback=new_brightness)
pvs[name] = (chid, sub)

while True:
    ca.poll()
