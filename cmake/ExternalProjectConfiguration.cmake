# ExternalProjectConfiguration.cmake
# 
#   Created on: Jan 10, 2020
#       Author: Franziska Wegner
#       
# Download external project if necessary.
# 

include ( ExternalProject )
include ( FetchContent )
find_package ( Git )

message( STATUS "")
message( STATUS "Download of data sets:")

####################################################################
# PyPSA Europe #####################################################
####################################################################
file ( MAKE_DIRECTORY "${PROJECT_INCLUDE_DIR}/data/PowerGrids/PyPSA" )
file ( MAKE_DIRECTORY "${PROJECT_INCLUDE_DIR}/data/PowerGrids/PyPSA/pypsa-eur" )

if ( EGOA_DOWNLOAD_PYPSA_EUR )
    message( STATUS "${MY_SPACE}Download PyPSA Europe data from https://github.com/PyPSA/pypsa-eur.git into ${PROJECT_INCLUDE_DIR}/data/PowerGrids/PyPSA/pypsa-eur.")

    FetchContent_Declare ( pypsa-eur
        GIT_REPOSITORY  https://github.com/PyPSA/pypsa-eur.git
        # URL_HASH SHA512=a5c3ec3962fa91987d739cba62f3ed796dd6eec840416e382849a6f161cb0a1cf95ce01565ae7b181ed1fadd9859217d7727e0732293764e4c1ea3ea80ac8dd7
        SOURCE_DIR      "${PROJECT_INCLUDE_DIR}/data/PowerGrids/PyPSA/pypsa-eur"
        GIT_TAG         master
        GIT_SHALLOW     1
    )

    FetchContent_GetProperties ( pypsa-eur )
    if ( NOT pypsa-eur_POPULATED )
        FetchContent_MakeAvailable ( pypsa-eur )
    endif()
endif ( EGOA_DOWNLOAD_PYPSA_EUR )

####################################################################
# PyPSA ITI Collaboration ##########################################
####################################################################
file ( MAKE_DIRECTORY "${PROJECT_INCLUDE_DIR}/data/PowerGrids/PyPSA/pypsa-iti-collaboration" )

if ( EGOA_DOWNLOAD_PYPSA_ITI_COLLABORATION )
    message( STATUS "${MY_SPACE}Download PyPSA ITI Collaboration data from https://git.scc.kit.edu/FN/iti-collaboration.git into ${PROJECT_INCLUDE_DIR}/data/PowerGrids/PyPSA/pypsa-iti-collaboration.")

    FetchContent_Declare ( pypsa-iti-collaboration
        GIT_REPOSITORY  https://git.scc.kit.edu/FN/iti-collaboration.git
        # URL_HASH SHA512=797ffef850c44dac210332b5a6554d98dc8ea51d8511c9d3fecc3c2291a8eb6b5b0f5e24e4cfa5aed356bc7e120cdca3013061cac59155c11932e70b39d9bae1
        SOURCE_DIR      "${PROJECT_INCLUDE_DIR}/data/PowerGrids/PyPSA/pypsa-iti-collaboration"
        GIT_TAG         master
        GIT_SHALLOW     1
    )

    FetchContent_GetProperties ( pypsa-iti-collaboration )
    if ( NOT pypsa-iti-collaboration_POPULATED )
        FetchContent_MakeAvailable ( pypsa-iti-collaboration )
    endif()
endif ( EGOA_DOWNLOAD_PYPSA_ITI_COLLABORATION )

####################################################################
# SciGRID Power v0.1 ###############################################
####################################################################
set ( EGOA_DOWNLOAD_DIRECTORY_SCIGRID "${PROJECT_INCLUDE_DIR}/data/PowerGrids/SciGrid" )

