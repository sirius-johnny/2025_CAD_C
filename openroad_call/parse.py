import openroad as ord
from openroad import Tech, Design, Timing
import os, odb, drt
from pathlib import Path
from parse_helper import *
import argparse 
import json
import sys

parser = argparse.ArgumentParser(description="Path to root of the tutorial directory")
parser.add_argument("--path", type = Path, default='../testcase', action = 'store')
pyargs = parser.parse_args()
tech, design = load_design(pyargs.path, verilog = False) 

timing = Timing(design)
db = ord.get_db()
corner = timing.getCorners()[0]
block = design.getBlock()
die_area = block.getDieArea()

dump_file_name = "./dump_for_Cplus/libs.txt"

# with open(dump_file_name, 'w') as f:
#     print(f"{die_area.ll()[0]} {die_area.ll()[1]} {die_area.ur()[0]} {die_area.ur()[1]}\n")
#     f.write(f"{die_area.ll()[0]} {die_area.ll()[1]} {die_area.ur()[0]} {die_area.ur()[1]}\n")

dump_libs_to_json(dump_file_name, db, design)

insts = block.getInsts()
for inst in insts:
    print(f'Inst Name: {inst.getName()}| Location: {inst.getLocation()}')


# ############
# #cell query#
# ############
# print(" name      | library_type | dynamic_power | static_power")
# insts = block.getInsts()[-10:]
# for inst in insts:
#   inst_static_power = timing.staticPower(inst, corner)
#   inst_dynamic_power = timing.dynamicPower(inst, corner)
#   inst_name = inst.getName()
#   libcell_name = inst.getMaster().getName()
#   print(f"{inst_name:<11}| {libcell_name:<13}| {inst_dynamic_power:14.4e}| {inst_static_power:12.4e}")
#   #hit tab for all available apis (ex. inst.[tab])
#   #the return type of power is float!!!
# print(f"Power return type: {type(inst_static_power)}")
# print("###################################################################")
# ###########
# #net query#
# ###########
# print(" name       | net_type | pin&wire_capacitance | net_degree")
# nets = block.getNets()
# for net in nets:
#   pin_and_wire_cap = timing.getNetCap(net, corner, timing.Max)
#   net_name = net.getName()
#   net_type = net.getSigType()
#   net_degree = len(net.getITerms())
#   print(f"{net_name:<12}| {net_type:<9}| {pin_and_wire_cap:19.4e} | {net_degree}")
#   #hit tab for all available apis (ex. net.[tab])
#   #the return type of pin_and_wire_cap is float!!!
# print("###################################################################")
# ###########
# #pin query#
# ###########
# print(" name        | rise_arrival_time | fall_arrival_time | rise_slack | fall_slack | slew")
# for inst in insts:
#   inst_ITerms = inst.getITerms()
#   for pin in inst_ITerms:
#     if design.isInSupply(pin):
#         continue
#     pin_name = design.getITermName(pin)
#     pin_rise_arr = timing.getPinArrival(pin, timing.Rise)
#     pin_fall_arr = timing.getPinArrival(pin, timing.Fall)
#     pin_rise_slack = timing.getPinSlack(pin, timing.Fall, timing.Max)
#     pin_fall_slack = timing.getPinSlack(pin, timing.Rise, timing.Max)
#     pin_slew = timing.getPinSlew(pin)
#     print(f"{pin_name:<12} | {pin_rise_arr:17.4e} | {pin_fall_arr:17.4e} | {pin_rise_slack:10.4e} | {pin_fall_slack:10.4e} | {pin_slew:6.4e}") 
#     #hit tab for all available apis (ex. pin.[tab])
#     #the return type of slack is float!!!
#     #timing-related properties go through timing.[tab] apis
# print("###################################################################")
# print(" name          | rise_arrival_time | fall_arrival_time | rise_slack | fall_slack | slew")
# for net in nets:
#   net_ITerms = net.getITerms()
#   for pin in net_ITerms:
#     pin_name = design.getITermName(pin)
#     pin_rise_arr = timing.getPinArrival(pin, timing.Rise)
#     pin_fall_arr = timing.getPinArrival(pin, timing.Fall)
#     pin_rise_slack = timing.getPinSlack(pin, timing.Fall, timing.Max)
#     pin_fall_slack = timing.getPinSlack(pin, timing.Rise, timing.Max)
#     pin_slew = timing.getPinSlew(pin)    
#     print(f"{pin_name:<14} | {pin_rise_arr:17.4e} | {pin_fall_arr:<17.4e} | {pin_rise_slack:10.4e} | {pin_fall_slack:10.4e} | {pin_slew:6.4e}")
# print("###################################################################")

# # Collect cell (instance) information
# cells = []
# for inst in block.getInsts():
#     cells.append({
#         "instance_name": inst.getName(),
#         "libcell_type": inst.getMaster().getName()
#     })

# # Collect net information
# nets = []
# for net in block.getNets():
#     nets.append({
#         "net_name": net.getName(),
#         "net_type": str(net.getSigType()),
#         "degree": len(net.getITerms()),
#         "pins": [design.getITermName(pin) for pin in net.getITerms()]
#     })

# # Collect explicit connections (net ↔ instance/pin)
# connections = []
# for net in block.getNets():
#     net_name = net.getName()
#     for pin in net.getITerms():
#         iterm = design.getITermName(pin)  # e.g., "U1/Y"
#         if "/" in iterm:
#             inst_name, pin_name = iterm.split("/", 1)
#         else:
#             inst_name, pin_name = None, iterm
#         connections.append({
#             "net": net_name,
#             "instance": inst_name,
#             "pin": pin_name
#         })

# # Combine into a top‐level JSON structure
# data = {
#     "cells": cells,
#     "nets": nets,
#     "connections": connections
# }

# Dump to file
# out_path = "design_info.json"
# with open(out_path, "w") as f:
#     json.dump(data, f, indent=2)

# print(f"JSON dumped to {out_path}, containing {len(cells)} cells, {len(nets)} nets, and {len(connections)} connections.")
