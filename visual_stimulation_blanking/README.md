# Circuit for blanking of the visual stimulation during 2p-imaging

![circuit-diagram-and-logic](https://github.com/thladnik/mariner-experimental-setup/blob/main/visual_stimulation_blanking/fig_appx_circuit_white_bg.png)

### A and B
Image and schematic of the wiring between the Lightcrafter E4500MKII's J29 connector, the Teensy 4.1 microcontroller and the BNC input/output connectors for synchronized blanking to 2-photon imaging of the visual stimulation. 
U1 (sync_in): input for the scan synchronization signal. Either the linescan's flyback signal (for Galvo-Galvo) or the imaging frame synchronization signal (Resonant-Galvo)
U2 (pmt_out): optional digital output for gating of photomultiplier tubes (PMT).
U3-5 (<color>_out): digital output signal for controlling the LED light source (corresponding to the Lightcrafter's blue, green and red channels)

### C
Diagram of gating logic for GalvoGalvo and ResGalvo blanking. Note that both SYNC_IN and PMT_OUT may optionally be inverted, according to microscope or PMT specifications.
