
U
Command: %s
53*	vivadotcl2$
power_opt_design2default:defaultZ4-113h px? 
?
@Attempting to get a license for feature '%s' and/or device '%s'
308*common2"
Implementation2default:default2
xczu3eg2default:defaultZ17-347h px? 
?
0Got license for feature '%s' and/or device '%s'
310*common2"
Implementation2default:default2
xczu3eg2default:defaultZ17-349h px? 
E
%Done setting XDC timing constraints.
35*timingZ38-35h px? 
E
0Begin power optimizations | Checksum: 15c838f92
*commonh px? 
?
jParam pwropt.runOnPwroptedDesign is set. Skipped checking if power_opt_design has been performed earlier.
121*pwroptZ34-141h px? 
i
#Optimizing power for module %s ...
50*pwropt2$
design_1_wrapper2default:defaultZ34-50h px? 
?
+Design is in %s state. Running in %s mode.
161*pwropt2
	pre-place2default:default2
	pre-place2default:defaultZ34-207h px? 
j
2Found %s new always-off flops by back propagation
95*pwropt2
952default:defaultZ34-95h px? 
?
I%sTime (s): cpu = %s ; elapsed = %s . Memory (MB): peak = %s ; gain = %s
268*common2$
Pre-processing: 2default:default2
00:00:072default:default2
00:00:042default:default2
3498.1452default:default2
14.5432default:defaultZ17-268h px? 
=
Applying IDT optimizations ...
9*pwroptZ34-9h px? 
?
I%sTime (s): cpu = %s ; elapsed = %s . Memory (MB): peak = %s ; gain = %s
268*common2$
PSMgr Creation: 2default:default2
00:00:102default:default2
00:00:052default:default2
3521.4732default:default2
37.8712default:defaultZ17-268h px? 
?
I%sTime (s): cpu = %s ; elapsed = %s . Memory (MB): peak = %s ; gain = %s
268*common2
IDT: 2default:default2
00:00:142default:default2
00:00:052default:default2
3619.2272default:default2
121.0822default:defaultZ17-268h px? 
?
Applying ODC optimizations ...
10*pwroptZ34-10h px? 
K
,Running Vector-less Activity Propagation...
51*powerZ33-51h px? 
P
3
Finished Running Vector-less Activity Propagation
1*powerZ33-1h px? 
}
DSkipped ODC enables for %s nets in BRAM flops in bus-based analysis.163*pwropt2
02default:defaultZ34-215h px? 
?
LSkipped ODC enables for %s nets in BRAM address flops in bus-based analysis.162*pwropt2
02default:defaultZ34-214h px? 
?
I%sTime (s): cpu = %s ; elapsed = %s . Memory (MB): peak = %s ; gain = %s
268*common2
ODC: 2default:default2
00:01:352default:default2
00:01:092default:default2
4916.4492default:default2
1297.2232default:defaultZ17-268h px? 
?
I%sTime (s): cpu = %s ; elapsed = %s . Memory (MB): peak = %s ; gain = %s
268*common2/
Power optimization passes: 2default:default2
00:01:572default:default2
00:01:172default:default2
4916.4492default:default2
1432.8482default:defaultZ17-268h px? 


*pwropth px? 
@
 Creating clock enable groups ...77*pwroptZ34-77h px? 
d
DIncluding small groups for filtering based on enable probabilities.
96*pwroptZ34-96h px? 
&
 Done
76*pwroptZ34-76h px? 
?
I%sTime (s): cpu = %s ; elapsed = %s . Memory (MB): peak = %s ; gain = %s
268*common2&
Grouping enables: 2default:default2
00:00:052default:default2
00:00:052default:default2
4916.4492default:default2
0.0002default:defaultZ17-268h px? 


*pwropth px? 
e

Starting %s Task
103*constraints2*
PowerOpt Patch Enables2default:defaultZ18-103h px? 
}
7Patching clock gating enable signals for design %s ...
26*pwropt2$
design_1_wrapper2default:defaultZ34-26h px? 
?
?WRITE_MODE attribute of %s BRAM(s) out of a total of %s has been updated to save power.
    Run report_power_opt to get a complete listing of the BRAMs updated.
129*pwropt2
02default:default2
32default:defaultZ34-162h px? 
d
+Structural ODC has moved %s WE to EN ports
155*pwropt2
02default:defaultZ34-201h px? 
?
KPatcher adaptive clustering : original %s clusters %s accepted clusters %s
100*pwropt2
ram2default:default2
62default:default2
62default:defaultZ34-100h px? 
?
KPatcher adaptive clustering : original %s clusters %s accepted clusters %s
100*pwropt2
flop2default:default2
6252default:default2
6252default:defaultZ34-100h px? 
?
C
Number of Slice Registers augmented: %s newly gated: %s Total: %s
64*pwropt2
8122default:default2
15032default:default2
256762default:defaultZ34-64h px? 
?
8Number of SRLs augmented: %s  newly gated: %s Total: %s
66*pwropt2
02default:default2
02default:default2
7432default:defaultZ34-66h px? 
?
CNumber of BRAM Ports augmented: %s newly gated: %s Total Ports: %s
65*pwropt2
42default:default2
22default:default2
62default:defaultZ34-65h px? 
h
1Number of Flops added for Enable Generation: %s

