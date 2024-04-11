connect -url tcp:127.0.0.1:3121
source D:/Desktop/Project/ZYNQ_Highlevel_Synthesis/ov5640_rgb2gray/ov5640_rgb2gray_ip_test/ov5640_rgb2gray_ip_test.sdk/design_1_wrapper_hw_platform_0/ps7_init.tcl
targets -set -filter {jtag_cable_name =~ "Digilent JTAG-SMT2 210251A08870" && level==0} -index 1
fpga -file D:/Desktop/Project/ZYNQ_Highlevel_Synthesis/ov5640_rgb2gray/ov5640_rgb2gray_ip_test/ov5640_rgb2gray_ip_test.sdk/design_1_wrapper_hw_platform_0/design_1_wrapper.bit
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Digilent JTAG-SMT2 210251A08870"} -index 0
loadhw -hw D:/Desktop/Project/ZYNQ_Highlevel_Synthesis/ov5640_rgb2gray/ov5640_rgb2gray_ip_test/ov5640_rgb2gray_ip_test.sdk/design_1_wrapper_hw_platform_0/system.hdf -mem-ranges [list {0x40000000 0xbfffffff}]
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Digilent JTAG-SMT2 210251A08870"} -index 0
stop
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent JTAG-SMT2 210251A08870"} -index 0
rst -processor
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent JTAG-SMT2 210251A08870"} -index 0
dow D:/Desktop/Project/ZYNQ_Highlevel_Synthesis/ov5640_rgb2gray/ov5640_rgb2gray_ip_test/ov5640_rgb2gray_ip_test.sdk/ov5640_rgb2gray_lcd/Debug/ov5640_rgb2gray_lcd.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent JTAG-SMT2 210251A08870"} -index 0
con
