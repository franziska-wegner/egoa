/*
 * TestGeojsonWriter.cpp
 *
 *  Created on: Nov 04, 2019
 *      Author: Franziska Wegner
 */

#include "TestGeojsonWriter.hpp"
#include "IO/Writer/GeojsonWriter.hpp"

#include "Auxiliary/Types.hpp"
#include "Helper/TestHelper.hpp"

#include <fstream>
#include <sstream>

namespace egoa::test {

TEST_F ( TestGeojsonExample, FilenameWriteTest )
{
    if ( ! egoa::PowerGridIO<TGraph>::write ( network_
                                            , TestCaseSmallExampleOutputFile_
                                            , TPowerGridIO::WriteGeoJson ) )
    {
        ASSERT_TRUE(false);
    }
}

TEST_F ( TestGeojsonExample, OutputStreamWriteTest )
{
    std::ofstream file;
    file.open(TestCaseSmallExampleOutputFile_, std::ofstream::trunc);
    if (!file.is_open()) return;
    file.seekp(0, std::ios::end); // file is empty

    if ( ! egoa::PowerGridIO<TGraph>::write ( network_
                                            , file
                                            , TPowerGridIO::WriteGeoJson ) )
    {
        ASSERT_TRUE(false);
    }
}

TEST_F ( TestGeojsonExample, CompareGeneratedStringWithFile )
{
    // Comparison string
    std::stringstream genfileStream;
    if ( ! egoa::PowerGridIO<TGraph>::write ( network_
                                            , genfileStream
                                            , TPowerGridIO::WriteGeoJson ) )
    {
        EXPECT_TRUE(false);
    }
    Types::string genfile = genfileStream.str();

    // Expected output converted to string
    std::ifstream inFile; inFile.open(TestCaseSmallExampleExpectedOutput_);
    std::stringstream expectedOutputStream;
    expectedOutputStream         << inFile.rdbuf();
    Types::string expectedOutput = expectedOutputStream.str();

    EXPECT_EQ(expectedOutput,genfile);
}

} //namespace egoa::test