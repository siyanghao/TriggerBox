# TriggerBox
Programmable MIMO synchronization device, software and hardward design 

### Input
- Active Trigger : Read TTL signal rising edge powered with 5V from the system. Intend to coordinate with a conducting mannul push-trigger.
- Passive Trigger: Read TTL signal rising edge powered with 5V from other system, current rated to 20mA. e.g. the trigger signal from motion controller or high speed cameras.

### Output
- Flash: A diriving pules to standrad LED diode 
- Beep: Drives a buzzer with specfic tone.
- Trigger Signal: Give a TTL siganl to other system, 5V 20mA or amplified with LM386 ampifier.
- Gate: keeps high when system get armed, low when disarmed.

## Hardwares
Listed hardware has been testified to be complitable.  Other alternaitves may also be found since they are just common comppnents
- Arduino (nano, Uno for lagency versions)
- Sheild board: The shield board is customized for the interface with hardwares. The design can be found in another folder, we choose [JLC](https://jlcpcb.com/?from=VG_PCBA&gclid=Cj0KCQjw8qmhBhClARIsANAtbodja4d4qfanlhSsr53VilFTFaHDHzYB8yUYQeh8ex-eZa1-4ntCvNQaAkl_EALw_wcB) as our manufacture. 
- 3-24V buzzer, for [example](https://www.amazon.com/QMseller-3-24V-Sound-Electronic-Buzzer/dp/B07XFFP42C/ref=sxin_16_pa_sp_search_thematic_sspa?content-id=amzn1.sym.570e7680-987b-4043-baad-ab61ea81d6c9%3Aamzn1.sym.570e7680-987b-4043-baad-ab61ea81d6c9&crid=1WLGGAO938HNU&cv_ct_cx=buzzer&keywords=buzzer&pd_rd_i=B07XFFP42C&pd_rd_r=f29132bb-8375-4041-954c-5aa37497188b&pd_rd_w=RFXWC&pd_rd_wg=8bFRS&pf_rd_p=570e7680-987b-4043-baad-ab61ea81d6c9&pf_rd_r=MCXN9FYSWM9ABPXXSY7F&qid=1680539976&sbo=RZvfv%2F%2FHxDF%2BO5021pAnSA%3D%3D&sprefix=buzzer%2Caps%2C99&sr=1-2-a73d1c8c-2fd2-4f19-aa41-2df022bcb241-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUExR0NHSVBLNjJOQzBRJmVuY3J5cHRlZElkPUEwOTQ1NDcwMk1SU1c0NFNESTkxUSZlbmNyeXB0ZWRBZElkPUEwOTYzMDA5MzJRTlQ4OUJUQ1JPMSZ3aWRnZXROYW1lPXNwX3NlYXJjaF90aGVtYXRpYyZhY3Rpb249Y2xpY2tSZWRpcmVjdCZkb05vdExvZ0NsaWNrPXRydWU=), which is loud enough :)
- [Led diode](https://www.sparkfun.com/products/13104), which is really bright...
- [LM386 Amplifiers](https://www.amazon.com/Amplifier-Module-Adjustable-Resistance-Ar-duino/dp/B0956WKJHJ/ref=sr_1_8?hvadid=616931664211&hvdev=c&hvlocphy=9002242&hvnetw=g&hvqmt=e&hvrand=5603527551695194777&hvtargid=kwd-137410832&hydadcr=26610_11715041&keywords=lm386&qid=1680539348&sr=8-8) 
- [LED driver](https://www.sparkfun.com/products/13716)

## Logic
- The system read a trigger input signal, either manul or motion pules,
 - The system get armed, 
 - flahing and buzzing with programmed pattern, 
 - trigger out put sent out simultaneously, gate keeps high.
- Another Trigger input will disarm the system, with a flash, buzz and trigger output.
## Software
- TriggerBox arduino code to drive the box
- TriggerFinder: {rising falling] = TriggerFinder( High, Low, State)
 - Matlab function for postprocessing the trigger siganl
 - Digitize: Set any value lower than Low to 0 and anyvalue higher than High to 5
 - Derivation and find peak to find all rising and falling edge
- Beepfinder:
 - short time fourier transfromation (STFT) to present a time history of spectrum
 - Cross corelation to find a beep pattern on the STFT
