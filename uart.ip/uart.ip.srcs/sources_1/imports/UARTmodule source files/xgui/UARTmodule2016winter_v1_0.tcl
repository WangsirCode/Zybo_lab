# Definitional proc to organize widgets for parameters.
proc init_gui { IPINST } {
  ipgui::add_param $IPINST -name "Component_Name"
  #Adding Page
  set Page_0 [ipgui::add_page $IPINST -name "Page 0"]
  ipgui::add_param $IPINST -name "BAUDRATE" -parent ${Page_0}
  ipgui::add_param $IPINST -name "FREQUENCY" -parent ${Page_0}
  ipgui::add_param $IPINST -name "TRANSMITTED_BITS" -parent ${Page_0}


}

proc update_PARAM_VALUE.BAUDRATE { PARAM_VALUE.BAUDRATE } {
	# Procedure called to update BAUDRATE when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.BAUDRATE { PARAM_VALUE.BAUDRATE } {
	# Procedure called to validate BAUDRATE
	return true
}

proc update_PARAM_VALUE.FREQUENCY { PARAM_VALUE.FREQUENCY } {
	# Procedure called to update FREQUENCY when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.FREQUENCY { PARAM_VALUE.FREQUENCY } {
	# Procedure called to validate FREQUENCY
	return true
}

proc update_PARAM_VALUE.TRANSMITTED_BITS { PARAM_VALUE.TRANSMITTED_BITS } {
	# Procedure called to update TRANSMITTED_BITS when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.TRANSMITTED_BITS { PARAM_VALUE.TRANSMITTED_BITS } {
	# Procedure called to validate TRANSMITTED_BITS
	return true
}


proc update_MODELPARAM_VALUE.TRANSMITTED_BITS { MODELPARAM_VALUE.TRANSMITTED_BITS PARAM_VALUE.TRANSMITTED_BITS } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.TRANSMITTED_BITS}] ${MODELPARAM_VALUE.TRANSMITTED_BITS}
}

proc update_MODELPARAM_VALUE.BAUDRATE { MODELPARAM_VALUE.BAUDRATE PARAM_VALUE.BAUDRATE } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.BAUDRATE}] ${MODELPARAM_VALUE.BAUDRATE}
}

proc update_MODELPARAM_VALUE.FREQUENCY { MODELPARAM_VALUE.FREQUENCY PARAM_VALUE.FREQUENCY } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.FREQUENCY}] ${MODELPARAM_VALUE.FREQUENCY}
}

