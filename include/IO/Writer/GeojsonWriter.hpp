/*
 * GeojsonWriter.hpp
 *
 *  Created on: Nov 02, 2019
 *      Author: Franziska Wegner
 */

#ifndef EGOA__IO__GEOJSON_WRITER_HPP
#define EGOA__IO__GEOJSON_WRITER_HPP

#include "DataStructures/Networks/PowerGrid.hpp"

#include "DataStructures/Graphs/StaticGraph.hpp"

#include "DataStructures/Graphs/Vertices/ElectricalProperties.hpp"
#include "DataStructures/Graphs/Vertices/GeneratorProperties.hpp"
#include "DataStructures/Graphs/Vertices/LoadProperties.hpp"

#include "DataStructures/Graphs/Edges/ElectricalProperties.hpp"

#include <fstream>

namespace egoa::IO {

template<typename GraphType = StaticGraph< Vertices::ElectricalProperties<Vertices::IeeeBusType>
                                         , Edges::ElectricalProperties > >
class GeoJsonWriter final {

#pragma mark TEMPLATE_TYPE_ALIASING
    // Template type aliasing
    using TGraph                = GraphType;
    using TNetwork              = PowerGrid<GraphType>;
    // Vertices
    using TVertex               = typename TGraph::TVertex;
    using TVertexProperties     = typename TGraph::TVertexProperties;
    using TVertexType           = typename TVertexProperties::TVertexType;
    using TGeneratorProperties  = typename TNetwork::TGeneratorProperties;
    using TLoadProperties       = typename TNetwork::TLoadProperties;
    // Edges
    using TEdge                 = typename TGraph::TEdge;
    using TEdgeProperties       = typename TGraph::TEdgeProperties;

    // Bounds
    using TBound                = Bound<>;

    public:

        ///@name Constructors and destructor
        ///@{
#pragma mark CONSTRUCTORS_AND_DESTRUCTOR

            /**
             * @brief      Constructs a new instance.
             *
             * @param      filename  The filename.
             * @param[in]  indent    If @p true the file has a proper layout,
             *      otherwise its representation is compact.
             */
            explicit GeoJsonWriter ( Types::count indent   = 4
                                   , bool         readable = true )
            : indent_(indent)
            , readable_(readable)
            {}

            ~GeoJsonWriter(){}
        ///@}

        ///@name Write Graph
#pragma mark GRAPH WRITER

            /**
             * @brief      Writes a graph.
             *
             * @param      os     The output stream.
             * @param      graph  The graph.
             *
             * @return     @p true if the writing was successful, @p false otherwise.
             */
            inline bool WriteGraph  ( std::ostream & os
                                    , TGraph const & graph )
            {
                WriteHeader ( os );
                WriteFeatureCollection ( os );
                WriteFeaturesBegin ( os );
                WriteVertices ( os, graph, false);
                WriteLines ( os, graph, true );
                WriteFeaturesEnd ( os, true );
                WriteFooter ( os );
                return true; // How do you declare success
            }
        ///@}

private:
        ///@name Auxiliary
        ///@{
#pragma mark AUXILIARY

            /**
             * @brief      Add indent to the output stream.
             *
             * @param      os      The output stream.
             * @param[in]  depth   The indent number.
             */
            inline void Indent ( std::ostream & os
                               , Types::count   depth = 1 )
            {
                if ( Readable() )
                {
                    Types::string indent( static_cast<std::string::size_type>( depth * indent_ ), ' ' );
                    os << indent;
                }
            }

            /**
             * @brief      Add new line to the output stream.
             *
             * @param      os    The output stream.
             */
            inline void NewLine ( std::ostream & os)
            {
                if ( Readable() )
                {
                    os << std::endl;
                }
            }

            /**
             * @brief      Write a readable GeoJson.
             *
             * @return     @true if the GeoJson will have indents and
             *     newlines, @false compact representation without any indents
             *     and newlines.
             */
            inline bool Readable ()
            {
                return readable_;
            }
        ///@}

        ///@name Writer Methods
        ///@{
#pragma mark WRITER METHODS

