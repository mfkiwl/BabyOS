#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import os, sys, psutil
from kconfiglib import Kconfig
from menuconfig import menuconfig

def mconf_set_env(argv):
    """
    Set Kconfig Env
    """
    os.environ["MENUCONFIG_STYLE"] = "default selection=fg:white,bg:blue"
    os.environ["KCONFIG_CONFIG"] = os.path.join(".bconfig")
    os.environ["KCONFIG_CONFIG_HEADER"] = "# Generated by BabyOS Configuration"
    os.environ["KCONFIG_AUTOHEADER"] = os.path.join("b_config.h")
    os.environ["CONFIG_"] = ""

def mconfig(argv):
    print(argv[0])
    
    kconf_fd = open("Kconfig", 'w+')
    kconf_list = "mainmenu " + "\"BabyOS Configuration\" \n"
    kconf_list += "source " + "\"" + argv[1] + "/core/Kconfig" + "\"" + "\n" 
    kconf_list += "source " + "\"" + argv[1] + "/hal/Kconfig" + "\"" + "\n"
    kconf_list += "source " + "\"" + argv[1] + "/mcu/Kconfig" + "\"" + "\n"
    kconf_list += "source " + "\"" + argv[1] + "/algorithm/Kconfig" + "\"" + "\n"
    kconf_list += "source " + "\"" + argv[1] + "/drivers/Kconfig" + "\"" + "\n"
    kconf_list += "source " + "\"" + argv[1] + "/modules/Kconfig" + "\"" + "\n"
    kconf_list += "source " + "\"" + argv[1] + "/thirdparty/Kconfig" + "\"" + "\n"
    kconf_list += "source " + "\"" + argv[1] + "/utils/Kconfig" + "\"" + "\n"
    print(kconf_list)
    kconf_fd.write(kconf_list)
    kconf_fd.close()
    
    #parent_pid = os.getppid()
    #parent_name = psutil.Process(parent_pid).name()
    #print(psutil.Process(parent_pid).name())
    #if parent_name.find('cmd.exe') < 0:

    mconf_set_env(argv)
    kconf = Kconfig(filename="./Kconfig")
    menuconfig(kconf)
    kconf.write_autoconf()
    bconf_fd = open("b_config.h", 'r')
    bconf_data = bconf_fd.read()
    bconf_fd.close()
    print(bconf_data)

    bconf_new_data = "#ifndef __B_CONFIG_H__ \n"
    bconf_new_data += "#define __B_CONFIG_H__ \n\n\n"
    bconf_new_data += bconf_data
    bconf_new_data += "\n\n#include \"b_type.h\" \n\n"
    bconf_new_data += "#endif \n\n"
    bconf_fd = open("b_config.h", 'w')
    bconf_fd.write(bconf_new_data)
    bconf_fd.close()
    
    os.remove("Kconfig")
    
if __name__ == "__main__":
    mconfig(sys.argv)
