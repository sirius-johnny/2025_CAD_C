#BSD 3-Clause License
#
#Copyright (c) 2023, ASU-VDA-Lab
#
#Redistribution and use in source and binary forms, with or without
#modification, are permitted provided that the following conditions are met:
#
#1. Redistributions of source code must retain the above copyright notice, this
#   list of conditions and the following disclaimer.
#
#2. Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the documentation
#   and/or other materials provided with the distribution.
#
#3. Neither the name of the copyright holder nor the names of its
#   contributors may be used to endorse or promote products derived from
#   this software without specific prior written permission.
#
#THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
#IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
#DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
#FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
#DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
#SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
#CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
#OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
#OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
import openroad as ord
from openroad import Tech, Design
import os, odb, drt
from pathlib import Path

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
    tech.readLiberty(libFile.as_posix())
    # if libFile.name == "asap7sc7p5t_INVBUF_LVT_TT_nldm_220122.lib": # Skip CON problem recorded @06/22
    #     tech.readLiberty(libFile.as_posix())
  print("Lib files reading done!")
  for techLefFile in techLefFiles:
    tech.readLef(techLefFile.as_posix())
  print("TechLef files reading done!")
  for lefFile in lefFiles:
    tech.readLef(lefFile.as_posix())
  print("Lef files reading done!")
  design = Design(tech)
  #Read design files

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