            /**
             * @brief      Writes a header.
             *
             * @param      os    The output stream.
             */
            inline void WriteHeader ( std::ostream & os )
            {
                os << "{";
                NewLine(os);
            }

            /**
             * @brief      Writes a footer.
             *
             * @param      os      The operating system
             * @param[in]  indent  The indent
             */
            inline void WriteFooter ( std::ostream & os
                                    , Types::count   indent = 0 )
            {
                Indent( os, indent );
                os  << "}";
                NewLine(os);
            }

            /**
             * @brief      Writes a feature begin.
             *
             * @param      os      The output stream.
             * @param[in]  indent  The indent.
             */
            inline void WriteFeatureBegin ( std::ostream & os
                                          , Types::count   indent = 1 )
            {
                Indent( os, indent );
                os  << "{";
                NewLine(os);

                Indent( os, indent + 1 );
                os  << "\"type\": \"Feature\",";
                NewLine(os);
            }

            /**
             * @brief      Writes a feature end.
             *
             * @param      os      The output stream.
             * @param[in]  last    The last.
             * @param[in]  indent  The indent.
             */
            inline void WriteFeatureEnd ( std::ostream & os
                                        , bool           last   = false
                                        , Types::count   indent = 1 )
            {
                char comma = last?' ':',';
                Indent( os, indent );
                os  << "}"
                    << comma;
                NewLine(os);
            }

            /**
             * @brief      Writes a properties begin.
             *
             * @param      os      The output stream.
             * @param[in]  indent  The indent.
             */
            inline void WritePropertiesBegin ( std::ostream & os
                                             , Types::count   indent = 2 )
            {
                Indent( os, indent );
                os  << "\"properties\":"
                    << "{";
                NewLine(os);
            }

            /**
             * @brief      Writes vertex properties.
             *
             * @param      os              The output stream.
             * @param      vertexProperty  The vertex property.
             * @param[in]  indent          The indent.
             */
            inline void WriteVertexProperties ( std::ostream            & os
                                              , TVertexProperties const & vertexProperty
                                              , Types::count              indent         = 2 )
            {
                bool last = false;
                /* Basic Property Members */
                PropertyTemplate<Types::name> ( os, "name", vertexProperty.Name(), last, indent );
                PropertyTemplate<TVertexType> ( os, "type", vertexProperty.Type(), last, indent );
                PropertyTemplate<Types::real> ( os, "xCoordinate", vertexProperty.X(), last, indent );
                PropertyTemplate<Types::real> ( os, "yCoordinate", vertexProperty.Y(), last, indent );

                /* Admittance Related Members */
                PropertyTemplate<Types::real> ( os, "shuntConductance", vertexProperty.ShuntConductance(), last, indent );
                PropertyTemplate<Types::real> ( os, "shuntSusceptance", vertexProperty.ShuntSusceptance(), last, indent );

                /* Voltage Related Members */
                PropertyTemplate<Types::real> ( os, "voltageMagnitude", vertexProperty.VoltageMagnitude(), last, indent );
                PropertyTemplate<Types::real> ( os, "voltageAngle", vertexProperty.VoltageAngle(), last, indent );
                PropertyTemplate<Types::real> ( os, "nominalVoltage", vertexProperty.NominalVoltage(), last, indent );
                PropertyTemplate<Types::real> ( os, "maximumVoltage", vertexProperty.MaximumVoltage(), last, indent );
                PropertyTemplate<Types::real> ( os, "minimumVoltage", vertexProperty.MinimumVoltage(), last, indent );

                /* Location Specific Members */
                PropertyTemplate<Types::name> ( os, "country", vertexProperty.Country(), last, indent );
                PropertyTemplate<Types::index> ( os, "area", vertexProperty.Area(), last, indent );
                PropertyTemplate<Types::index> ( os, "zone", vertexProperty.Zone(), last, indent );
                PropertyTemplate<Vertices::ControlType> ( os, "control", vertexProperty.Control(), last, indent );
                PropertyTemplate<Vertices::EnergyCarrier> ( os, "carrier", vertexProperty.Carrier(), last, indent );

                /* Status Members */
                last = true;
                PropertyTemplate<Vertices::BusStatus> ( os, "status", vertexProperty.Status(), last, indent );
            }

