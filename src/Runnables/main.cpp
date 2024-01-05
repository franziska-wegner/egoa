/*
 * main.cpp
 *
 *  Created on: Sep 13, 2018
 *      Author: Franziska Wegner
 */

#ifdef OPENMP_AVAILABLE
    #include <omp.h>
#endif // OPENMP_AVAILABLE

#include <clocale>
#include <iostream>
#include <string>
#include <set>
#include <tuple>

#include <QFile>
#include <QStringList>

#include "DataStructures/Labels/Label.hpp"
#include "DataStructures/Labels/SusceptanceNormLabel.hpp"
#include "DataStructures/Labels/VoltageAngleDifferenceLabel.hpp"

#include "Algorithms/SpanningTree/MST.hpp"
#include "Algorithms/SpanningTree/Prim.hpp"
#include "Algorithms/SpanningTree/Kruskal.hpp"

#include <QTimer>
#include <QDebug>
#include <QString>
#include <QApplication>
#include <QCommandLineParser>

#include <cassert>
#include <cmath>
#include <ctime>
#include <memory>
#include <type_traits>

#include "DataStructures/Networks/PowerGrid.hpp"

#include "DataStructures/Graphs/StaticGraph.hpp"
#include "DataStructures/Graphs/DynamicGraph.hpp"
#include "DataStructures/Graphs/Vertices/Vertex.hpp"
#include "DataStructures/Graphs/Vertices/ElectricalProperties.hpp"
#include "DataStructures/Graphs/Edges/Edge.hpp"
#include "DataStructures/Graphs/Edges/ElectricalProperties.hpp"

// #include "MathematicalModel/DirectCurrent/DCPF.hpp"
// #include "MathematicalModel/DirectCurrent/DCMPF.hpp"
// #include "MathematicalModel/DirectCurrent/DCMTSF.hpp"

#include "Auxiliary/Auxiliary.hpp"
#include "Auxiliary/Comparators.hpp"

#include "IO/PowerGridIO.hpp"
#include "IO/Appearance/Color.hpp"

QString inputFile(""), outputDir("");
void addCommandLineOptions ( const QCoreApplication &application,
                             QCommandLineParser     &parser       )
{
    parser.setApplicationDescription("Power Grid Tool");
    parser.addHelpOption();
    parser.addVersionOption();

#pragma mark COMMANDLINE_OPTIONS
    QCommandLineOption algorithmOption(
            "algo",
            QCoreApplication::translate("main", "Algorithm for the problem (default: MILP)."),
            QCoreApplication::translate("main", "algo"), "MILP"
    );
    parser.addOption(algorithmOption);

    QCommandLineOption variantOption(
            "variant",
            QCoreApplication::translate("main", "Variant for the algorithm (default: ?."),
            QCoreApplication::translate("main", "variant"), "?"
    );
    parser.addOption(variantOption);

    QCommandLineOption networkSettingOption(
            "networkSetting",
            QCoreApplication::translate("main", "Network setting (default: exact for PF (not changeable), bounded for DCMPF and DCMTSF)."),
            QCoreApplication::translate("main", "networkSetting"), "bounded"
    );
    parser.addOption(networkSettingOption);

    QCommandLineOption solverOption(
            "solver",
            QCoreApplication::translate("main", "Solver if necessary (default: gurobi)."),
            QCoreApplication::translate("main", "solver"), "gurobi"
    );
    parser.addOption(solverOption);

    QCommandLineOption inputFileWarmStartOption(
        QStringList() << "inputFileWarmStart",
        QCoreApplication::translate("main", "Input file for the warm start (default: ../Data/windfarm-benchmarksets/testset-0-instance-1.gml)."),
        QCoreApplication::translate("main", "inputFileWarmStart"), "WS-testset-0-instance-1.gml"
    );
    parser.addOption(inputFileWarmStartOption);

    QCommandLineOption timeOption(
            "time",
            QCoreApplication::translate("main", "--time <time>  -- specify time limit in seconds (default: 1h)."),
            QCoreApplication::translate("main", "time"), "3600"
    );
    parser.addOption(timeOption);

    QCommandLineOption traceSolutionOption(
            "trace",
            QCoreApplication::translate("main", "--trace <true|false>  -- Trace solution. (default: false)."),
            QCoreApplication::translate("main", "trace"), "false"
    );
    parser.addOption(traceSolutionOption);

    QCommandLineOption verboseOption(
            "verbose",
            QCoreApplication::translate("main", "--verbose <true|false>  -- Verbose mode. Prints out all information. (default: NA)."),
            QCoreApplication::translate("main", "verbose"), "true"
    );
    parser.addOption(verboseOption);

    QCommandLineOption outputTypeOption(
            "outputType",
            QCoreApplication::translate("main", "--outputType GML | DOT | PS | PDF | SVG -- Output type. Outputs the result in the output directory. (default: DOT)."),
            QCoreApplication::translate("main", "outputType"), "DOT"
    );
    parser.addOption(outputTypeOption);


#pragma mark COMMANDLINE_POSITIONAL_ARGUMENTS
    parser.addPositionalArgument(
            "inputFile",
            QCoreApplication::translate("main", "The input file to open.")
    );

    parser.addPositionalArgument(
            "outputDir",
            QCoreApplication::translate("main", "The output directory to write files.")
    );


#pragma mark COMMANDLINE_CHECKS_AND_PROCESSING
    parser.process(application);

    const QStringList args = parser.optionNames();
    // if (args.size() < 1) {
    //     fprintf(stderr, "%s\n", qPrintable(QCoreApplication::translate("main", "Error: Must specify an argument.")));
    //     parser.showHelp(1);
    //     exit(1);
    // }

    QStringList positionalArgs    = parser.positionalArguments();
    if (positionalArgs.count() == 2) {
        inputFile = positionalArgs.at(0);
        outputDir = positionalArgs.at(1);
    } else {
        fprintf(stderr, "%s\n", qPrintable(QCoreApplication::translate("main", "Error: Must specify both argument \"inputFile\" and \"outputDir\".")));
        parser.showHelp(1);
        exit(1);
    }
}

