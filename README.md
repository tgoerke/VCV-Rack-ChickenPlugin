# VCV-Rack-ChickenPlugin
The Chicken Module for VCV Rack

If the clock input is connected it's a dual S&H with slew, range and
offset. Otherwise it's two lowpass filters of signals connected to Mod1
& Mod2 with knobs used for cutoff and resonance freq.

The module code was transcibed from a video by
Leonardo Laguna Ruiz, author of the vult language:

Tutorial: Programming Modules for VCV Rack
https://www.youtube.com/watch?v=oF-swv76odY

It demonstrates how to integrate DSP code generated by vult
into a VCV Rack module.

CHANGELOG

Initial Plugin & Module code generated by helper.py
Add: vult runtime files v0.4.5
Add: Module using vult-generated code
Add: Chicken module - Dual S&H with slew
Add: factored out channel() function
Add: Slewed S&H and lowpass filter modes