            /**
             * @brief      Writes edge properties.
             *
             * @param      os            The output stream.
             * @param      edgeProperty  The edge property.
             * @param[in]  indent        The indent.
             */
            inline void WriteEdgeProperties ( std::ostream          & os
                                            , TEdgeProperties const & edgeProperty
                                            , Types::count            indent         = 2 )
            {
                bool last = false;
                /* Basic Property Members */
                PropertyTemplate<Types::name> ( os, "name", edgeProperty.Name(), last, indent );
                PropertyTemplate<bool> ( os, "status", edgeProperty.Status(), last, indent );
                PropertyTemplate<Edges::ElectricalEdgeType> ( os, "type", edgeProperty.Type(), last, indent );
                PropertyTemplate<Types::real> ( os, "minimumThetaBound", edgeProperty.ThetaBound().Minimum() / Const::PI * 180, last, indent );
                PropertyTemplate<Types::real> ( os, "maximumThetaBound", edgeProperty.ThetaBound().Maximum() / Const::PI * 180, last, indent );

                /* Branch impedance */
                PropertyTemplate<Types::real> ( os, "resistance", edgeProperty.Resistance(), last, indent );
                PropertyTemplate<Types::real> ( os, "reactance", edgeProperty.Reactance(), last, indent );

                /* Voltage Related Members */
                PropertyTemplate<Types::real> ( os, "conductance", edgeProperty.template Conductance<Edges::CarrierDifferentiationType::DC>(), last, indent );
                PropertyTemplate<Types::real> ( os, "susceptance", edgeProperty.template Susceptance<Edges::CarrierDifferentiationType::DC>(), last, indent );
                PropertyTemplate<Types::real> ( os, "charge", edgeProperty.Charge(), last, indent );

                /* Line MVA ratings */
                PropertyTemplate<Types::real> ( os, "thermalLimitA", edgeProperty.ThermalLimit(), last, indent );
                PropertyTemplate<Types::real> ( os, "thermalLimitB", edgeProperty.ThermalLimitB(), last, indent );
                PropertyTemplate<Types::real> ( os, "thermalLimitC", edgeProperty.ThermalLimitC(), last, indent );

                /* Location Specific Members */
                PropertyTemplate<Types::real> ( os, "tapRatio", edgeProperty.TapRatio(), last, indent );
                PropertyTemplate<Types::real> ( os, "angleShift", edgeProperty.AngleShift(), last, indent );

                /* Location Specific Members */
                PropertyTemplate<Types::real> ( os, "capitalCost", edgeProperty.CapitalCost(), last, indent );
                PropertyTemplate<Types::real> ( os, "length", edgeProperty.Length(), last, indent );
                PropertyTemplate<Types::count> ( os, "numberOfParallelLines", edgeProperty.NumberOfParallelLines(), last, indent );
                PropertyTemplate<Types::real> ( os, "nominalApparentPower", edgeProperty.NominalApparentPower(), last, indent );
                PropertyTemplate<Types::real> ( os, "nominalVoltage", edgeProperty.NominalVoltage(), last, indent );
                PropertyTemplate<Types::real> ( os, "minimumNominalApparentPowerBound", edgeProperty.NominalApparentPowerBound().Minimum(), last, indent );
                PropertyTemplate<Types::real> ( os, "maximumNominalApparentPowerBound", edgeProperty.NominalApparentPowerBound().Maximum(), last, indent );
                PropertyTemplate<bool> ( os, "nominalApparentPowerExtendable", edgeProperty.NominalApparentPowerExtendable(), last, indent );
                last = true;
                PropertyTemplate<Types::real> ( os, "terrainFactor", edgeProperty.TerrainFactor(), last, indent );
            }

