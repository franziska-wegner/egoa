/*
 * PowerGridIO.hpp
 *
 *  Created on: Sep 07, 2018
 *      Author: Franziska Wegner
 *      
 * Check definitions under https://graphviz.gitlab.io/_pages/doc/info/output.html
 */

#ifndef EGOA__IO__POWER_GRID_IO_HPP
#define EGOA__IO__POWER_GRID_IO_HPP

#include <fstream>
#include <sstream>

#ifdef OGDF_AVAILABLE
    #include <ogdf/fileformats/GraphIO.h>
#endif // OGDF_AVAILABLE

#include "DataStructures/Graphs/PowerGrid.hpp"
#include "Parser/IeeeCdfMatlabParser.hpp"
#include "Parser/PyPsaParser.hpp"
#include "Writer/GeojsonWriter.hpp"

namespace egoa {

/**
 * @brief      Class for power grid io.
 *
 * @tparam     GraphType  The graph @f$\graph = (\vertices, \edges)@f$.
 */
template<typename GraphType>
class PowerGridIO {

    // Template type aliasing
    using TGraph            = GraphType;
    using TElectricalVertex = typename TGraph::TVertex;
    using TElectricalEdge   = typename TGraph::TEdge;

    public:

#pragma mark FUNCTION POINTER

        ///@name Reader function pointer
        ///@{
            using ReaderFunctionStreamBased = bool (*)( PowerGrid< GraphType> &
                                                      , std::istream & );
            using ReaderFunctionStringBased = bool (*)( PowerGrid< GraphType> &
                                                      , std::string const & );
            using ReaderFunctionStreamBasedPowerGridAndCandidateNetwork  
                                            = bool (*)( PowerGrid< GraphType> &
                                                      , GraphType &
                                                      , std::string const & );
        ///@}

        ///@name Writer function pointer
        ///@{
            using WriterFunctionStreamBased  = bool (*)( PowerGrid<GraphType> const &
                                                       , std::ostream & );
            using WriterFunctionStreamBasedtionStringBased 
                                             = bool (*)( PowerGrid<GraphType> const &
                                                       , std::string          const & );
        ///@}

        ///@name Vector of reader function pointers
        ///@{
            static std::vector<ReaderFunctionStreamBased>                             const streamReaders;
            static std::vector<ReaderFunctionStringBased>                             const fileReaders;
            static std::vector<ReaderFunctionStreamBasedPowerGridAndCandidateNetwork> const streamReadersPowerGridAndCandidateNetwork;
        ///@}

        ///@name Vector of writer function pointers
        ///@{
            static std::vector<WriterFunctionStreamBased>                const streamWriters;
            static std::vector<WriterFunctionStreamBasedtionStringBased> const fileWriters;
        ///@}

        ///@name General reader
        ///@{
#pragma mark GENERAL_READER

            /**
             * @brief      Function to read a power grid.
             *
             * @param      network       The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param      input_stream  The stream from which the data is read.
             *
             * @return     @p true if the reading was successful, @p false otherwise.
             */
            static 
            inline bool read ( PowerGrid<GraphType> & network
                             , std::istream         & input_stream ) 
            {
                for ( auto & reader : streamReaders ) 
                {
                    if ( reader ( network, input_stream ) ) 
                    {
                        return true;
                    } else {
                        input_stream.clear();
                        input_stream.seekg(0, std::ios::beg);
                    }
                }
                return false;
            }

            /**
             * @brief      Function to read a power grid.
             *
             * @param      network           The network @f$\network = ( \graph, \generators, \consumers, \capacity, \susceptance, \dots )@f$.
             * @param      candidateNetwork  The candidate network @f$\network @f$.
             * @param      filename          The filename from which the data is read.
             *
             * @return     @p true if the reading was successful, @p false otherwise.
             */
            static 
            inline bool read ( PowerGrid<GraphType> & network
                             , GraphType            & candidateNetwork
                             , std::string    const & filename ) 
            {
                for ( auto & reader : streamReadersPowerGridAndCandidateNetwork ) 
                {
                    if ( reader ( network, candidateNetwork, filename ) ) 
                    {
                        return true;
                    }
                }
                return false;
            }

