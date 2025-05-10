# TriggerBox
Programmable MIMO synchronization device: software and hardware design  
![image](https://github.com/siyanghao/TriggerBox/assets/49823842/441866c8-93c6-4346-a01a-04c31f9e7951)

### Input
- **Active Triggers (source):** Reads TTL signal rising edge (5V) from the TriggerBox system. Intended to coordinate with a manually conducted push-trigger.  
- **Passive Triggers (sink):** Reads TTL signal rising edge (5V) from other systems, current rated to 20mA (e.g., a trigger signal from a motion controller or high-speed camera).

### Output
- **Flash:** A driving pulse to a standard LED diode  
- **Beep:** Drives a buzzer with a specific tone  
- **Trigger Signal:** Sends a TTL signal to other systems, 5V 20mA or amplified with an LM386 amplifier  
- **Gate:** Stays high when the system is armed, low when disarmed

## Logic

### V2.6: General-purpose version
- The system reads a trigger input signal, either manual or motion pulse  
- The system gets armed  
- Flashes and beeps with a programmed pattern  
- Trigger output is sent simultaneously; gate remains high  
- Another trigger input disarms the system with a flash, beep, and trigger output

### V3.01: New features for PIV/Laser system
- Takes inputs from the safety curtain and PTUX to control the gate of the DM laser  
- Armed by push trigger  
- Opens the laser gate only if the system is armed and LaVision is ready (PTU output HIGH)  
- The system is disarmed by pressing the manual trigger again or if an object falls through the safety curtain

## Software

- **TriggerBox**: Arduino code to drive the box  
- **TriggerFinder**: `{rising, falling} = TriggerFinder(High, Low, State)`  
  - MATLAB function for post-processing the trigger signal  
  - Digitizes: sets any value below *Low* to 0 and any value above *High* to 5  
  - Derivative used to find peaks at rising and falling edges  
- **BeepFinder**  
  - Detects beep tones collected by a microphone in post-processing  
  - Uses Short-Time Fourier Transform (STFT) to visualize time history of the spectrum  
  - Uses cross-correlation to find beep patterns on the STFT  
- **InlineTrigger**  
  - Generates a burst of pulses upon receiving one TTL pulse  

## Hardware

The listed hardware has been verified to be compatible. Alternatives may also be used since these are standard components.

- Arduino (Nano, Uno for legacy versions)  
- Shield board: see PCB design  
- 3–24V buzzer, for [example](https://www.amazon.com/QMseller-3-24V-Sound-Electronic-Buzzer/dp/B07XFFP42C/ref=...) — loud enough :)  
- [LED diode](https://www.sparkfun.com/products/13104) — very bright...  
- [LM386 Amplifiers](https://www.amazon.com/Amplifier-Module-Adjustable-Resistance-Ar-duino/dp/B0956WKJHJ/ref=...)  
- [LED driver](https://www.sparkfun.com/products/13716)

## PCB Design

- The shield board is customized for hardware interface  
- The design files are provided in the PCB design `.zip` archive  
- We chose [JLCPCB](https://jlcpcb.com/?from=VG_PCBA...) as our manufacturer