            /**
             * @brief      Standard JSON key : value pair template.
             *
             * @pre        The right hand-side object has to support the
             *     output stream operator.
             *
             * @param      os      The output stream.
             * @param[in]  lhs     The left hand side.
             * @param      rhs     The right hand side.
             * @param[in]  last    The last.
             * @param[in]  indent  The indent.
             *
             * @tparam     T       Type of the right hand-side.
             */
            template<typename T>
            inline void PropertyTemplate ( std::ostream & os
                                         , std::string    lhs
                                         , T      const & rhs
                                         , bool           last   = false
                                         , Types::count   indent = 2)
            {
                std::string comma = last?" ":",";
                Indent( os, indent );
                os  << "\""
                    << lhs
                    << "\": "
                    << "\""
                    << rhs
                    << "\""
                    << comma;
                NewLine(os);
            }

            /**
             * @brief      Writes a properties end.
             *
             * @param      os      The output stream.
             * @param[in]  last    The last.
             * @param[in]  indent  The indent.
             */
            inline void WritePropertiesEnd  ( std::ostream & os
                                            , bool           last   = false
                                            , Types::count   indent = 2 )
            {
                std::string comma = last?" ":",";

                Indent( os, indent );
                os  << "}"
                    << comma;
                NewLine(os);
            }

            /**
             * @brief      Writes a feature collection.
             *
             * @param      os    The output stream.
             */
            inline void WriteFeatureCollection ( std::ostream & os )
            {
                os  << "\"type\": \"FeatureCollection\",";
                NewLine(os);
            }

            /**
             * @brief      Writes a features begin.
             *
             * @param      os    The output stream.
             */
            inline void WriteFeaturesBegin ( std::ostream & os )
            {
                os  << "\"features\": [";
                NewLine(os);
            }

            /**
             * @brief      Writes a features end.
             *
             * @param      os      The output stream.
             * @param[in]  last    The last.
             * @param[in]  indent  The indent.
             */
            inline void WriteFeaturesEnd ( std::ostream & os
                                         , bool           last   = false
                                         , Types::count   indent = 0 )
            {
                char comma = last?' ':',';
                Indent( os, indent );
                os  << "]"
                    << comma;
                NewLine(os);
            }

            /**
             * @brief      Writes a geometry.
             *
             * @param      os      The output stream.
             * @param[in]  indent  The indent.
             */
            inline void WriteGeometry ( std::ostream & os
                                      , Types::count   indent = 2 )
            {
                Indent( os, indent );
                os  << "\"geometry\": ";
            }
        ///@}

        ///@name Point Writer
        ///@{
#pragma mark POINT WRITER

            /**
             * @brief      Writes points.
             *
             * @param      os      The output stream.
             * @param      graph   The graph.
             * @param[in]  last    The last.
             * @param[in]  indent  The indent.
             */
            inline void WriteVertices ( std::ostream & os
                                      , TGraph const & graph
                                      , bool           last   = false
                                      , Types::count   indent = 1 )
            {
                graph.for_all_vertices( [this, &os, &last, &indent]( TVertex const & vertex ){
                    WriteFeatureBegin ( os, indent );
                    WritePropertiesBegin ( os, indent + 1 );
                    WriteVertexProperties ( os, vertex.Properties(), indent + 2 );
                    WritePropertiesEnd ( os, false, indent + 1 );
                    WritePoint ( os, vertex, indent + 1 );
                    WriteFeatureEnd ( os, last, indent );
                });
            }

            /**
             * @brief      Writes points.
             *
             * @param      os      The output stream.
             * @param      graph   The graph.
             * @param[in]  last    The last.
             * @param[in]  indent  The indent.
             */
            inline void WriteGenerators ( std::ostream   & os
                                        , TNetwork const & network
                                        , bool           last   = false
                                        , Types::count   indent = 1 )
            {
                // network.for_all_generators( [this, &os, &last, &indent]( TGeneratorProperties const & generatorProperty ){
                //     WriteFeatureBegin ( os, indent );
                //     WritePropertiesBegin ( os, indent + 1 );
                //     WriteVertexProperties ( os, vertex.Properties(), indent + 2 );
                //     WritePropertiesEnd ( os, false, indent + 1 );
                //     WritePoint ( os, vertex, indent + 1 );
                //     WriteFeatureEnd ( os, last, indent );
                // });
            }

