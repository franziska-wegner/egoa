/* 
 * Edge.hpp
 *
 *  Created on: May 3, 2019
 *      Author: Franziska Wegner
 */

#ifndef EGOA__IO__WRAPPER__EDGE_HPP
#define EGOA__IO__WRAPPER__EDGE_HPP

#include "Auxiliary/Types.hpp"

namespace egoa::io {

template<typename PropertiesType>
class Edge {
public:
    using TProperties = PropertiesType;

    Edge()
    : source_(Const::INFTY),
      target_(Const::INFTY),
      properties_() {
    }
    
    inline Types::vertexId   Source()                const { return source_; }
    inline Types::vertexId & Source()                      { return source_; }

    inline Types::vertexId   Target()                const { return target_; }
    inline Types::vertexId & Target()                      { return target_; }
    
    inline TProperties       & Properties()       { return properties_; }
    inline TProperties const & Properties() const { return properties_; }

private:
    Types::vertexId source_;                /**< Source bus */
    Types::vertexId target_;                /**< Target bus */
    TProperties properties_;
};

} // namespace egoa::io

#endif // EGOA__IO__WRAPPER__EDGE_HPP