            /**
             * @brief      Function to read a power grid.
             *
             * @param      network   The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param      filename  The filename from which the data is read.
             * @param[in]  reader    The reader, e.g., ReadPyPsa.
             *
             * @return     @p true if the reading was successful, @p false otherwise.
             */
            static 
            inline bool read ( PowerGrid<GraphType>    & network
                             , std::string       const & filename
                             , ReaderFunctionStreamBased reader = PowerGridIO<GraphType>::read ) 
            {
                std::ifstream input_stream( filename );
                return input_stream.good() && reader ( network, input_stream );
            }

            /**
             * @brief      Function to read a power grid.
             *
             * @param      network   The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param      filename  The filename from which we read the data.
             * @param[in]  reader            The reader, e.g., ReadPyPsa.
             *
             * @return     @p true if the reading was successful, @p false otherwise.
             */
            static 
            inline bool read ( PowerGrid<GraphType>    & network
                             , std::string       const & filename
                             , ReaderFunctionStringBased reader = PowerGridIO<GraphType>::read ) 
            {
                return reader ( network, filename );
            }

            /**
             * @brief      Function to read a power grid.
             *
             * @param      network           The network @f$\network = (
             *     \graph, \generators, \consumers, \capacity, \susceptance,
             *     \dots )@f$.
             * @param      candidateNetwork  The candidate network @f$\graph @f$.
             * @param      filename          The filename from which the data is read.
             * @param[in]  reader            The reader, e.g., ReadPyPsa.
             *
             * @return     @p true if the reading was successful, @p false otherwise.
             */
            static 
            inline bool read ( PowerGrid<GraphType>                                & network
                             , GraphType                                           & candidateNetwork
                             , std::string                                   const & filename
                             , ReaderFunctionStreamBasedPowerGridAndCandidateNetwork reader = PowerGridIO<GraphType>::read ) 
            {
                return reader ( network, candidateNetwork, filename );
            }
        ///@}

        ///@name General writer
        ///@{
#pragma mark GENERAL_WRITER

            /**
             * @brief      Function to write a power grid.
             *
             * @param      network   The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param      filename  The filename to which the data is written.
             * @param[in]  writer    The writer.
             *
             * @return     @p true if the writing was successful, @p false otherwise.
             */
            static 
            inline bool write ( PowerGrid<GraphType> const & network
                              , std::ostream               & outputStream
                              , WriterFunctionStreamBased    writer = PowerGridIO<GraphType>::write ) 
            {
                return writer ( network, outputStream );
            }

            /**
             * @brief      Function to write a power grid.
             *
             * @param      network   The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param      filename  The filename
             * @param[in]  writer    The writer, e.g., WriteGeoJson.
             *
             * @return     @p true if the writing was successful, @p false otherwise.
             */
            static 
            inline bool write ( PowerGrid<GraphType>             const & network
                              , std::string                      const & filename
                              , WriterFunctionStreamBasedtionStringBased writer = PowerGridIO<GraphType>::write ) 
            {
                return writer ( network, filename );
            }
        ///@}

        ///@name IEEE CDF MATLAB DATA
        ///@{
#pragma mark IEEE CDF MATLAB DATA
            /**
             * @brief      Reads an IEEE CDF Matlab file.
             *
             * @param      network       The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param      input_stream  The input stream to read data from,
             *     e.g., a file.
             *
             * @return     @p true if the reading was successful, @p false otherwise.
             */
            static
            inline bool readIeeeCdfMatlab ( PowerGrid<GraphType> & network
                                          , std::istream         & input_stream ) 
            {
                if ( !input_stream.good() ) return false;
                IeeeCdfMatlabParser<GraphType> parser(input_stream);
                return parser.read(network);
            }

            /**
             * @brief      Writes an IEEE CDF Matlab file.
             *
             * @param      network        The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param      output_stream  The output stream to write data to, e.g., a file.
             *
             * @return     @p true if the writing was successful, @p false otherwise.
             */
            static
            inline bool writeIeeeCdfMatlab ( PowerGrid<GraphType> const & network
                                           , std::ostream               & output_stream ) 
            {
                if (!output_stream.good()) return false;
                IeeeCdfMatlabParser<GraphType> parser(output_stream);
                return parser.write(network);
            }
        ///@}

