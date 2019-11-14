/*
 * PowerGridIO.cpp
 *
 *  Created on: Sep 07, 2018
 *      Author: Franziska Wegner
 */

#include "IO/PowerGridIO.hpp"
#include "IO/Parser/IeeeCdfMatlabParser.hpp"
#include "IO/Parser/PyPsaParser.hpp"

namespace egoa {

template<typename GraphType>
const std::vector<typename PowerGridIO<GraphType>::ReaderFunctionStreamBased> PowerGridIO<GraphType>::streamReaders = {
    PowerGridIO<GraphType>::readIeeeCdfMatlab
    //@todo PowerGridIO::readIeeePti
};

template<typename GraphType>
const std::vector<typename PowerGridIO<GraphType>::ReaderFunctionStringBased> PowerGridIO<GraphType>::fileReaders = {
    PowerGridIO<GraphType>::ReadPyPsa
    //@todo PowerGridIO::readIeeePti
};
// 
template<typename GraphType>
const std::vector<typename PowerGridIO<GraphType>::ReaderFunctionStreamBasedPowerGridAndCandidateNetwork> PowerGridIO<GraphType>::streamReadersPowerGridAndCandidateNetwork = {
    PowerGridIO<GraphType>::ReadPyPsa
    //@todo PowerGridIO::readIeeePti
};

template<typename GraphType>
const std::vector<typename PowerGridIO<GraphType>::WriterFunctionStreamBased> PowerGridIO<GraphType>::streamWriters = {
    PowerGridIO<GraphType>::writeIeeeCdfMatlab
    , PowerGridIO<GraphType>::WriteGraphDot
    , PowerGridIO<GraphType>::WriteGeoJson
    //@todo PowerGridIO::readIeeePti
};

template<typename GraphType>
const std::vector<typename PowerGridIO<GraphType>::WriterFunctionStreamBasedtionStringBased> PowerGridIO<GraphType>::fileWriters = {
    PowerGridIO<GraphType>::WriteGraphGml
    , PowerGridIO<GraphType>::WriteGraphDot
    , PowerGridIO<GraphType>::WriteGeoJson
    //@todo PowerGridIO::readIeeePti
};

} // namespace egoa
