#include <iostream>
#include <cmath>
#include <cstdint>
#include <AudioFile.h>

#include "ResamplingNAM.h"

int main(int argc, char *args[])
{
    if(argc < 3)
	{
		std::cout<<"Please provide args: "<<args[0]<<" "<<"[Sample WAV file] [NAM-file1] [NAM-file2] ... [NAM-fileN]"<<std::endl;
		return 1;
	}

	//Load example audio
	const std::string inputFilePath(args[1]);
    
	AudioFile<double> a;
	a.load (inputFilePath);

	//Load NAM file
	for(int i = 2; i < argc; i++)
	{
		int blocksize = 2048;

		std::cout<<"Processing "<<args[i]<<std::endl;

		try {
			std::filesystem::path path = args[i];
			std::unique_ptr<nam::DSP> model = nam::get_dsp(path);
			std::unique_ptr<ResamplingNAM> model_nam = std::make_unique<ResamplingNAM>(std::move(model), a.getSampleRate());
			model_nam->Reset(a.getSampleRate(), blocksize);
			
			//Process example audio with NAM model
			double *readPointer = &a.samples[0][0];
			double *writePointer = &a.samples[0][0];
			int numSamples = a.getNumSamplesPerChannel();
			
			std::cout<<numSamples<<" samples left"<<std::flush;
			while(numSamples > 0)
			{
				int currentNumSamples = std::min(numSamples, blocksize);
				model_nam->process(readPointer, writePointer, currentNumSamples);
				model_nam->finalize_(currentNumSamples);

				readPointer += currentNumSamples;
				writePointer += currentNumSamples;
				numSamples -= currentNumSamples;

				std::cout<<"\r"<<numSamples<<" samples left"<<std::flush;
			}

			std::cout<<"NAM finished, saving wav"<<std::endl;
			
			std::string outputFilePath;
			if(argc == 3)outputFilePath = "out.wav";
			else outputFilePath = std::string("out") + std::to_string(i - 1) + ".wav";
			a.save (outputFilePath, AudioFileFormat::Wave);
		}
		catch(const std::runtime_error &e)
		{
			std::cout<<"Runtime error: "<<e.what()<<std::endl;
		}
	}
}