if ( EGOA_DOWNLOAD_SCIGRID )
    message( STATUS "${MY_SPACE}Download SciGRID Power data (version 0.1) from \"https://www.power.scigrid.de/releases_archive/scigrid-0.1-data-only.zip\" into \"${EGOA_DOWNLOAD_DIRECTORY_SCIGRID}/scigrid-0.1-data-only/\".")
    file ( MAKE_DIRECTORY "${EGOA_DOWNLOAD_DIRECTORY_SCIGRID}/scigrid-0.1-data-only" )

    file ( DOWNLOAD 
        https://www.power.scigrid.de/releases_archive/scigrid-0.1-data-only.zip 
        "${EGOA_DOWNLOAD_DIRECTORY_SCIGRID}/scigrid-0.1-data-only.zip"
        # URL_HASH SHA512=56c8246eca1142dc9d9487ef1d1bd690af91c0e3716a56adc25c4a218bceb1be7f84cf5361acbaae354fe23cf44be6f479ae3d6026abd7dcb131b89ca5779f26
        # SHOW_PROGRESS
    )

    execute_process (
        COMMAND ${CMAKE_COMMAND} -E tar xzf ${EGOA_DOWNLOAD_DIRECTORY_SCIGRID}/scigrid-0.1-data-only.zip
        WORKING_DIRECTORY ${EGOA_DOWNLOAD_DIRECTORY_SCIGRID}/scigrid-0.1-data-only/
    )

    file ( REMOVE ${EGOA_DOWNLOAD_DIRECTORY_SCIGRID}/scigrid-0.1-data-only.zip )
endif ( EGOA_DOWNLOAD_SCIGRID )

####################################################################
# SciGRID Power v0.2 ###############################################
####################################################################

if ( EGOA_DOWNLOAD_SCIGRID )
    message( STATUS "${MY_SPACE}Download SciGRID Power data (version 0.2) from \"https://www.power.scigrid.de/releases_archive/scigrid-0.2-data-only.zip\" into \"${EGOA_DOWNLOAD_DIRECTORY_SCIGRID}/scigrid-0.2-data-only/\".")

    file ( DOWNLOAD 
        https://www.power.scigrid.de/releases_archive/scigrid-0.2-data-only.zip
        "${EGOA_DOWNLOAD_DIRECTORY_SCIGRID}/scigrid-0.2-data-only.zip"
        # URL_HASH SHA512=0f6473487cc224e86d73d764b2b9ad5b34fae3c7b9a2a8f3be70846631429f14ddde10fb0a06672955e2725794c1c32fe5fc5fc356219d371ab462ca98bc1d7c
        # SHOW_PROGRESS
    )

    execute_process (
        COMMAND ${CMAKE_COMMAND} -E tar xzf ${EGOA_DOWNLOAD_DIRECTORY_SCIGRID}/scigrid-0.2-data-only.zip
        WORKING_DIRECTORY ${EGOA_DOWNLOAD_DIRECTORY_SCIGRID}/
    )

    file ( REMOVE ${EGOA_DOWNLOAD_DIRECTORY_SCIGRID}/scigrid-0.2-data-only.zip )
endif ( EGOA_DOWNLOAD_SCIGRID )

####################################################################
# SciGRID Power Germany ############################################
####################################################################

if ( EGOA_DOWNLOAD_SCIGRID )
    message( STATUS "${MY_SPACE}Download SciGRID Power data (conference version) from \"https://www.power.scigrid.de/releases_archive/scigrid-conference-de-data-only.zip\" into \"${EGOA_DOWNLOAD_DIRECTORY_SCIGRID}/scigrid-conference-de-data-only/\".")

    file ( DOWNLOAD 
        https://www.power.scigrid.de/releases_archive/scigrid-conference-de-data-only.zip
        "${EGOA_DOWNLOAD_DIRECTORY_SCIGRID}/scigrid-conference-de-data-only.zip"
        # URL_HASH SHA512=a03a69d9f30fca08a7945e9d9acbf4e0da18b639df351024f11df1c4b2d57a15bbc8eb4419b20b97a9741c9641a0aa24c8a3c7b45816380787185e58771ca77f
        # SHOW_PROGRESS
    )

    execute_process (
        COMMAND ${CMAKE_COMMAND} -E tar xzf ${EGOA_DOWNLOAD_DIRECTORY_SCIGRID}/scigrid-conference-de-data-only.zip
        WORKING_DIRECTORY ${EGOA_DOWNLOAD_DIRECTORY_SCIGRID}/
    )

    file ( REMOVE ${EGOA_DOWNLOAD_DIRECTORY_SCIGRID}/scigrid-conference-de-data-only.zip )
