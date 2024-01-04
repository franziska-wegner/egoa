/*
 * SolverRuntimeCollection.hpp
 *
 *  Created on: Jan 29, 2019
 *      Author: Franziska Wegner
 */

#ifndef EGOA__IO__STATISTICS__GUROBI_INFO_COLLECTION_HPP
#define EGOA__IO__STATISTICS__GUROBI_INFO_COLLECTION_HPP

#include "IO/Statistics/SolverRuntimeRow.hpp"
#include "IO/Statistics/SolverRuntimeCollection.hpp"

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;

namespace egoa::IO {

class SolverRuntimeCollection {
    public:
        using TRow  = SolverRuntimeRow;


        ///@name Constructor and destructor
        ///@{
#pragma mark CONSTRUCTORS_AND_DESTRUCTOR
            SolverRuntimeCollection()
            : information()
            , min(), max(), avg()
            , filename_("SolverRuntimeCollectionFilename")
            , verbose_(false)
            , name_("SolverRuntimeCollectionName")
            , numberOfVertices_(0)
            , numberOfEdges_(0)
            {}

            SolverRuntimeCollection ( Types::string filename
                                    , bool          verbose
                                    , Types::string name
                                    )
            : information()
            , min(), max(), avg()
            , filename_(filename)
            , verbose_(verbose)
            , name_(name)
            , numberOfVertices_(0)
            , numberOfEdges_(0)
            { }
        ///@}

        ///@name Operators
        ///@{
#pragma mark OPERATORS
            inline SolverRuntimeCollection & operator+= ( TRow & rhs )
            {
                if (verbose_)
                {
                    rhs.Name           = name_;
                    rhs.NumberOfEdges  = numberOfEdges_;
                    DumpLine ( filename_, rhs, false );
                }
                else information.push_back(rhs);
                return *this;
            }

            inline void AddMeta ( Types::name  name
                                , Types::count nrVertices
                                , Types::count nrEdges
                                )
            {
                for ( auto & info : information )
                {
                    info.Name               = name;
                    info.NumberOfVertices   = nrVertices;
                    info.NumberOfEdges      = nrEdges;
                }
            }

            // Compute statistics.
            inline void ComputeStatistics()
            {
                if ( information.empty() ) return;

                // Compute average, minimum, and maximum.
                avg = information[0];
                min = information[0];
                max = information[0];

                for ( size_t i = 1; i < information.size(); ++i )
                {
                    avg += information[i];
                    min.Min(information[i]);
                    max.Max(information[i]);
                }
                avg /= information.size();
            }
        ///@}


        ///@name Output
        ///@{
#pragma mark OUTPUT