// Decide which graph type to use, meaning either a static or a dynamic graph
#ifndef USE_DYNAMIC_GRAPH
    const bool isStaticGraph = true;
#else
    const bool isStaticGraph = false;
#endif

#ifndef USE_TYPES_REAL_WEIGHT
    const bool isTypesReal = true;
#else
    const bool isTypesReal = false;
#endif

typedef std::conditional<isStaticGraph,
                         egoa::StaticGraph<egoa::Vertices::ElectricalProperties<>, egoa::Edges::ElectricalProperties>,
                         egoa::DynamicGraph<egoa::Vertices::ElectricalProperties<>, egoa::Edges::ElectricalProperties>>::type TGraph;

typedef std::conditional<isTypesReal,
                         egoa::Types::real,
                         egoa::Types::posInteger>::type TWeight;

#ifdef GUROBI_AVAILABLE
    void printGurobiException(const GRBException & e) {
        time_t t   = time(nullptr);   // get time now
        tm* now    = localtime(&t);
        //
        std::cerr << std::string(4*16+3*5, '-')                                                   << std::endl;
        std::cerr << std::setw(16) << "Time"              << " = " << (now->tm_year + 1900)       << '-'
                                                         << (now->tm_mon + 1)           << '-'
                                                         <<  now->tm_mday               << " at "
                                                         <<  now->tm_hour               << ':'
                                                         <<  now->tm_min                << ':'
                                                         <<  now->tm_sec                << " o'clock " << std::endl;
        std::cerr << std::setw(16) << "Error code"        << " = " << e.getErrorCode()            << std::endl;
        std::cerr << std::setw(16) << "Message"           << " = " << e.getMessage()              << std::endl;
    }
#endif

void setNetworkSetting(egoa::PowerGrid<TGraph> & network, const QString & networkSetting) {
    if      ( networkSetting == "BOUNDED"      ) { network.MakeBounded();       }
    else if ( networkSetting == "PUREUNBOUNDED") { network.MakePureUnbounded(); }
    else if ( networkSetting == "UNBOUNDED"    ) { network.MakeUnbounded();     }
    else if ( networkSetting == "EXACT"        ) { network.MakeExact();         }
}

