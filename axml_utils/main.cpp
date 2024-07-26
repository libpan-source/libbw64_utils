#include <iostream>
#include <sstream>

#include <adm/adm.hpp>
#include <bw64/bw64.hpp>
#include "adm/common_definitions.hpp"
#include "adm/parse.hpp"
#include "adm/write.hpp"

#include "main.h"

const unsigned int BLOCK_SIZE = 4096;

int main(int argc, char *argv[]){

     std::cout << "add axml start. \n";
    auto doc = adm::Document::create();
    auto reader = bw64::readFile(argv[1]);

    auto admDocument = adm::parseXml(argv[3]);

    std::stringstream xmlStream;
    writeXml(xmlStream, admDocument);

	std::vector<std::shared_ptr<adm::AudioTrackUid>> trackids = std::vector<std::shared_ptr<adm::AudioTrackUid>>(admDocument->getElements<adm::AudioTrackUid>().begin(), admDocument->getElements<adm::AudioTrackUid>().end());
	auto chnaChunk = std::make_shared<bw64::ChnaChunk>();
    std::shared_ptr<bw64::AxmlChunk> newxmlChunk(new bw64::AxmlChunk(xmlStream.str()));

    for (auto trackid : trackids)
	{
		auto iindex = trackid.get()->get<adm::AudioTrackUidId>().get<adm::AudioTrackUidIdValue>().get();
		auto uid = formatId(trackid.get()->get<adm::AudioTrackUidId>());
		auto audiopack = trackid.get()->getReference<adm::AudioPackFormat>();
		auto audiotrack = trackid.get()->getReference<adm::AudioTrackFormat>();
		std::string strpackid = "";
		std::string strtrackid = "";
		if (audiopack != nullptr)
		{
			strpackid = formatId(audiopack.get()->get<adm::AudioPackFormatId>());
		}
		if (audiotrack != nullptr)
		{
			strtrackid = formatId(audiotrack.get()->get<adm::AudioTrackFormatId>());
		}

		chnaChunk->addAudioId(
			bw64::AudioId(iindex, std::string(uid.c_str(), 12), std::string(strtrackid.c_str(), 14),
				std::string(strpackid.c_str(), 11)));

	}

    auto outFile = bw64::writeFile(argv[2], reader->channels(), reader->sampleRate(),
                           reader->bitDepth(), chnaChunk, newxmlChunk);

    std::vector<float> buffer(BLOCK_SIZE * reader->channels());
    while (!reader->eof()) {
        auto readFrames = reader->read(&buffer[0], BLOCK_SIZE);
        outFile->write(&buffer[0], readFrames);
    }

    std::cout << "add axml end.\n";
    return 0;
}