            /**
             * @brief      Writes a GeoJson point.
             *
             * @param      os           The output stream.
             * @param[in]  xCoordinate  The coordinate.
             * @param[in]  yCoordinate  The y coordinate.
             */
            inline void WritePoint  ( std::ostream & os
                                    , Types::real    xCoordinate
                                    , Types::real    yCoordinate
                                    , Types::count   indent      = 2 )
            {
                WriteGeometry ( os, indent );
                os  << "{";
                NewLine(os);

                Indent( os, indent + 1 );
                os  << "\"type\": \"Point\",";
                NewLine(os);

                Indent( os, indent + 1 );
                os  << "\"coordinates\": ";
                WritePointCoordinate ( os, xCoordinate, yCoordinate, 0 );
                NewLine(os);
                Indent( os, indent );
                os  << "}";
                NewLine(os);
            }

            /**
             * @brief      Writes a GeoJson point.
             *
             * @param      os        The output stream.
             * @param      graph     The graph.
             * @param[in]  vertexId  The vertex identifier.
             */
            inline void WritePoint ( std::ostream  & os
                                   , TGraph  const & graph
                                   , Types::vertexId vertexId
                                   , Types::count   indent      = 2 )
            {
                WritePoint  ( os
                            , graph.VertexAt(vertexId).X()
                            , graph.VertexAt(vertexId).Y()
                            , indent );
            }

            /**
             * @brief      Writes a GeoJson point.
             *
             * @param      os      The output stream.
             * @param      vertex  The vertex.
             */
            inline void WritePoint  ( std::ostream  & os
                                    , TVertex const & vertex
                                    , Types::count   indent      = 2 )
            {
                WritePoint  ( os
                            , vertex.Properties().X()
                            , vertex.Properties().Y()
                            , indent );
            }

            /**
             * @brief      Writes a point coordinate.
             *
             * @param      os           The output stream.
             * @param[in]  xCoordinate  The coordinate
             * @param[in]  yCoordinate  The y coordinate
             */
            inline void WritePointCoordinate ( std::ostream & os
                                             , Types::real    xCoordinate
                                             , Types::real    yCoordinate
                                             , Types::count   indent      = 2 )
            {
                Indent ( os, indent );
                os  << "["
                    << xCoordinate
                    << ","
                    << yCoordinate
                    << "]"
                    ;
            }

            /**
             * @brief      Writes a point coordinate.
             *
             * @param      os        The output stream.
             * @param      graph     The graph
             * @param[in]  vertexId  The vertex identifier
             */
            inline void WritePointCoordinate ( std::ostream  & os
                                             , TGraph  const & graph
                                             , Types::vertexId vertexId )
            {
                WritePointCoordinate ( os
                                     , graph.VertexAt(vertexId).X()
                                     , graph.VertexAt(vertexId).Y() );
            }

            /**
             * @brief      Writes a point coordinate.
             *
             * @param      os      The output stream.
             * @param      vertex  The vertex
             */
            inline void WritePointCoordinate ( std::ostream  & os
                                             , TVertex const & vertex )
            {
                WritePointCoordinate ( os
                                     , vertex.X()
                                     , vertex.Y() );
            }
        ///@}

        ///@name Line Writer
        ///@{
#pragma mark LINE WRITER

