# NAM_to_NeuralPi

You can use this repo to execute NAM models with a WAV file. The main purpose of this is to convert NAM models to [NeuralPi](https://github.com/GuitarML/NeuralPi) or [Proteus](https://github.com/GuitarML/Proteus). The generated WAV files can then be used to upload the Keith's Colab script to generate to model.

# Building

    git clone https://github.com/Thomas-Sparber/NAM_to_NeuralPi
    cd NAM_to_NeuralPi
    git submodule update --init --recursive
    mkdir Build
    cd Build
    cmake ..
    make

This will give you the executable `Build NAM_to_NeuralPi`

# Usage

    ./NAM_to_NeuralPi [path-to wav file] [NAM-model-1] [NAM-model-2] ... [NAM-model-N]

You can already use the WAV file prepared by Keith which is in the correct format to be used for NeuralPi or Proteus:

    ./NAM_to_NeuralPi Proteus_Capture_Utility/Proteus_Capture.wav [NAM-model-1] [NAM-model-2] ... [NAM-model-N]

The wav file will then be processed using the NAM model and the result is stored as `out.wav` if only one NAM model is provided or `out1.wav`, `out2.wav`, ..., `outN.wav`
