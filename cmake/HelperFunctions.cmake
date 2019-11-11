# HelperFunctions.cmake
# 
#   Created on: Jan 30, 2019
#       Author: Franziska Wegner
#       
# A collection of function that help to reduce the cmake complexity.
# 

include_directories(${PROJECT_INCLUDE_DIR})

# Link Gurobi if available
function(add_gurobi_if_available varName)
    if(GUROBI_FOUND)
        target_link_libraries(${varName} ${GUROBI_LIBRARIES})
        message(STATUS "GUROBI LINK ${GUROBI_LIBRARIES}")
    endif()
endfunction()

# Link OGDF if available
function(add_ogdf_if_available varName)
    if(OGDF_FOUND)
        target_link_libraries(${varName} OGDF)
    endif()
endfunction()

# Link COIN if available
function(add_coin_if_available varName)
    if(COIN_FOUND)
        target_link_libraries(${varName} COIN)
    endif()
endfunction()

# Link OGDF and COIN if available
function(add_ogdf_coin_if_available varName)
    if(OGDF_FOUND AND COIN_FOUND)
        add_ogdf_if_available(${varName})
        add_coin_if_available(${varName})
    elseif(OGDF_FOUND)
        add_ogdf_if_available(${varName})
    elseif(COIN_FOUND)
        add_coin_if_available(${varName})
    endif()
endfunction()
