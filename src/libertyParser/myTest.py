import libertyParser as LP
import os

myLibPar = LP.libertyParser('/app/ASP-DAC24-Tutorial/ICCAD25-CAD-C/testcase/ASAP7/LIB/sram_asap7_64x256_1rw.lib', debug=False)
print(len(myLibPar.libDic))
cellList = myLibPar.getCellList()
print(cellList)
cellAreaDic = myLibPar.getCellArea(cellList)
print(cellAreaDic)
# myLibPar.restoreLib('exa')