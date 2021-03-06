# 
# Synthesis run script generated by Vivado
# 

set_param gui.test TreeTableDev
debug::add_scope template.lib 1
set_msg_config -id {Common-41} -limit 4294967295
set_msg_config -id {HDL 9-1061} -limit 100000
set_msg_config -id {HDL 9-1654} -limit 100000
set_msg_config -id {HDL-1065} -limit 10000

create_project -in_memory -part xc7z010iclg225-1L
set_param project.compositeFile.enableAutoGeneration 0
set_param synth.vivado.isSynthRun true
set_property webtalk.parent_dir C:/Xilinx/xup/led_ip/ip_repo/edit_led_ip_v1_0.cache/wt [current_project]
set_property parent.project_path C:/Xilinx/xup/led_ip/ip_repo/edit_led_ip_v1_0.xpr [current_project]
set_property default_lib xil_defaultlib [current_project]
set_property target_language Verilog [current_project]
set_property ip_repo_paths C:/Xilinx/xup/led_ip/ip_repo/led_ip_1.0 [current_project]
read_verilog -library xil_defaultlib {
  C:/Xilinx/xup/led_ip/ip_repo/lab3_user_logic.v
  C:/Xilinx/xup/led_ip/ip_repo/led_ip_1.0/hdl/led_ip_v1_0_S_AXI.v
  C:/Xilinx/xup/led_ip/ip_repo/led_ip_1.0/hdl/led_ip_v1_0.v
}
catch { write_hwdef -file led_ip_v1_0.hwdef }
synth_design -top led_ip_v1_0 -part xc7z010iclg225-1L
write_checkpoint -noxdef led_ip_v1_0.dcp
catch { report_utilization -file led_ip_v1_0_utilization_synth.rpt -pb led_ip_v1_0_utilization_synth.pb }
