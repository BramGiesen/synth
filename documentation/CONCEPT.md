Synthesizer
==

##### Minimaal:

* 1 waveform:
  * sine

 * 2 oscillatoren:
    * carrier
    * modulator

 * FM-synthese

 * Instellingen zijn aan te passen terwijl het programma draait
  * instellen van de ADSR
  * instellen fm, ratio en modulatie diepte

 * Bestuurbaar met midi via OSC
  * client waar de MIDI informatie binnen komt
  * de Synth is de server waar de MIDI informatie naar toe wordt gestuurd

 * ADSR

 * Simpele filters
   * low-pass
  * high-pass

 * Multithreading
  * thread voor het afspelen van de audio en eentje voor het binnenhalen van de MIDI informatie en andere controls.

##### extra's:

 * LFO
  * LFO op het volume of de pitch

 * Effecten bijv:
  * delay
  * chorus

 * Polyfoon
