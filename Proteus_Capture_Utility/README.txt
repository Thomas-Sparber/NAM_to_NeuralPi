These are utility files for training a Proteus compatible amp or pedal model. 

Included files:

ProteusCapture.ipynb : A google Colab script for training a Proteus model. This can be uploaded to the Google Colab website. 
                          Instructions are included in the script.

Proteus_Capture.wav  : An input .wav audio file to create output .wav files for capturing Amps or Pedals.
                          Play this audio through your device and record the output. Then upload the output to Colab and use the above script
                          to train a model compatible with the Proteus plugin.

                          Recommended to add this track to your DAW, then output audio from your Audio Interface through a reamper and to your device. 
                          Then run the output of your device back to your Audio Interface (muting the armed recording track to prevent feedback). Record the audio
                          for the duration of this file. For Parameterized capture of a knob/control, record the audio five times, increasing your knob 
                          value in equal steps from 0% (or just above 0%), 25%, 50%, 75%, 100%, then export these as five separate .wav files.


           IMPORTANT INFO:

                          NEVER run speaker level outputs from your amp into your audio device. You must use a load-box to convert the speaker
                          output to a safe level. 

                          Recommended to use a Re-Amp box to convert your line out from your audio device into intrument level for your amp or pedal.

                          For parameterized capture of the full range of a Gain or EQ knob, you will need to create 5 output wav files, starting with
                          the knob at or just above 0% (for knobs where 0% is silent), and continuing with 25%, 50%, 75%, an 100% to create
                          5 new wav files. Once uploaded to Colab, these will need to be renamed to the following:
                                  "out1.wav", "out2.wav", "out3.wav", "out4.wav", "out5.wav"

                          The trained knob model will be able to fill in the gaps between the five steps, re-creating the full range of the knob from 
                          your amp or pedal. This should work well for Gain/Drive or EQ. 
                          
                          
                          
                          This audio contains 3.5 minutes of generated sounds, clean guitar, and bass.
 
                          Note that the WAV format is PCM16, as opposed to FP32 for reduced size.

                  Note: This capture method is limited to non-time based effects (no Delay, Reverb, Flange, Phaser, etc.) 
                        It is intended for Amplifiers and Distortion/Overdrive/Boost effects



GuitarML
https://guitarml.com/
smartguitarml@gmail.com