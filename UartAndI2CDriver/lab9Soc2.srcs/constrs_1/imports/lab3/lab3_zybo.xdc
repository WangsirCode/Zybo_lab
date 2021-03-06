############################
# On-board LED             #
############################
set_property PACKAGE_PIN M14 [get_ports LED[0]]
set_property IOSTANDARD LVCMOS33 [get_ports LED[0]]
set_property PACKAGE_PIN M15 [get_ports LED[1]]
set_property IOSTANDARD LVCMOS33 [get_ports LED[1]]
set_property PACKAGE_PIN G14 [get_ports LED[2]]
set_property IOSTANDARD LVCMOS33 [get_ports LED[2]]
set_property PACKAGE_PIN D18 [get_ports LED[3]]
set_property IOSTANDARD LVCMOS33 [get_ports LED[3]]

set_property DONT_TOUCH true [get_cells system_i]
set_property DONT_TOUCH true [get_cells system_i/processing_system7_0]
set_property DONT_TOUCH true [get_cells system_i/processing_system7_0/inst]
set_property PACKAGE_PIN V20 [get_ports iic_1_scl_io]
set_property PACKAGE_PIN W20 [get_ports iic_1_sda_io]
set_property IOSTANDARD LVCMOS33 [get_ports iic_1_scl_io]
set_property IOSTANDARD LVCMOS33 [get_ports iic_1_sda_io]

set_property DONT_TOUCH true [get_cells system_i/UARTmodule2016winter_0]
set_property DONT_TOUCH true [get_cells system_i/axi_gpio_0]
set_property DONT_TOUCH true [get_cells system_i/axi_gpio_0/U0]
set_property DONT_TOUCH true [get_cells system_i/axi_gpio_1]
set_property DONT_TOUCH true [get_cells system_i/axi_gpio_1/U0]
set_property DONT_TOUCH true [get_cells system_i/processing_system7_0_axi_periph]
set_property DONT_TOUCH true [get_cells system_i/processing_system7_0_axi_periph/s00_couplers/auto_pc]
set_property DONT_TOUCH true [get_cells system_i/processing_system7_0_axi_periph/xbar]
set_property DONT_TOUCH true [get_cells system_i/rst_processing_system7_0_100M]
set_property PACKAGE_PIN V15 [get_ports tx]
set_property IOSTANDARD LVCMOS33 [get_ports tx]
