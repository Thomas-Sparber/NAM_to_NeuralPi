#include <iostream>
#include <cmath>
#include <cstdint>
#include <thread>
#include <chrono>
#include <AudioFile.h>

#include "ResamplingNAM.h"

int main(int argc, char *args[])
{
    if(argc < 3)
	{
		std::cout<<"Please provide args: "<<args[0]<<" "<<"[Sample WAV file] [NAM-file1] [NAM-file2] ... [NAM-fileN]"<<std::endl;
		return 1;
	}

	std::vector<bool> threadStatus(argc - 2);
	std::vector<std::thread> threads(argc - 2);
	std::vector<int> percent(argc - 2);

	std::cout<<"Processing..."<<std::endl;

	//Load NAM file
	for(int i = 2; i < argc; i++)
	{
		threadStatus[i - 2] = true;

		threads[i - 2] = std::thread([i, argc, args, &percent, &threadStatus]()
		{
			int blocksize = 2048;

			try {
				//Load example audio
				const std::string inputFilePath(args[1]); 
				AudioFile<double> a;
				a.load (inputFilePath);

				std::filesystem::path path = args[i];
				std::unique_ptr<nam::DSP> model = nam::get_dsp(path);
				std::unique_ptr<ResamplingNAM> model_nam = std::make_unique<ResamplingNAM>(std::move(model), a.getSampleRate());
				model_nam->Reset(a.getSampleRate(), blocksize);
				
				//Process example audio with NAM model
				double *readPointer = &a.samples[0][0];
				double *writePointer = &a.samples[0][0];
				int numSamples = a.getNumSamplesPerChannel();
				
				while(numSamples > 0)
				{
					int currentNumSamples = std::min(numSamples, blocksize);
					model_nam->process(readPointer, writePointer, currentNumSamples);
					model_nam->finalize_(currentNumSamples);

					readPointer += currentNumSamples;
					writePointer += currentNumSamples;
					numSamples -= currentNumSamples;

					percent[i - 2] = (a.getNumSamplesPerChannel() - numSamples) * 100 / a.getNumSamplesPerChannel();
				}
				
				std::string outputFilePath;
				if(argc == 3)outputFilePath = "out.wav";
				else outputFilePath = std::string("out") + std::to_string(i - 1) + ".wav";
				a.save (outputFilePath, AudioFileFormat::Wave);
			}
			catch(const std::runtime_error &e)
			{
				std::cout<<"Runtime error: "<<e.what()<<std::endl;
			}

			threadStatus[i - 2] = false;
		});
	}

	bool running = true;
	while(running)
	{
		int sum = 0;
		for(int p : percent)sum += p;
		sum = sum / percent.size();

		std::cout<<"\r"<<sum<<" % "<<std::flush;

		bool oneRunning = false;
		for(bool r : threadStatus)oneRunning = oneRunning || r;

		if(!oneRunning)running = false;

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	for(int i = 0; i < threads.size(); ++i)
	{
		threads[i].join();
	}

	std::cout<<"\rFinished"<<std::endl;
}
