sqr2 = 1.414213562;
if (lowpass) {
   c = 1 / tan((PI / sampleRate) * cutoffFreq);
   c2 = c * c;
   csqr2 = sqr2 * c;
   d = (c2 + csqr2 + 1);
   ampIn0 = 1 / d;
   ampIn1 = ampIn0 + ampIn0;
   ampIn2 = ampIn0;
   ampOut1 = (2 * (1 - c2)) / d;
   ampOut2 = (c2 – csqr2 + 1) / d;






} else if (highpass) {
   c = tan((PI / sampleRate) * cutoffFreq);
   c2 = c * c;
   csqr2 = sqr2 * c;
   d = (c2 + csqr2 + 1);
   ampIn0 = 1 / d;
   ampIn1 = -(ampIn0 + ampIn0)
   ampIn2 = ampIn0;
   ampOut1 = (2 * (c2 – 1)) / d;
   ampOut2 = (1 - csqr2 + c2) / d;
} else if (bandpass) {
   c = 1 / tan((PI / sampleRate) * cutoffFreq);
   d = 1 + c;
   ampIn0 = 1 / d;
   ampIn1 = 0;
   ampIn2 = -ampIn0;
   ampOut1 = (-c*2*cos(twoPI*cutoffFreq/sr)) / d;
   ampOut2 = (c – 1) / d;
}
out = (ampIn0 * in)
    + (ampIn1 * dlyIn1)
    + (ampIn2 * dlyIn2)
–    (ampOut1 * dlyOut1)
–    (ampOut2 * dlyOut2);
dlyOut2 = dlyOut1;
dlyOut1 = out;
dlyIn2 = dlyIn1;
dlyIn1 = in;
return out * gain;