            /**
             * @brief      Writes lines.
             *
             * @param      os      The output stream.
             * @param      graph   The graph.
             * @param[in]  last    The last.
             * @param[in]  indent  The indent.
             */
            inline void WriteLines ( std::ostream & os
                                   , TGraph const & graph
                                   , bool           last   = false
                                   , Types::count   indent = 2 )
            {
                Types::count edgeCounter = 0;
                graph.for_all_edges ( [this, &os, &graph, &last, &indent, &edgeCounter] (TEdge const & edge) {
                    WriteFeatureBegin ( os );
                    WritePropertiesBegin ( os );
                    WriteEdgeProperties ( os, edge.Properties(), indent + 2 );
                    WritePropertiesEnd ( os );
                    Types::vertexId source  = edge.Source();
                    Types::vertexId target  = edge.Target();
                    WriteLinesGeometryObject ( os, graph.VertexAt(source), graph.VertexAt(target), indent );
                    ( edgeCounter + 1 < graph.NumberOfEdges() )?last=false:last=true;
                    WriteFeatureEnd ( os, last );
                    ++edgeCounter;
                });
                // os << "," << std::endl;
            }

            /**
             * @brief      Writes a lines geometry object.
             *
             * @param      os      The output stream.
             * @param      graph   The graph.
             * @param[in]  indent  The indent.
             */
            inline void WriteLinesGeometryObject  ( std::ostream  & os
                                                  , TVertex const & sourceVertex
                                                  , TVertex const & targetVertex
                                                  , Types::count    indent       = 2 )
            {
                WriteGeometry ( os, indent );
                WriteLineHeader ( os, indent + 1 );
                WriteLineContent ( os, sourceVertex, targetVertex, indent + 2 );
                WriteLineFooter ( os, indent );
            }

            /**
             * @brief      Writes a line header.
             *
             * @param      os      The output stream.
             * @param[in]  indent  The indent.
             */
            inline void WriteLineHeader ( std::ostream & os
                                        , Types::count   indent = 3 )
            {
                os  << "{";
                NewLine(os);
                Indent( os, indent );
                os  << "\"type\": \"LineString\",";
                NewLine(os);
                Indent( os, indent );
                os  << "\"coordinates\": [";
                NewLine(os);
            }

            /**
             * @brief      Writes a line content.
             *
             * @param      os      The output stream.
             * @param      graph   The graph.
             * @param[in]  indent  The indent.
             */
            inline void WriteLineContent ( std::ostream  & os
                                         , TVertex const & sourceVertex
                                         , TVertex const & targetVertex
                                         , Types::count          indent = 4 )
            {
                Indent( os, indent );
                WritePointCoordinate ( os
                                     , sourceVertex.Properties().X()
                                     , sourceVertex.Properties().Y() );
                os << ',';
                NewLine(os);
                Indent( os, indent );
                WritePointCoordinate ( os
                                     , targetVertex.Properties().X()
                                     , targetVertex.Properties().Y() );
                NewLine(os);
            }

            /**
             * @brief      Writes a line footer.
             *
             * @param      os      The output stream.
             * @param[in]  indent  The indent.
             */
            inline void WriteLineFooter ( std::ostream & os
                                        , Types::count   indent = 2 )
            {
                Indent( os, indent + 1 );
                os  << "]";
                NewLine(os);
                Indent( os, indent );
                os  << "}";
                NewLine(os);
            }
        ///@}

    public:
        ///@name Writer
#pragma mark WRITER
            /**
             * @brief      Write GeoJSON using the filename.
             *
             * @param      network   The network.
             * @param      filename  The filename.
             *
             * @return     @p true if the writing was successful, @p false otherwise.
             */
            bool write  ( TNetwork    const & network
                        , std::string const & filename )
            {
                std::ofstream file;
                file.open(filename, std::ofstream::trunc);
                if (!file.is_open()) return false;

                // file is empty
                file.seekp(0, std::ios::end);
                return WriteGraph ( file, network.Graph() );
            }

            /**
             * @brief      Write GeoJSON using the output stream.
             *
             * @param      network       The network.
             * @param      OutputStream  The output stream to write data.
             *
             * @return     @p true if the writing was successful, @p false otherwise.
             */
            bool write  ( TNetwork const & network
                        , std::ostream  & outputStream )
            {
                return WriteGraph ( outputStream, network.Graph() );
            }
        ///@}

    private:
        Types::count const  indent_;
        bool                readable_;
};

} // namespace egoa::IO

#endif // EGOA__IO__GEOJSON_WRITER_HPP