        ///@name PYPSA DATA
        ///@{
#pragma mark PYPSA DATA
            /**
             * @brief      Reads a PyPsa file.
             *
             * @param      network   The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param      filename  The filename
             *
             * @return     @p true if the reading was successful, @p false otherwise.
             */
            static
            inline bool ReadPyPsa ( PowerGrid<GraphType>  & network
                                  , std::string     const & filename ) 
            {
                PyPsaParser<GraphType> parser(filename);
                return parser.read(network, filename);
            }

            /**
             * @brief      Reads a PyPsa file.
             *
             * @param      network           The network @f$\network = (
             *     \graph, \generators, \consumers, \capacity, \susceptance,
             *     \dots )@f$.
             * @param      candidateNetwork  The candidate network @f$\network @f$.
             * @param      filename          The filename
             *
             * @return     @p true if the reading was successful, @p false otherwise.
             */
            static
            inline bool ReadPyPsa ( PowerGrid<GraphType>  & network
                                  , GraphType             & candidateNetwork
                                  , std::string     const & filename ) 
            {
                PyPsaParser<GraphType> parser(filename);
                return parser.read(network, candidateNetwork, filename);
            }
        ///@}

        ///@name       GeoJson
        ///@details    For more information on GeoJson see <a
        ///    href="https://geojson.org">GeoJson</a> and <a
        ///    href="https://tools.ietf.org/html/rfc7946">RFC7946</a>.
        ///@{
#pragma mark GEOJSON

            /**
             * @brief      Write the network into a GeoJson format.
             *
             * @param      network   The network @f$\network = (
             *     \graph, \generators, \consumers, \capacity, \susceptance,
             *     \dots )@f$.
             * @param      filename  The file to which the data is written.
             *
             * @return     @p true if the reading was successful, @p false otherwise.
             */
            static
            inline bool WriteGeoJson ( PowerGrid<GraphType> const & network
                                     , std::string          const & filename )
            {
                IO::GeoJsonWriter<GraphType> writer;//
                return writer.write ( network, filename );
            }

            /**
             * @brief      Write the network into a GeoJson format.
             *
             * @param      network       The network @f$\network = (
             *     \graph, \generators, \consumers, \capacity, \susceptance,
             *     \dots )@f$.
             * @param      outputStream  The stream to which the data is written.
             *
             * @return     @p true if the reading was successful, @p false otherwise.
             */
            static
            inline bool WriteGeoJson ( PowerGrid<GraphType> const & network
                                     , std::ostream               & outputStream )
            {
                IO::GeoJsonWriter<GraphType> writer;//
                return writer.write ( network, outputStream );
            }
        ///@}
        
        ///@name       Graph modeling language (GML)
        ///@details    For more information on GML see <a
        ///    href="https://gephi.org/users/supported-graph-formats/gml-format/">GML</a>.
        ///@{
#pragma mark GRAPH_GML
            
            /**
             * @brief      Reads a graph from a gml file.
             *
             * @param      network       The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param      input_stream  The input stream to read data from, e.g., a file.
             *
             * @return     @true if the reading was successful, @false otherwise.
             */
            static
            inline bool ReadGraphGml ( PowerGrid<GraphType> & network
                                     , std::istream         & input_stream ) 
            {
                throw std::runtime_error("ReadGraphGml is not implemented yet");
            }

#ifndef OGDF_AVAILABLE

            /**
             * @brief      Writes a graph into a gml file.
             *
             * @param      network        The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param      output_stream  The output stream to write data to, e.g., a file.
             *
             * @return     @p true if the writing was successful, @p false otherwise. 
             */
            static
            inline bool WriteGraphGml ( PowerGrid<GraphType> const & network
                                      , std::ostream               & output_stream ) 
            {
                throw std::runtime_error("WriteGraphGml is not implemented yet");
            }

            /**
             * @brief      Writes a graph into a gml file.
             *
             * @param      network   The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param      filename  The filename to write the data.
             *
             * @return     @p true if the writing was successful, @p false otherwise. 
             */
            static
            inline bool WriteGraphGml ( PowerGrid<GraphType> const & network
                                      , std::string          const & filename ) 
            {
                throw std::runtime_error("WriteGraphGml is not implemented yet");
            }
        ///@}

#else // IF OGDF AVAILABLE
        