endif ( EGOA_DOWNLOAD_SCIGRID )

####################################################################
# SciGRID Power Europe #############################################
####################################################################

if ( EGOA_DOWNLOAD_SCIGRID )
    message( STATUS "${MY_SPACE}Download SciGRID Power data (conference version) from \"https://www.power.scigrid.de/releases_archive/scigrid-conference-eu-data-only.zip\" into \"${EGOA_DOWNLOAD_DIRECTORY_SCIGRID}/scigrid-conference-eu-data-only/\".")

    file ( DOWNLOAD 
        https://www.power.scigrid.de/releases_archive/scigrid-conference-eu-data-only.zip
        "${EGOA_DOWNLOAD_DIRECTORY_SCIGRID}/scigrid-conference-eu-data-only.zip"
        # URL_HASH SHA512=b8590cf9c2cea1ef3a096d041a5918a8e9f919236aba898e205ba732dbbab7b0b388bfd521399cfa2460123e16f3b0c1528db5dc8d0da82c097b9f096001f697
        # SHOW_PROGRESS
    )

    execute_process (
        COMMAND ${CMAKE_COMMAND} -E tar xzf ${EGOA_DOWNLOAD_DIRECTORY_SCIGRID}/scigrid-conference-eu-data-only.zip
        WORKING_DIRECTORY ${EGOA_DOWNLOAD_DIRECTORY_SCIGRID}/
    )

    file ( REMOVE ${EGOA_DOWNLOAD_DIRECTORY_SCIGRID}/scigrid-conference-eu-data-only.zip )
endif ( EGOA_DOWNLOAD_SCIGRID )

####################################################################
# Generated Wind Farm Data from ITI 2017 ###########################
####################################################################

set ( EGOA_DOWNLOAD_DIRECTORY_WINDFARM "${PROJECT_INCLUDE_DIR}/data/Windfarms" )
file ( MAKE_DIRECTORY "${EGOA_DOWNLOAD_DIRECTORY_WINDFARM}/Networks" )

if ( EGOA_DOWNLOAD_WINDFARM )
    message( STATUS "${MY_SPACE}Download generated wind farm data (ITI 2017) from \"https://i11www.iti.kit.edu/_media/projects/windfarmcabling/windfarm-benchmarksets.zip\" into \"${EGOA_DOWNLOAD_DIRECTORY_WINDFARM}/Networks/2017-iti-windfarm-benchmarksets/\".")
    
    file ( DOWNLOAD 
        https://i11www.iti.kit.edu/_media/projects/windfarmcabling/windfarm-benchmarksets.zip
        "${EGOA_DOWNLOAD_DIRECTORY_WINDFARM}/Networks/windfarm-benchmarksets.zip"
        # URL_HASH SHA512=52eff0790e78e2718e81e4ee2e0fc965180900d236e05822501019c8148a249529f7194e616c28394960a3086911af361165073cdf24195c7e5f1d603e463112
        # SHOW_PROGRESS
    )

    execute_process (
        COMMAND ${CMAKE_COMMAND} -E tar xzf ${EGOA_DOWNLOAD_DIRECTORY_WINDFARM}/Networks/windfarm-benchmarksets.zip 
        COMMAND mv ${EGOA_DOWNLOAD_DIRECTORY_WINDFARM}/Networks/windfarm-benchmarksets ${EGOA_DOWNLOAD_DIRECTORY_WINDFARM}/Networks/2017-iti-windfarm-benchmarksets
        COMMAND rm -r ${EGOA_DOWNLOAD_DIRECTORY_WINDFARM}/Networks/windfarm-benchmarksets
        WORKING_DIRECTORY ${EGOA_DOWNLOAD_DIRECTORY_WINDFARM}/Networks/
    )

    file ( REMOVE ${EGOA_DOWNLOAD_DIRECTORY_WINDFARM}/Networks/windfarm-benchmarksets.zip )
endif ( EGOA_DOWNLOAD_WINDFARM )

message( STATUS "")
