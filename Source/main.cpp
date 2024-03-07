#include <iostream>
#include <cmath>
#include <cstdint>
#include <AudioFile.h>

#define NAM_SAMPLE_FLOAT
#include <NAM/dsp.h>

int main(int argc, char *args[])
{
    if(argc < 3)
	{
		std::cout<<"Please provide args: "<<args[0]<<" "<<"[Sample WAV file] [NAM-file1] [NAM-file2] ... [NAM-fileN]"<<std::endl;
		return 1;
	}

	//Load example audio
	const std::string inputFilePath(args[1]);
    
	AudioFile<float> a;
	a.load (inputFilePath);

	//Load NAM file
	for(int i = 2; i < argc; i++)
	{
		std::filesystem::path path = args[i];
		nam::dspData conf = nam::get_dsp_data(path);
		auto model_nam = nam::get_dsp(conf);
		model_nam->prewarm();
		
		//Process example audio with NAM model
		const float *readPointer = &a.samples[0][0];
		float *writePointer = &a.samples[0][0];
		int numSamples = a.getNumSamplesPerChannel();
		int blocksize = 512;
		
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
}