        /**
         * @brief      Writes a graph into a gml file using OGDF.
         *
         * @param      network   The network @f$\network = ( \graph,
         *     \generators, \consumers, \capacity, \susceptance, \dots )@f$.
         * @param      filename  The filename to write the data.
         *
         * @return     @p true if the writing was successful, @p false otherwise.
         */
        static
        inline bool WriteGraphGml ( PowerGrid<GraphType> const & network
                                  , std::string          const & filename ) 
        {
            ogdf::Graph graph;
            ogdf::GraphAttributes ga(   graph, 
                                        ogdf::GraphAttributes::nodeGraphics     |  
                                        ogdf::GraphAttributes::nodeLabel        | 
                                        ogdf::GraphAttributes::nodeWeight       | 
                                        ogdf::GraphAttributes::nodeId           |
                                        // ogdf::GraphAttributes::nodeStyle        | //does not work yet 
                                        ogdf::GraphAttributes::edgeGraphics     |
                                        ogdf::GraphAttributes::edgeStyle        |
                                        ogdf::GraphAttributes::edgeLabel        | 
                                        ogdf::GraphAttributes::edgeIntWeight    | 
                                        ogdf::GraphAttributes::edgeDoubleWeight |
                                        ogdf::GraphAttributes::nodeTemplate
                                    );
            PowerGrid2OgdfGraph(network, graph, ga );
            return WriteGml ( ga, filename );
        }

        /**
         * @brief      Writes a gml into a gml file using OGDF.
         *
         * @param      ga        The graph attributes.
         * @param      filename  The filename to write the data.
         *
         * @return     @p true if the writing was successful, @p false otherwise.
         */
        static 
        inline bool WriteGml ( ogdf::GraphAttributes const & ga
                             , std::string           const & filename ) 
        {
            return ogdf::GraphIO::write( ga, filename, ogdf::GraphIO::writeGML );
            // return ogdf::GraphIO::write( ga, filename, ogdf::GraphIO::writeGraphML );
        }

        /**
         * @brief      Convert an OGDF shape to a basic vertex type.
         *
         * @param      shape  The OGDF shape.
         * @param      type   The basic vertex type.
         */
        static 
        inline void Shape2VertexType ( ogdf::Shape       const & shape
                                     , Vertex::BasicVertexType & type  ) 
        {
            switch (shape) 
            {
                case ogdf::Shape::Ellipse:  type = Vertex::BasicVertexType::source;         break;
                case ogdf::Shape::Triangle: type = Vertex::BasicVertexType::sink;           break;
                case ogdf::Shape::Rect:     type = Vertex::BasicVertexType::intermediate;   break;
                default:                    type = Vertex::BasicVertexType::unknown;
            }
        }

        /**
         * @brief      Converts an OGDF shape to a basic vertex type.
         *
         * @param[in]  shape  The OGDF shape.
         * @param      type   The CDF bus type.
         */
        static 
        inline void Shape2VertexType ( ogdf::Shape          shape
                                     , Vertex::CdfBusType & type) 
        {
            switch (shape) 
            {
                case ogdf::Shape::Ellipse:      type = Vertex::CdfBusType::slack;   break;
                case ogdf::Shape::Triangle:     type = Vertex::CdfBusType::load;    break;
                case ogdf::Shape::RoundedRect:  type = Vertex::CdfBusType::mvar;    break;
                case ogdf::Shape::Octagon:      type = Vertex::CdfBusType::voltage; break;
                default:                        type = Vertex::CdfBusType::unknown;
            }
        }

        /**
         * @brief      Converts an OGDF shapes to an IEEE vertex type.
         *
         * @param      shape  The OGDF shape.
         * @param      type   The IEEE bus type.
         */
        static 
        inline void Shape2VertexType ( ogdf::Shape   const & shape
                                     , Vertex::IeeeBusType & type) 
        {
            switch (shape) 
            {
                case ogdf::Shape::Ellipse:      type = Vertex::IeeeBusType::slack;      break;
                case ogdf::Shape::Triangle:     type = Vertex::IeeeBusType::load;       break;
                case ogdf::Shape::RoundedRect:  type = Vertex::IeeeBusType::generator;  break;
                default:                        type = Vertex::IeeeBusType::unknown; 
            }
        }

