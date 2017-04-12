
 add_fsm_encoding \
       {vdma_to_vga__parameterized0.vga_state} \
       { }  \
       {{000 000} {001 001} {010 010} {011 011} {100 100} {101 101} }

 add_fsm_encoding \
       {axi_dispctrl_v1_0.clk_state} \
       { }  \
       {{000 00000010} {001 00000100} {010 00001000} {011 00010000} {100 00100000} {101 01000000} {110 10000000} }

 add_fsm_encoding \
       {axi_vdma_sm.dmacntrl_cs} \
       { }  \
       {{000 000} {001 001} {010 010} {011 100} {100 011} {101 101} }