23*pwropt2
02default:defaultZ34-23h px? 
?
UFlops dropped: %s/%s RAMS dropped: %s/%s Clusters dropped: %s/%s Enables dropped: %s
57*pwropt2
1072default:default2
25262default:default2
02default:default2
62default:default2
382default:default2
6312default:default2
382default:defaultZ34-57h px? 
m
+Patching clock gating enables finished %s.
27*pwropt2 
successfully2default:defaultZ34-27h px? 
N
9Ending PowerOpt Patch Enables Task | Checksum: 15a3f730f
*commonh px? 
?

%s
*constraints2o
[Time (s): cpu = 00:02:01 ; elapsed = 00:01:36 . Memory (MB): peak = 4916.449 ; gain = 0.0002default:defaulth px? 
J
*Power optimization finished successfully.
30*pwroptZ34-30h px? 
C
.End power optimizations | Checksum: 15a3f730f
*commonh px? 
?
I%sTime (s): cpu = %s ; elapsed = %s . Memory (MB): peak = %s ; gain = %s
268*common2(
Power optimization: 2default:default2
00:04:062default:default2
00:03:032default:default2
4916.4492default:default2
1537.1722default:defaultZ17-268h px? 
u
<Malloced memory gain at end of power optimization: %s bytes
152*pwropt2
02default:defaultZ34-198h px? 
a

Starting %s Task
103*constraints2&
Logic Optimization2default:defaultZ18-103h px? 
i

Phase %s%s
101*constraints2
1 2default:default2
Retarget2default:defaultZ18-101h px? 
w
)Pushed %s inverter(s) to %s load pin(s).
98*opt2
222default:default2
542default:defaultZ31-138h px? 
?
$Fixed cascade connection for DSP: %s484*opt2?
?design_1_i/hard_cnn_0/inst/hard_cnn_dexp_64nbjl_U68/hard_cnn_ap_dexp_11_full_dsp_64_u/U0/i_synth/EXP_OP.i_sp_or_dp.OP/i_ccm_recip_ln2/g_tables[1].i_addsub/dsp.one.dsp48e1_add/i_no_versal_es1_workaround.DSP	?design_1_i/hard_cnn_0/inst/hard_cnn_dexp_64nbjl_U68/hard_cnn_ap_dexp_11_full_dsp_64_u/U0/i_synth/EXP_OP.i_sp_or_dp.OP/i_ccm_recip_ln2/g_tables[1].i_addsub/dsp.one.dsp48e1_add/i_no_versal_es1_workaround.DSP2default:default8Z31-925h px? 
?
$Fixed cascade connection for DSP: %s484*opt2?
?design_1_i/hard_cnn_0/inst/hard_cnn_dexp_64nbjl_U68/hard_cnn_ap_dexp_11_full_dsp_64_u/U0/i_synth/EXP_OP.i_sp_or_dp.OP/i_ccm_recip_ln2/g_tables[2].i_addsub/dsp.one.dsp48e1_add/i_no_versal_es1_workaround.DSP	?design_1_i/hard_cnn_0/inst/hard_cnn_dexp_64nbjl_U68/hard_cnn_ap_dexp_11_full_dsp_64_u/U0/i_synth/EXP_OP.i_sp_or_dp.OP/i_ccm_recip_ln2/g_tables[2].i_addsub/dsp.one.dsp48e1_add/i_no_versal_es1_workaround.DSP2default:default8Z31-925h px? 
K
Retargeted %s cell(s).
49*opt2
02default:defaultZ31-49h px? 
;
&Phase 1 Retarget | Checksum: 86fb2766
*commonh px? 
?

%s
*constraints2o
[Time (s): cpu = 00:00:09 ; elapsed = 00:00:07 . Memory (MB): peak = 4916.449 ; gain = 0.0002default:defaulth px? 
?
.Phase %s created %s cells and removed %s cells267*opt2
Retarget2default:default2
32default:default2
292default:defaultZ31-389h px? 
?
?In phase %s, %s netlist objects are constrained preventing optimization. Please run opt_design with -debug_log to get more detail. 510*opt2
Retarget2default:default2
302default:defaultZ31-1021h px? 
r

Phase %s%s
101*constraints2
2 2default:default2%
BUFG optimization2default:defaultZ18-101h px? 
D
/Phase 2 BUFG optimization | Checksum: 86fb2766
*commonh px? 
?

%s
*constraints2o
[Time (s): cpu = 00:00:13 ; elapsed = 00:00:11 . Memory (MB): peak = 4916.449 ; gain = 0.0002default:defaulth px? 
?
EPhase %s created %s cells of which %s are BUFGs and removed %s cells.395*opt2%
BUFG optimization2default:default2
02default:default2
02default:default2
02default:defaultZ31-662h px? 
f

Phase %s%s
101*constraints2
3 2default:default2
Remap2default:defaultZ18-101h px? 
9
$Phase 3 Remap | Checksum: 11551fa27
*commonh px? 
?

%s
*constraints2o
[Time (s): cpu = 00:00:17 ; elapsed = 00:00:14 . Memory (MB): peak = 4916.449 ; gain = 0.0002default:defaulth px? 
?
.Phase %s created %s cells and removed %s cells267*opt2
Remap2default:default2
1482default:default2
3042default:defaultZ31-389h px? 
?
?In phase %s, %s netlist objects are constrained preventing optimization. Please run opt_design with -debug_log to get more detail. 510*opt2
Remap2default:default2
112default:defaultZ31-1021h px? 
x

Phase %s%s
101*constraints2
4 2default:default2+
Post Processing Netlist2default:defaultZ18-101h px? 
K
6Phase 4 Post Processing Netlist | Checksum: 158eae9cb
*commonh px? 
?

%s
*constraints2o
[Time (s): cpu = 00:00:17 ; elapsed = 00:00:15 . Memory (MB): peak = 4916.449 ; gain = 0.0002default:defaulth px? 
?
.Phase %s created %s cells and removed %s cells267*opt2+
Post Processing Netlist2default:default2
02default:default2
02default:defaultZ31-389h px? 
?
?In phase %s, %s netlist objects are constrained preventing optimization. Please run opt_design with -debug_log to get more detail. 510*opt2+
Post Processing Netlist2default:default2
302default:defaultZ31-1021h px? 
/
Opt_design Change Summary
*commonh px? 
/
=========================
*commonh px? 


*commonh px? 


*commonh px? 
?
v---------------------------------------------------------------------------------------------------------------------
*commonh px? 
?
?|  Phase                    |  #Cells created  |  #Cells Removed  |  #Constrained objects preventing optimizations  |
---------------------------------------------------------------------------------------------------------------------
*commonh px? 
?
?|  Retarget                 |               3  |              29  |                                             30  |
|  BUFG optimization        |               0  |               0  |                                              0  |
|  Remap                    |             148  |             304  |                                             11  |
|  Post Processing Netlist  |               0  |               0  |                                             30  |
---------------------------------------------------------------------------------------------------------------------
*commonh px? 


*commonh px? 


*commonh px? 
I
4Ending Logic Optimization Task | Checksum: 3bfd25ab
*commonh px? 
?

%s
*constraints2o
[Time (s): cpu = 00:00:18 ; elapsed = 00:00:15 . Memory (MB): peak = 4916.449 ; gain = 0.0002default:defaulth px? 
b

Starting %s Task
103*constraints2'
Netlist Obfuscation2default:defaultZ18-103h px? 
?
I%sTime (s): cpu = %s ; elapsed = %s . Memory (MB): peak = %s ; gain = %s
268*common2.
Netlist sorting complete. 2default:default2
00:00:002default:default2 
00:00:00.0592default:default2
4916.4492default:default2
0.0002default:defaultZ17-268h px? 
J
5Ending Netlist Obfuscation Task | Checksum: 3bfd25ab
*commonh px? 
?

%s
*constraints2s
_Time (s): cpu = 00:00:00 ; elapsed = 00:00:00.059 . Memory (MB): peak = 4916.449 ; gain = 0.0002default:defaulth px? 
Z
Releasing license: %s
83*common2"
Implementation2default:defaultZ17-83h px? 
?
G%s Infos, %s Warnings, %s Critical Warnings and %s Errors encountered.
28*	vivadotcl2
782default:default2
42default:default2
02default:default2
02default:defaultZ4-41h px? 
b
%s completed successfully
29*	vivadotcl2$
power_opt_design2default:defaultZ4-42h px? 
?
I%sTime (s): cpu = %s ; elapsed = %s . Memory (MB): peak = %s ; gain = %s
268*common2&
power_opt_design: 2default:default2
00:04:462default:default2
00:03:302default:default2
4916.4492default:default2
1537.1722default:defaultZ17-268h px? 
H
&Writing timing data to binary archive.266*timingZ38-480h px? 
?
 The %s '%s' has been generated.
621*common2

checkpoint2default:default2[
GD:/Capstone/project_1/project_1.runs/impl_1/design_1_wrapper_pwropt.dcp2default:defaultZ17-1381h px? 
?
I%sTime (s): cpu = %s ; elapsed = %s . Memory (MB): peak = %s ; gain = %s
268*common2&
write_checkpoint: 2default:default2
00:00:202default:default2
00:00:122default:default2
4916.4492default:default2
0.0002default:defaultZ17-268h px? 


End Record