        /**
         * @brief      Converts a basic vertex type to an OGDF shape.
         *
         * @param[in]  type   The basic vertex type.
         * @param      shape  The OGDF shape.
         */
        static 
        inline void VertexType2Shape ( Vertex::BasicVertexType type
                                     , ogdf::Shape           & shape ) 
        {
            switch (type) 
            {
                case Vertex::BasicVertexType::source:       shape = ogdf::Shape::Ellipse;   break;
                case Vertex::BasicVertexType::sink:         shape = ogdf::Shape::Triangle;  break;
                case Vertex::BasicVertexType::intermediate: shape = ogdf::Shape::Rect;      break;
                default:                                    shape = ogdf::Shape::Hexagon; 
            }
        }

        /**
         * @brief      Converts a CDF bus type to an OGDF shape.
         *
         * @param[in]  type   The CDF bus type.
         * @param      shape  The OGDF shape.
         */
        static 
        inline void VertexType2Shape ( Vertex::CdfBusType type
                                     , ogdf::Shape      & shape ) 
        {
            switch (type) 
            {
                case Vertex::CdfBusType::slack:         shape = ogdf::Shape::Ellipse;       break;
                case Vertex::CdfBusType::mvar:          shape = ogdf::Shape::RoundedRect;   break;
                case Vertex::CdfBusType::voltage:       shape = ogdf::Shape::Octagon;       break;
                case Vertex::CdfBusType::load:          shape = ogdf::Shape::Triangle;      break;
                default:                                shape = ogdf::Shape::Hexagon;
            }
        }

        /**
         * @brief      Converts a IEEE bus type to an OGDF shape.
         *
         * @param[in]  type   The IEEE bus type.
         * @param      shape  The OGDF shape.
         */
        static 
        inline void VertexType2Shape ( Vertex::IeeeBusType type
                                     , ogdf::Shape       & shape ) 
        {
            switch (type) 
            {
                case Vertex::IeeeBusType::generator:    shape = ogdf::Shape::RoundedRect;   break;
                case Vertex::IeeeBusType::slack:        shape = ogdf::Shape::Ellipse;       break;
                case Vertex::IeeeBusType::load:         shape = ogdf::Shape::Triangle;      break;
                default:                                shape = ogdf::Shape::Hexagon;
            }
        }

        /**
         * @brief      Converts a stroke to an OGDF stroke.
         *
         * @param      stroke  The stroke.
         *
         * @return     The OGDF stroke.
         */
        static 
        inline ogdf::StrokeType Stroke2OgdfStroke ( Stroke::Name const & stroke ) 
        {
            switch ( stroke ) 
            {
                case Stroke::Name::solid:          return ogdf::StrokeType::Solid;
                case Stroke::Name::dashed:         return ogdf::StrokeType::Dash;
                case Stroke::Name::dotted:         return ogdf::StrokeType::Dot;
                case Stroke::Name::dasheddotted:   return ogdf::StrokeType::Dashdot;
                case Stroke::Name::bold:           return ogdf::StrokeType::Solid;
                default:                           return ogdf::StrokeType::None;
            }
        }

#endif // not OGDF_AVAILABLE ?

        ///@name Graph DOT 
        ///@{
#pragma mark GRAPH_DOT 
            // see https://en.wikipedia.org/wiki/DOT_(graph_description_language)
            // see spec http://www.graphviz.org/doc/info/attrs.html#k:color
            
