# TriggerBox
Programmable MIMO synchronization device, software, and hardware design 
![image](https://github.com/siyanghao/TriggerBox/assets/49823842/441866c8-93c6-4346-a01a-04c31f9e7951)
### Input
- Active Triggers (source): Read TTL signal rising edge (5V) from the TriggerBox system. Intend to coordinate with a conducting manual push-trigger.
- Passive Triggers (sink): Read TTL signal rising edge (5V) from other systems, current rated to 20mA. e.g., the trigger signal from a motion controller or high-speed cameras.

### Output
- Flash: A driving pules to standard LED diode 
- Beep: Drives a buzzer with specfic tone.
- Trigger Signal: Give a TTL signal to other systems, 5V 20mA or amplified with LM386 amplifier.
- Gate: keeps high when the system gets armed, low when disarmed.
## Logic
### V2.6: General purpose version
- The system reads a trigger input signal, either manual or motion pules,
- The system gets armed, 
- flashing and buzzing with a programmed pattern, 
- trigger output sent out simultaneously, gate keeps high.
- Another Trigger input will disarm the system with a flash, buzz, and trigger output.
### V3.01: New features added to work with PIV/Laser system
  - Take inputs from the safety curtain and PTUX to control the gate of the DM laser
  - Armed by push trigger 
  - Open the laser gate only if the system is armed and LaVision is ready(PTU output  HIGH)
  - The system disarmed by pushing the manual trigger again or objects fall through the safety curtain
## Software
- TriggerBox Arduino code to drive the box
- TriggerFinder: {rising falling] = TriggerFinder( High, Low, State)
  - Matlab function for postprocessing the trigger signal
  - Digitize: Set any value lower than Low to 0 and any value higher than High to 5
  - Derivation and find a peak to find all rising and falling edge
- Beepfinder:
  - find the beep tone collected by microphone in postprocessing
  - short time Fourier transformation (STFT) to present a time history of spectrum
  - Cross-correlation to find a beep pattern on the STFT
- InlineTrigger
  - Generate a brust of pluses on the receiving of one TTL pluse. 
## Hardware
The listed hardware has been testified to be completable.  Other alternatives may also be found since they are just common components
- Arduino (nano, Uno for legacy versions)
- Shield board: see PCB design
- 3-24V buzzer, for [example](https://www.amazon.com/QMseller-3-24V-Sound-Electronic-Buzzer/dp/B07XFFP42C/ref=sxin_16_pa_sp_search_thematic_sspa?content-id=amzn1.sym.570e7680-987b-4043-baad-ab61ea81d6c9%3Aamzn1.sym.570e7680-987b-4043-baad-ab61ea81d6c9&crid=1WLGGAO938HNU&cv_ct_cx=buzzer&keywords=buzzer&pd_rd_i=B07XFFP42C&pd_rd_r=f29132bb-8375-4041-954c-5aa37497188b&pd_rd_w=RFXWC&pd_rd_wg=8bFRS&pf_rd_p=570e7680-987b-4043-baad-ab61ea81d6c9&pf_rd_r=MCXN9FYSWM9ABPXXSY7F&qid=1680539976&sbo=RZvfv%2F%2FHxDF%2BO5021pAnSA%3D%3D&sprefix=buzzer%2Caps%2C99&sr=1-2-a73d1c8c-2fd2-4f19-aa41-2df022bcb241-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUExR0NHSVBLNjJOQzBRJmVuY3J5cHRlZElkPUEwOTQ1NDcwMk1SU1c0NFNESTkxUSZlbmNyeXB0ZWRBZElkPUEwOTYzMDA5MzJRTlQ4OUJUQ1JPMSZ3aWRnZXROYW1lPXNwX3NlYXJjaF90aGVtYXRpYyZhY3Rpb249Y2xpY2tSZWRpcmVjdCZkb05vdExvZ0NsaWNrPXRydWU=), which is loud enough :)
- [Led diode](https://www.sparkfun.com/products/13104), which is really bright...
- [LM386 Amplifiers](https://www.amazon.com/Amplifier-Module-Adjustable-Resistance-Ar-duino/dp/B0956WKJHJ/ref=sr_1_8?hvadid=616931664211&hvdev=c&hvlocphy=9002242&hvnetw=g&hvqmt=e&hvrand=5603527551695194777&hvtargid=kwd-137410832&hydadcr=26610_11715041&keywords=lm386&qid=1680539348&sr=8-8) 
- [LED driver](https://www.sparkfun.com/products/13716)
## PCB Design
- The shield board is customized for the interface with hardware.
- The design can be found in another folder.
- we choose [JLC](https://jlcpcb.com/?from=VG_PCBA&gclid=Cj0KCQjw8qmhBhClARIsANAtbodja4d4qfanlhSsr53VilFTFaHDHzYB8yUYQeh8ex-eZa1-4ntCvNQaAkl_EALw_wcB) as our manufacture. 