auto main(int const argc, char const * const * const argv) -> int {

// Command line parsing
    auto application = std::unique_ptr<QCoreApplication>(std::make_unique<QCoreApplication>(argc, argv));
    QCoreApplication::setApplicationName("GPGT");
    QCoreApplication::setApplicationVersion("Version: 1");
    std::setlocale(LC_NUMERIC, "C");

// Parse command line
    QCommandLineParser parser;
    addCommandLineOptions(*application, parser);

    auto algorithm          = parser.value("algo").toUpper();
    auto solver             = parser.value("solver").toUpper();
    egoa::Types::real timeLimit   = parser.value("time").toDouble();
    bool traceSolution      = parser.value("trace").toUpper()=="TRUE"?true:false;
    bool verbose            = parser.value("verbose").toUpper()=="TRUE"?true:false;;
    auto networkSetting     = parser.value("networkSetting").toUpper();
    auto variant            = parser.value("variant").toUpper();
    auto outputType         = parser.value("outputType").toUpper();

#ifndef NDEBUG
    qDebug() << Qt::endl;
    qDebug() << "\tInputFile :"   << inputFile;
    qDebug() << "\tOutputDir :"   << outputDir;
    qDebug() << "\tAlgorithm :"   << algorithm;
    qDebug() << "\tVariant   :"   << variant;
    qDebug() << "\tNetwork   :"   << networkSetting;
    qDebug() << "\tSolver    :"   << solver;
    qDebug() << "\tTime      :"   << QString::number(timeLimit);
    qDebug() << "\tTrace Sol.:"   << QString::number(traceSolution);
    qDebug() << "\tVerbose   :"   << QString::number(verbose);
    qDebug() << "\tOutput Type:"  << outputType;
    qDebug() << "---- OpenMP-Info ----------------------------------";
    qDebug() << "\tNumber of Processors:               " << egoa::Auxiliary::NumberOfProcessors();
    qDebug() << "\tMaximum number of possible Threads: " << egoa::Auxiliary::MaximumNumberOfThreads();
    qDebug() << "\tNumber of allowed Threads:          " << egoa::Auxiliary::NumberOfThreads();
#endif // NDEBUG



// Read graph file
    egoa::PowerGrid<TGraph> network;
    std::string filename = egoa::Auxiliary::Basename( inputFile.toStdString() );
                filename = egoa::Auxiliary::RemoveExtension( filename );

    if (!egoa::PowerGridIO<TGraph>::read ( network, inputFile.toStdString(), egoa::PowerGridIO<TGraph>::readIeeeCdfMatlab ))
        std::cerr << "Expected file " << inputFile.toStdString() << " does not exist!";

// Output network
    if (verbose) {
        std::cout << network << std::endl;

        std::cout   << std::string(40, '-')
                    << std::endl
                    << "\tAlgorithm: " << algorithm.toStdString() << std::endl
                    << "\tVariant: "   << variant.toStdString()   << std::endl
                    << std::endl;
    }

    network.OutputGeneratorSnaps();
    network.OutputLoadSnaps();

// Decide which algorithm to use
    using TNetwork = egoa::PowerGrid<TGraph>;
    TNetwork resultGraph  = network;
    try {
        // std::unique_ptr<egoa::DCPF<TNetwork>> model;
        // if ( algorithm == "DCPF" ) {
            // model = std::make_unique<egoa::DCPF<TNetwork>>( network, filename, timeLimit, false, traceSolution );
            // model->Run();
        // } else if ( algorithm == "DCMPF" ) {
            // model = std::make_unique<egoa::DCMPF<TNetwork>>( network, filename, timeLimit, false, traceSolution );
            // setNetworkSetting(network, networkSetting);
            // model->Run();
        // } else if ( algorithm == "DCMTSF" ) {
            // model = std::make_unique<egoa::DCMTSF<TNetwork>>( network, filename, timeLimit, false, traceSolution );
            // setNetworkSetting(network, networkSetting);

            // if      ( variant == "BIGM"      ) { model->SetKVl2BigM();      }
            // else if ( variant == "INDICATOR" ) { model->SetKVl2Indicator(); }
            // else if ( variant == "QUADRATIC" ) { model->SetKVl2Quadratic(); }
            // check variant here
            // model->Run();
        // } else
        if ( algorithm == "MAXST" || algorithm == "2APPROXIMATION" ) {
            auto comparator = [&network](egoa::Types::edgeId lhs, egoa::Types::edgeId rhs) {
                return network.Graph().EdgeAt(lhs).Properties().ThermalLimit()
                     > network.Graph().EdgeAt(rhs).Properties().ThermalLimit();
            };
            std::unique_ptr<egoa::MST<TGraph>> mst;
            if        ( variant == "KRUSKAL" ) {
                mst = std::make_unique<egoa::Kruskal<TGraph>>( network.Graph(), comparator );
            } else if ( variant == "PRIM"    ) {
                mst = std::make_unique<egoa::Prim<TGraph>>( network.Graph(), comparator ); }
            else {
                mst = std::make_unique<egoa::Kruskal<TGraph>>( network.Graph(), comparator );
            }
            mst->Run();
            auto result = mst->Result();
            SwitchEdges(network, result);
        } else if ( algorithm == "MINST" ) {
            auto comparator = [&network](egoa::Types::edgeId lhs, egoa::Types::edgeId rhs) {
                return network.Graph().EdgeAt(lhs).Properties().ThermalLimit()
                     < network.Graph().EdgeAt(rhs).Properties().ThermalLimit();
            };
            std::unique_ptr<egoa::MST<TGraph>> mst;
            if        ( variant == "KRUSKAL" ) {
                mst = std::make_unique<egoa::Kruskal<TGraph>>( network.Graph(), comparator );
            } else if ( variant == "PRIM"    ) {
                mst = std::make_unique<egoa::Prim<TGraph>>( network.Graph(), comparator ); }
            else {
                mst = std::make_unique<egoa::Kruskal<TGraph>>( network.Graph(), comparator );
            }
            mst->Run();
            auto result = mst->Result();
            SwitchEdges(network, result);
        } else {
            //code
        }

        // if ( verbose && model != nullptr ) {
        //     std::cout   << "Finished "
        //                 << algorithm.toStdString()
        //                 << " with status "
        //                 << model->Solver().Status()
        //                 << std::endl;
        //     std::cout   << *model;
        //     std::cout   << std::endl << std::endl;
        // }
    // } catch (GRBException e) {
        // printGurobiException(e);
    } catch(...) {
        std::cerr << "Unexpected exception during optimization" << std::endl;
    }

    // Write out original graph and result graph
    std::string algoFile = filename + "-" + variant.toLower().toStdString() + "-" + algorithm.toLower().toStdString();
    std::string file     = filename;
    if ( outputType == "GML" ) {
        // qDebug() << "Output: " << outputType << "\n" << flush;
        egoa::PowerGridIO<TGraph>::write( network    , outputDir.toStdString() + file     + ".gml", egoa::PowerGridIO<TGraph>::WriteGraphGml );
        egoa::PowerGridIO<TGraph>::write( resultGraph, outputDir.toStdString() + algoFile + ".gml", egoa::PowerGridIO<TGraph>::WriteGraphGml );
    } else if ( outputType == "PDF" ) {
        // qDebug() << "Output: " << outputType << "\n" << flush;
        egoa::PowerGridIO<TGraph>::write( network, outputDir.toStdString() + file     + ".dot", egoa::PowerGridIO<TGraph>::WriteGraphDot );
        egoa::PowerGridIO<TGraph>::write( resultGraph, outputDir.toStdString() + algoFile + ".dot", egoa::PowerGridIO<TGraph>::WriteGraphDot );
        system( ("dot -Tps " + outputDir.toStdString() + file     + ".dot -o " + outputDir.toStdString() + file + ".pdf").c_str() );
        system( ("dot -Tps " + outputDir.toStdString() + algoFile + ".dot -o " + outputDir.toStdString() + algoFile + ".pdf").c_str() );
    } else if ( outputType == "SVG" ) {
        // qDebug() << "Output: " << outputType << "\n" << flush;
        egoa::PowerGridIO<TGraph>::write( network, outputDir.toStdString() + file     + ".dot", egoa::PowerGridIO<TGraph>::WriteGraphDot );
        egoa::PowerGridIO<TGraph>::write( resultGraph, outputDir.toStdString() + algoFile + ".dot", egoa::PowerGridIO<TGraph>::WriteGraphDot );
        system( ("dot -Tps " + outputDir.toStdString() + file     + ".dot -o " + outputDir.toStdString() + file + ".svg").c_str() );
        system( ("dot -Tps " + outputDir.toStdString() + algoFile + ".dot -o " + outputDir.toStdString() + algoFile + ".svg").c_str() );
    } else if ( outputType == "NONE" ) {
        // qDebug() << "Output: " << outputType << "\n" << flush;
    } else {
        // qDebug() << "Output: " << outputType << "\n" << flush;
        egoa::PowerGridIO<TGraph>::write( network, outputDir.toStdString() + file     + ".dot", egoa::PowerGridIO<TGraph>::WriteGraphDot );
        egoa::PowerGridIO<TGraph>::write( resultGraph, outputDir.toStdString() + algoFile + ".dot", egoa::PowerGridIO<TGraph>::WriteGraphDot );
        system( ("dot -Tps " + outputDir.toStdString() + file     + ".dot -o " + outputDir.toStdString() + file + ".ps").c_str() );
        system( ("dot -Tps " + outputDir.toStdString() + algoFile + ".dot -o " + outputDir.toStdString() + algoFile + ".ps").c_str() );
    }

    return EXIT_SUCCESS;
}