            inline void Dump ( ostream & os )
            {
                if ( information.empty() ) return;
                // ComputeStatistics();
                os  << "\n"
                    << "Statistics:" << std::endl
                    << "-----------" << std::endl

                    << std::setprecision(2)
                    << std::fixed

                    << setw(30) << "Problem: "              << setw(8)  << information[0].NameOfProblem         << ", "     << std::endl
                    << setw(30) << "Name: "                 << setw(8)  << information[0].Name                  << ", "     << std::endl

                    << setw(30) << "Number of vertices: "   << setw(8)  << information[0].NumberOfVertices      << ", "     << std::endl
                    << setw(30) << "Number of edges: "      << setw(8)  << information[0].NumberOfEdges         << ", "     << std::endl

                    << setw(30) << "Total time: "           << setw(8)  << avg.OptimizationRuntimeSeconds       << setw(11) << " sec (avg), "
                                                            << setw(8)  << min.OptimizationRuntimeSeconds       << setw(11) << " sec (min), "
                                                            << setw(8)  << max.OptimizationRuntimeSeconds       << setw(11) << " sec (max)"    << std::endl

                    << setw(30) << "Solutions: "            << setw(8)  << avg.Solution                         << setw(11) << " (avg), "
                                                            << setw(8)  << min.Solution                         << setw(11) << " (min), "
                                                            << setw(8)  << max.Solution                         << setw(11) << " (max)"       << std::endl

                    << setw(30) << "MipGap: "               << setw(8)  << avg.MipGap                           << setw(11) << " (avg), "
                                                            << setw(8)  << min.MipGap                           << setw(11) << " (min), "
                                                            << setw(8)  << max.MipGap                           << setw(11) << " (max)"       << std::endl

                    << setw(30) << "Upper bound: "          << setw(8)  << avg.UpperBound                       << setw(11) << " (avg), "
                                                            << setw(8)  << min.UpperBound                       << setw(11) << " (min), "
                                                            << setw(8)  << max.UpperBound                       << setw(11) << " (max)"       << std::endl

                    << setw(30) << "Lower bound: "          << setw(8)  << avg.LowerBound                       << setw(11) << " (avg), "
                                                            << setw(8)  << min.LowerBound                       << setw(11) << " (min), "
                                                            << setw(8)  << max.LowerBound                       << setw(11) << " (max)"       << std::endl

                    << setw(30) << "NumberOfVariables: "    << setw(8)  << avg.NumberOfVariables                << setw(11) << " (avg), "
                                                            << setw(8)  << min.NumberOfVariables                << setw(11) << " (min), "
                                                            << setw(8)  << max.NumberOfVariables                << setw(11) << " (max)"       << std::endl
                    << setw(30) << "NumberOfConstraints: "  << setw(8)  << avg.NumberOfConstraints              << setw(11) << " (avg), "
                                                            << setw(8)  << min.NumberOfConstraints              << setw(11) << " (min), "
                                                            << setw(8)  << max.NumberOfConstraints              << setw(11) << " (max)"       << std::endl
                    << setw(30) << "NumberOfConstraints: "  << setw(8)  << avg.NumberOfSoS                      << setw(11) << " (avg), "
                                                            << setw(8)  << min.NumberOfSoS                      << setw(11) << " (min), "
                                                            << setw(8)  << max.NumberOfSoS                      << setw(11) << " (max)"       << std::endl
                    << setw(30) << "NumberOfQConstrains: "  << setw(8)  << avg.NumberOfQConstrains              << setw(11) << " (avg), "
                                                            << setw(8)  << min.NumberOfQConstrains              << setw(11) << " (min), "
                                                            << setw(8)  << max.NumberOfQConstrains              << setw(11) << " (max)"       << std::endl
                    << setw(30) << "NumberOfQConstrains: "  << setw(8)  << avg.NumberOfGenConstrains            << setw(11) << " (avg), "
                                                            << setw(8)  << min.NumberOfGenConstrains            << setw(11) << " (min), "
                                                            << setw(8)  << max.NumberOfGenConstrains            << setw(11) << " (max)"       << std::endl
                    << setw(30) << "NumberOfNZs: "          << setw(8)  << avg.NumberOfNZs                      << setw(11) << " (avg), "
                                                            << setw(8)  << min.NumberOfNZs                      << setw(11) << " (min), "
                                                            << setw(8)  << max.NumberOfNZs                      << setw(11) << " (max)"       << std::endl
                    << setw(30) << "NumberOfIntVars: "      << setw(8)  << avg.NumberOfIntVars                  << setw(11) << " (avg), "
                                                            << setw(8)  << min.NumberOfIntVars                  << setw(11) << " (min), "
                                                            << setw(8)  << max.NumberOfIntVars                  << setw(11) << " (max)"       << std::endl
                    << setw(30) << "NumberOfBinaryVars: "   << setw(8)  << avg.NumberOfBinaryVars               << setw(11) << " (avg), "
                                                            << setw(8)  << min.NumberOfBinaryVars               << setw(11) << " (min), "
                                                            << setw(8)  << max.NumberOfBinaryVars               << setw(11) << " (max)"       << std::endl
                    << std::endl;
            }

            inline void DumpLine ( Types::string    const   filename
                                 , TRow             const & info
                                 , bool             const   overwrite = false ) const
            {
#ifndef NDEBUG
                qDebug() << "Dumping debug data to: " << QString::fromStdString(filename);
#endif
                // Open output stream.
                // ofstream f(filename);
                std::ofstream f;
                overwrite?f.open(filename, std::ofstream::trunc):f.open(filename, std::ofstream::app);
                if (!f.is_open()) return;

                // GurobiInfo::Header(f);
                // file is empty
                f.seekp(0, ios::end);
                if ( f.tellp() == 0 ) { TRow::Header(f); }

                info.Content(f);
            }

            inline void Dump ( std::string const filename
                             , bool        const overwrite = true ) const
            {
#ifdef NDEBUG
                qDebug() << "Dumping debug data to: " << QString::fromStdString(filename);
#endif
                // Open output stream.
                // ofstream f(filename);
                std::ofstream f;
                overwrite?f.open(filename, std::ofstream::trunc):f.open(filename, std::ofstream::app);
                if (!f.is_open()) return;

                // GurobiInfo::Header(f);
                // file is empty
                f.seekp(0, ios::end);
                if ( f.tellp() == 0 ) { TRow::Header(f); }

                for ( const auto & info : information ) { info.Content(f); }
            }
        ///@}


        inline Types::count   NumberOfVertices () const { return numberOfVertices_; }
        inline Types::count & NumberOfVertices ()       { return numberOfVertices_; }

        inline Types::count   NumberOfEdges () const { return numberOfEdges_; }
        inline Types::count & NumberOfEdges ()       { return numberOfEdges_; }

    private:
        ///@name Member
        ///@{
#pragma mark MEMBER
            vector<TRow> information;
            TRow min, max, avg;

            Types::name filename_;
            bool verbose_;

            Types::name problemName_;
            Types::name name_;

            Types::count numberOfVertices_;
            Types::count numberOfEdges_;
        ///@}
};

} // namespace egoa::IO

#endif // EGOA__IO__STATISTICS__GUROBI_INFO_COLLECTION_HPP
