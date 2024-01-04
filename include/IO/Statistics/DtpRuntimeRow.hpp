/*
 * DtpRuntimeRow.hpp
 *
 *  Created on: Feb 03, 2019
 *      Author: Franziska Wegner
 */

#ifndef EGOA__IO__STATISTICS__DTP_RUNTIME_ROW_HPP
#define EGOA__IO__STATISTICS__DTP_RUNTIME_ROW_HPP

#include <fstream>
#include <iostream>
#include <vector>

#include "Auxiliary/Constants.hpp"
#include "Auxiliary/Types.hpp"

namespace egoa::IO {

/**
 * @brief      Statistics about one execution of the DTP algorithm.
 *
 * @see        egoa::DominatingThetaPath
 */
class DtpRuntimeRow {
    public:
        Types::string NameOfProblem;                /**< The name of the problem that is solved. */
        Types::name   Name;                         /**< The name of the instance. */

        Types::vertexId  SourceId;                  /**< The source identifier. */

        Types::count  NumberOfVertices;             /**< The number of vertices. */
        Types::count  NumberOfGenerators;           /**< The number of generators. */
        Types::count  NumberOfLoads;                /**< The number of loads. */
        Types::count  NumberOfEdges;                /**< The number of edges. */

        Types::count  NumberOfEdgesProducingNoCycle;/**< The number of edges that produce not a cycle. */
        Types::count  NumberOfRelaxedEdges;         /**< The number of relaxed edges. */
        Types::count  NumberOfScannedEdges;         /**< The number of scanned edges. */
        Types::count  NumberOfLabels;               /**< The number of labels. */

        Types::real   GlobalElapsedMilliseconds;    /**< The total runtime. */

        DtpRuntimeRow() :
            NameOfProblem("DTP")
            , Name("")

            , SourceId(0)

            , NumberOfVertices(0)
            , NumberOfGenerators(0)
            , NumberOfLoads(0)
            , NumberOfEdges(0)

            , NumberOfEdgesProducingNoCycle(0)
            , NumberOfRelaxedEdges(0)
            , NumberOfScannedEdges(0)
            , NumberOfLabels(0)

            , GlobalElapsedMilliseconds(0.0)
            {}

        inline void Clear () {
            NameOfProblem = "DTP";
            Name = "";
            SourceId = 0;
            NumberOfVertices = 0;
            NumberOfGenerators = 0;
            NumberOfLoads = 0;
            NumberOfEdges = 0;
            NumberOfScannedEdges = 0;
            NumberOfEdgesProducingNoCycle = 0;
            NumberOfRelaxedEdges = 0;
            GlobalElapsedMilliseconds = 0;
            NumberOfLabels = 0;
        }

        inline static void Header ( std::ostream & os )
        {
            os
                << "NameOfProblem"              << ",\t"
                << "Name"                       << ",\t"

                << "SourceId"                   << ",\t"

                << "NumberOfVertices"           << ",\t"
                << "NumberOfGenerators"         << ",\t"
                << "NumberOfLoads"              << ",\t"
                << "NumberOfEdges"              << ",\t"

                << "NumberOfScannedEdges"       << ",\t"
                << "NumberOfEdgesProducingNoCycle"<< ",\t"
                << "NumberOfRelaxedEdges"       << ",\t"

                << "NumberOfLabels"             << ",\t"

                << "GlobalElapsedMilliseconds"  << ",\t"

                << "\n";
        }

        inline void Content ( std::ostream & os ) const
        {
            os
                << NameOfProblem                << ",\t"
                << Name                         << ",\t"

                << SourceId                     << ",\t"

                << NumberOfVertices             << ",\t"
                << NumberOfGenerators           << ",\t"
                << NumberOfLoads                << ",\t"
                << NumberOfEdges                << ",\t"

                << NumberOfScannedEdges         << ",\t"
                << NumberOfEdgesProducingNoCycle<< ",\t"
                << NumberOfRelaxedEdges         << ",\t"

                << NumberOfLabels               << ",\t"

                << GlobalElapsedMilliseconds

                << "\n";
        }

        inline DtpRuntimeRow & operator+= ( const DtpRuntimeRow & rhs )
        {
            NumberOfEdgesProducingNoCycle   += rhs.NumberOfEdgesProducingNoCycle;
            NumberOfRelaxedEdges            += rhs.NumberOfRelaxedEdges;
            NumberOfScannedEdges            += rhs.NumberOfScannedEdges;
            NumberOfLabels                  += rhs.NumberOfLabels;

            GlobalElapsedMilliseconds       += rhs.GlobalElapsedMilliseconds;

            return *this;
        }

        friend std::ostream & operator<< ( std::ostream  & os
                                         , DtpRuntimeRow & dtpRuntimeRow )
        {
            dtpRuntimeRow.Content ( os );
            return os;
        }

        inline void WriteRowToFileWith ( Types::string const filename
                                       , bool                overwrite = false )
        {
#ifndef NDEBUG
            std::cout << "Write DTP runtime information row to: " << filename << std::endl;
#endif
            // Open output stream.
            // ofstream fileStream(filename);
            std::ofstream fileStream;
            overwrite?fileStream.open(filename, std::ofstream::trunc):fileStream.open(filename, std::ofstream::app);
            if (!fileStream.is_open()) return;

            // file is empty
            fileStream.seekp(0, std::ios::end);
            if ( fileStream.tellp() == 0 )
            {
                DtpRuntimeRow::Header(fileStream);
            }

            fileStream << *this;
        }
};

} // namespace egoa::IO

#endif // EGOA__IO__STATISTICS__DTP_RUNTIME_ROW_HPP
