puts "reading lib.."
foreach libFile [glob "../ASAP7/LIB/*nldm*.lib"] {
    puts "lib: $libFile"
    read_liberty $libFile
}
puts "reading lef.."
read_lef ../ASAP7/techlef/asap7_tech_1x_201209.lef
foreach lef [glob "../ASAP7/LEF/*.lef"] {
    read_lef $lef
}
puts "reading def.."
read_def ../aes_cipher_top/aes_cipher_top.def
read_sdc ../aes_cipher_top/aes_cipher_top.sdc
source ../ASAP7/setRC.tcl
estimate_parasitics -placement
report_tns
report_wns
report_power

set paths [find_timing_paths -path_group reg2reg -sort_by_slack -group_path_count 1]
set path [lindex $paths 0]
set slack [get_property $path slack]

set fp [open $::env(OUTFILE) w]
puts $fp "slack: $slack"
close $fp