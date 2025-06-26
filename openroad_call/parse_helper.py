import openroad as ord
from openroad import Tech, Design, Timing
import os, odb, drt
from pathlib import Path
import json


def load_design(demo_path, verilog = False):
  #Read Files
  tech = Tech()
  libDir = demo_path/"ASAP7/LIB/"
  techLefDir = demo_path/"ASAP7/techlef/"
  lefDir = demo_path/"ASAP7/LEF/"
  designDir = demo_path/"aes_cipher_top/"
  # Read technology files
  libFiles = libDir.glob('*nldm*.lib')
  techLefFiles = techLefDir.glob('*.lef')
  lefFiles = lefDir.glob('*.lef')
  for libFile in libFiles:
    print(f'Reading {libFile}')
    tech.readLiberty(libFile.as_posix())
  for techLefFile in techLefFiles:
    tech.readLef(techLefFile.as_posix())
  for lefFile in lefFiles:
    tech.readLef(lefFile.as_posix())
  design = Design(tech)

  if verilog:
    verilogFile = designDir/"aes_cipher_top_modified.v"
    design.readVerilog(f"{verilogFile}")
    design.link("aes_cipher_top")
  else:
    defFile = designDir/'aes_cipher_top.def'
    design.readDef(f"{defFile}")
  
  # Read the SDC file and set the clocks
  sdcFile = designDir/"aes_cipher_top.sdc" 
  design.evalTclString(f"read_sdc {sdcFile}")
  design.evalTclString("create_clock -period 20 [get_ports clk] -name core_clock")
  design.evalTclString("set_propagated_clock [all_clocks]")
  
  return tech, design

def dump_libs_to_json(dump_file_path, libs):
  data = []
  print(f'Len(libs): {len(libs)}')
  
  for lib in libs:
    print(f'Library File: {lib.getName()}')  
    for master in lib.getMasters():
      libcell_name = master.getName()
      libcell_area = master.getHeight() * master.getWidth()
      print(f'Libcell Name: {libcell_name}, Libcell Area: {libcell_area}')
      data.append({
        "libcell_name": libcell_name,
        "libcell_area": libcell_area
      })

  with open(dump_file_path, 'w') as f:
    json.dump(data, f, indent=2)