            /**
             * @brief      Writes a graph dot.
             *
             * @param      network       The network
             * @param      outputStream  The stream to write data to
             *
             * @return     @true if the writing was successful, @false otherwise.
             * 
             * @todo       Improve and put in its own file.
             */
            static 
            bool WriteGraphDot ( PowerGrid<GraphType> const & network
                               , std::ostream               & outputStream ) 
            {
                outputStream << "graph " << network.Graph().Name() << " {\n"; 
                
                outputStream << "rankdir=LR" << "\n";
                outputStream << "size=" << "\"" << "3,3" << "\"" << "\n";
                outputStream << "ratio=" << "\"" << "filled" << "\"" << "\n";
                
                // edge style
                outputStream << "edge[";
                outputStream << "size=" << "\"" << "3,3" << "\"" << "";
                outputStream << "]\n";

                // vertex style
                outputStream << "node[";
                outputStream << "size=" << "\"" << "3,3" << "\"" << "\n";
                outputStream << "]";

                // edges
                network.Graph().template for_all_edges<ExecutionPolicy::sequential>(
                    [&outputStream, network](TElectricalEdge edge){
                        outputStream << network.Graph().VertexAt(edge.Source()).Properties().Name() 
                                     << " -- " 
                                     << network.Graph().VertexAt(edge.Target()).Properties().Name(); 
                        Color  color;
                        Stroke::Name stroke;
                        Edges::ElectricalEdge2Color(  edge.Properties().Type(), color  );
                        Edges::ElectricalEdge2Stroke( edge.Properties().Type(), stroke );
                        outputStream << "[color=\""     << color.Hexadecimal()                      << "\", ";
                        outputStream << "fontcolor=\""  << color.Hexadecimal()                      << "\", ";
                        outputStream << "style=\""      << Stroke2DotStyle(stroke)                  << "\", ";
                        outputStream << "label=\""      << edge.Properties().ThermalLimit() * network.BaseMva()  << "\"];\n";
                    }
                );

                outputStream << "}";
                return true;
            }

            static 
            bool WriteGraphDot ( PowerGrid<GraphType> const & network
                               , std::string          const & filename ) 
            {
                std::ofstream outputStream(filename);
                outputStream << "graph " << network.Graph().Name() << " {\n"; 
                
                outputStream << "rankdir=LR" << "\n";
                outputStream << "size=" << "\"" << "3,3" << "\"" << "\n";
                outputStream << "ratio=" << "\"" << "filled" << "\"" << "\n";
                
                // edge style
                outputStream << "edge[";
                outputStream << "size=" << "\"" << "3,3" << "\"" << "";
                outputStream << "]\n";

                // vertex style
                outputStream << "node[";
                outputStream << "size=" << "\"" << "3,3" << "\"" << "\n";
                outputStream << "]";

                // edges
                network.Graph().template for_all_edges<ExecutionPolicy::sequential>(
                    [&outputStream, network](TElectricalEdge edge){
                        outputStream << network.Graph().VertexAt(edge.Source()).Properties().Name() 
                                     << " -- " 
                                     << network.Graph().VertexAt(edge.Target()).Properties().Name(); 
                        Color  color;
                        Stroke::Name stroke;
                        Edges::ElectricalEdge2Color(  edge.Properties().Type(), color  );
                        Edges::ElectricalEdge2Stroke( edge.Properties().Type(), stroke );
                        outputStream << "[color=\""     << color.Hexadecimal()                      << "\", ";
                        outputStream << "fontcolor=\""  << color.Hexadecimal()                      << "\", ";
                        outputStream << "style=\""      << Stroke2DotStyle(stroke)                  << "\", ";
                        outputStream << "label=\""      << edge.Properties().ThermalLimit() * network.BaseMva()  << "\"];\n";
                    }
                );

                outputStream << "}";
                return outputStream.good() && true;
            }

            /**
             * @brief      Convert a stroke into a dot style stroke.
             *
             * @param      stroke  The stroke.
             *
             * @return     The dot style stroke.
             */
            static 
            inline std::string Stroke2DotStyle ( Stroke::Name const & stroke )
            {
                switch ( stroke ) 
                {
                    case Stroke::Name::solid:          return "solid";
                    case Stroke::Name::dashed:         return "dashed";
                    case Stroke::Name::dotted:         return "dotted";
                    case Stroke::Name::dasheddotted:   return "tapered";
                    case Stroke::Name::bold:           return "bold";
                    default:                           return "invis";
                }
            }
        ///@}

    private:
        static char indentChar_;   /**< Character used for indentation. */
        static int  indentWidth_;  /**< Number of indent characters used for indentation. */
};

} // namespace egoa

#endif // EGOA__IO__POWER_GRID_IO_HPP
