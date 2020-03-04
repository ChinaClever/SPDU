import rtconfig
from building import *

cwd     = GetCurrentDir()
CPPPATH = [cwd, str(Dir('#'))]
src     = Split("""
main.c
""")

if GetDepend(['RT_USING_DFS']):
    src += ['mnt.c']
    
if GetDepend(['BSP_USING_ADC1']):
    src += Glob('common/cpu_temp/*.c')

src += Glob('common/aes/*.c')
CPPPATH += [cwd + '/common/aes']

src += Glob('common/datapacket/*.c')
CPPPATH += [cwd + '/common/datapacket']

src += Glob('common/json/*.c')
CPPPATH += [cwd + '/common/json']

src += Glob('common/list/*.c')
CPPPATH += [cwd + '/common/list']

src += Glob('common/dingtalk/*.c')
CPPPATH += [cwd + '/common/dingtalk']

src += Glob('common/upgrade/*.c')
CPPPATH += [cwd + '/common/upgrade']

src += Glob('common/devcfg/*.c')
CPPPATH += [cwd + '/common/devcfg']

src += Glob('common/iwdg/*.c')
CPPPATH += [cwd + '/common/iwdg']

src += Glob('network/*.c')
CPPPATH += [cwd + '/network']

src += Glob('manager/*.c')
CPPPATH += [cwd + '/manager']

src += Glob('snmp/*.c')
CPPPATH += [cwd + '/snmp']

src += Glob('rtu/*.c')
CPPPATH += [cwd + '/rtu']

src += Glob('modbus/*.c')
CPPPATH += [cwd + '/modbus']

src += Glob('web/*.c')
CPPPATH += [cwd + '/web']

if GetDepend('PKG_USING_MYMQTT'):
	src += Glob('mqtt/*.c')
	CPPPATH += [cwd + '/mqtt']

if GetDepend('PKG_USING_ALI_IOTKIT'):
	src += Glob('aliiot/*.c')
	CPPPATH += [cwd + '/aliiot']
		

group = DefineGroup('Applications', src, depend = [''], CPPPATH = CPPPATH)

Return('group')
