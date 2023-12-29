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
# CppAD ############################################################
####################################################################
#
# Website: https://github.com/coin-or/CppAD.git
#          and https://coin-or.github.io/CppAD/doc/cppad.htm
####################################################################

if ( EGOA_DOWNLOAD_CPPAD )
    message( STATUS "${MY_SPACE}Download CppAD from https://github.com/coin-or/CppAD into ${PROJECT_INCLUDE_DIR}/external/CppAD.")
    file ( MAKE_DIRECTORY "${PROJECT_INCLUDE_DIR}/external/CppAD" )

    ExternalProject_Add ( CppAD
        GIT_REPOSITORY  https://github.com/coin-or/CppAD
        SOURCE_DIR      "${PROJECT_INCLUDE_DIR}/external/CppAD"
        GIT_TAG         master
        GIT_SHALLOW     1
    )
endif ( EGOA_DOWNLOAD_CPPAD )

####################################################################
# Eigen ############################################################
####################################################################
#
# Website: https://gitlab.com/libeigen/eigen.git
#          and http://eigen.tuxfamily.org/index.php
####################################################################

if ( EGOA_DOWNLOAD_EIGEN )
    message( STATUS "${MY_SPACE}Download Eigen from https://gitlab.com/libeigen/eigen.git into ${PROJECT_INCLUDE_DIR}/external/Eigen.")
    file ( MAKE_DIRECTORY "${PROJECT_INCLUDE_DIR}/external/Eigen" )

    FetchContent_Declare ( Eigen
        GIT_REPOSITORY  https://gitlab.com/libeigen/eigen.git
        SOURCE_DIR      "${PROJECT_INCLUDE_DIR}/external/Eigen"
        GIT_TAG         master
        GIT_SHALLOW     1
    )

    if ( ${CMAKE_VERSION} VERSION_LESS 3.14 )
        FetchContent_GetProperties ( Eigen )
        if ( NOT Eigen_POPULATED )
            FetchContent_Populate ( Eigen )
            # add_subdirectory ( ${Eigen_SOURCE_DIR} ${Eigen_BINARY_DIR} )
        endif()
    else()
        FetchContent_MakeAvailable ( Eigen )
    endif()

endif ( EGOA_DOWNLOAD_EIGEN )

####################################################################
# Google Test Framework ############################################
####################################################################
#
# Website: https://github.com/google/googletest
####################################################################

if ( EGOA_DOWNLOAD_GOOGLE_TEST_FRAMEWORK )
    message( STATUS "${MY_SPACE}Download Google-Testing Framework from https://github.com/google/googletest.git into ${PROJECT_INCLUDE_DIR}/external/GoogleTestFramework.")
    file ( MAKE_DIRECTORY "${PROJECT_INCLUDE_DIR}/external/GoogleTestFramework" )

    ExternalProject_Add ( GoogleTestFramework
        GIT_REPOSITORY  https://github.com/google/googletest.git
        SOURCE_DIR      "${PROJECT_INCLUDE_DIR}/external/GoogleTestFramework"
        GIT_TAG         main
        GIT_SHALLOW     1
    )
endif ( EGOA_DOWNLOAD_GOOGLE_TEST_FRAMEWORK )

####################################################################
# PyPSA Europe #####################################################
####################################################################
# Publication:
#
# PyPSA-Eur: An Open Optimisation Model of the European Transmission
#            System
#
# 2018
# Website: https://doi.org/10.5281/zenodo.3520875
#          and https://github.com/PyPSA/pypsa-eur
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
# Publication:
#
# PyPSA-Eur: An Open Optimisation Model of the European Transmission
#            System
#
# 2018
# Website: https://doi.org/10.5281/zenodo.3520875
#          and https://git.scc.kit.edu/FN/iti-collaboration
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
# Publication:
#
# SciGRID - An Open Source Reference Model for the European
#           Transmission Network (v0.2)
#
# 2016
# Website: http://www.scigrid.de
####################################################################

set ( EGOA_DOWNLOAD_DIRECTORY_SCIGRID "${PROJECT_INCLUDE_DIR}/data/PowerGrids/SciGrid" )

if ( EGOA_DOWNLOAD_SCIGRID AND NOT EXISTS "${EGOA_DOWNLOAD_DIRECTORY_SCIGRID}/scigrid-0.1-data-only" )
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
endif ()

####################################################################
# SciGRID Power v0.2 ###############################################
####################################################################
# Publication:
#
# SciGRID - An Open Source Reference Model for the European
#           Transmission Network (v0.2)
#
# 2016
# Website: http://www.scigrid.de
####################################################################

if ( EGOA_DOWNLOAD_SCIGRID AND NOT EXISTS "${EGOA_DOWNLOAD_DIRECTORY_SCIGRID}/scigrid-0.2-data-only" )
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
endif ()

####################################################################
# SciGRID Power Germany ############################################
####################################################################
# Publication:
#
# SciGRID - An Open Source Reference Model for the European
#           Transmission Network (v0.2)
#
# 2016
# Website: http://www.scigrid.de
####################################################################

if ( EGOA_DOWNLOAD_SCIGRID AND NOT EXISTS "${EGOA_DOWNLOAD_DIRECTORY_SCIGRID}/scigrid-conference-de-data-only" )
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
endif ()

####################################################################
# SciGRID Power Europe #############################################
####################################################################
# Publication:
#
# SciGRID - An Open Source Reference Model for the European
#           Transmission Network (v0.2)
#
# 2016
# Website: http://www.scigrid.de
####################################################################

if ( EGOA_DOWNLOAD_SCIGRID AND NOT EXISTS "${EGOA_DOWNLOAD_DIRECTORY_SCIGRID}/scigrid-conference-eu-data-only" )
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
endif ()

####################################################################
# IEEE Benchmark Cases #############################################
####################################################################
# Publication:
#
# Website:
#       * https://github.com/MATPOWER/matpower/archive/master.zip
#       * https://labs.ece.uw.edu/pstca
#       * https://www.maths.ed.ac.uk/optenergy
####################################################################

if ( EGOA_DOWNLOAD_IEEE AND NOT EXISTS "${EGOA_DOWNLOAD_DIRECTORY_IEEE}/IEEE" )
    message( STATUS "${MY_SPACE}Download IEEE Power Grid data.")

    # file ( MAKE_DIRECTORY "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/00-Matpower-Data" )
    # file ( MAKE_DIRECTORY "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/01-Pypower-Data" )
    file ( MAKE_DIRECTORY "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/02-gml" )
    # file ( MAKE_DIRECTORY "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases" )
    # file ( MAKE_DIRECTORY "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/04-IEEE-Dynamic_Test_Cases" )
    # file ( MAKE_DIRECTORY "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS" )
    # file ( MAKE_DIRECTORY "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/06-IEEE-Voltage_Collapse_Sensitivities" )
    file ( MAKE_DIRECTORY "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/07-PEGASE_Test_Cases" )
    # file ( MAKE_DIRECTORY "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/08-Edinburgh_Power_Flow_Test_Cases" )
    # file ( MAKE_DIRECTORY "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/09-Edinburgh_Dynamic_Test_Cases" )
    file ( MAKE_DIRECTORY "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/10-NESTA" )
    file ( MAKE_DIRECTORY "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/11-Dimacs" )
    file ( MAKE_DIRECTORY "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/12-Hitting-Sets" )
    file ( MAKE_DIRECTORY "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/13-Publication_Test_Cases" )
    file ( MAKE_DIRECTORY "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/14-EIRGrid_Test_Cases" )
    file ( MAKE_DIRECTORY "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/15-Synthetic_Power_Grid_Test_Cases" )
    file ( MAKE_DIRECTORY "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/16-Literature_Based_Power_Flow_Test_Cases" )
    file ( MAKE_DIRECTORY "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/17-Small_Signal_Stability_Test_Cases" )

    # Matlab ###################################################
    if ( NOT EXISTS "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/00-Matpower-Data" )
        file ( DOWNLOAD
            https://github.com/MATPOWER/matpower/archive/master.zip
            "${PROJECT_INCLUDE_DIR}/external/Matpower-Master.zip"
        )
        execute_process (
            COMMAND ${CMAKE_COMMAND} -E tar xzf ${PROJECT_INCLUDE_DIR}/external/Matpower-Master.zip
            WORKING_DIRECTORY ${PROJECT_INCLUDE_DIR}/external/
        )
        execute_process (
            COMMAND ${CMAKE_COMMAND} -E rename ${PROJECT_INCLUDE_DIR}/external/matpower-master/data ${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/00-Matpower-Data
            WORKING_DIRECTORY ${PROJECT_INCLUDE_DIR}/external/matpower-master/data/
        )
        file ( REMOVE ${PROJECT_INCLUDE_DIR}/external/Matpower-Master.zip )
    endif ()

    # PyPower ##################################################
    if ( NOT EXISTS "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/01-Pypower-Data" )
        file ( DOWNLOAD
            https://github.com/rwl/PYPOWER/archive/master.zip
            "${PROJECT_INCLUDE_DIR}/external/Pypower-Master.zip"
        )
        execute_process (
            COMMAND ${CMAKE_COMMAND} -E tar xzf ${PROJECT_INCLUDE_DIR}/external/Pypower-Master.zip
            WORKING_DIRECTORY ${PROJECT_INCLUDE_DIR}/external/
        )
        execute_process (
            COMMAND ${CMAKE_COMMAND} -E rename ${PROJECT_INCLUDE_DIR}/external/pypower-master/pypower ${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/01-Pypower-Data
            WORKING_DIRECTORY ${PROJECT_INCLUDE_DIR}/external/matpower-master/data/
        )

        execute_process (
            COMMAND bash -c "rm $(find \"${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/01-Pypower-Data\" -iname \"*.py\" | grep -v 'case' | sed 's/://')"
            COMMAND bash -c "rm \"${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/01-Pypower-Data/caseformat.py\""
            COMMAND bash -c "rm \"${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/01-Pypower-Data/loadcase.py\""
            COMMAND bash -c "rm \"${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/01-Pypower-Data/savecase.py\""
            WORKING_DIRECTORY ${PROJECT_INCLUDE_DIR}/external/matpower-master/data/
        )

        file ( REMOVE ${PROJECT_INCLUDE_DIR}/external/PYPOWER-master )
        file ( REMOVE ${PROJECT_INCLUDE_DIR}/external/Pypower-Master.zip )
    endif()

    # 14 Bus System ############################################
    if ( NOT EXISTS "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/014-Bus" )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/pf14/ieee14cdf.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/014-Bus/ieee14cdf.txt"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/pf14/pg_tca14fig.htm
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/014-Bus/pg_tca14fig.htm"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/pf14/14bus600.tif
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/014-Bus/14bus600.tif"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/formats/cdf.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/014-Bus/cdf.txt"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/pf14/pg_tca14bus.htm
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/014-Bus/pg_tca14bus.webarchive"
        )
    endif ()

    # 57 Bus System ############################################
    if ( NOT EXISTS "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/057-Bus" )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/pf57/ieee57cdf.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/057-Bus/ieee57cdf.txt"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/pf57/pg_tca57fig.htm
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/057-Bus/pg_tca57fig.htm"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/pf57/57bus600.tif
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/057-Bus/57bus600.tif"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/formats/cdf.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/057-Bus/cdf.txt"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/pf57/pg_tca57bus.htm
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/057-Bus/pg_tca57bus.webarchive"
        )
    endif ()

    # 118 Bus System ###########################################
    if ( NOT EXISTS "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/118-Bus" )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/pf118/ieee118psp.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/118-Bus/ieee118psp.txt"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/pf118/ieee118cdf.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/118-Bus/ieee118cdf.txt"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/pf118/pg_tca118fig.htm
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/118-Bus/pg_tca118fig.htm"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/pf118/118bus6.tif
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/118-Bus/118bus6.tif"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/formats/cdf.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/118-Bus/cdf.txt"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/formats/psap.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/118-Bus/psap.txt"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/pf118/pg_tca118bus.htm
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/118-Bus/pg_tca118bus.webarchive"
        )
    endif ()

    # 300 Bus System ###########################################
    if ( NOT EXISTS "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/300-Bus" )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/pf300/ieee300cdf.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/300-Bus/ieee300cdf.txt"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/pf300/ieee300pti.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/300-Bus/ieee300pti.txt"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/pf300/pg_tca300fig.htm
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/300-Bus/pg_tca300fig.htm"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/pf300/300bus6.tif
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/300-Bus/300bus6.tif"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/formats/cdf.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/300-Bus/cdf.txt"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/formats/pti.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/300-Bus/pti.txt"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/pf300/pg_tca300bus.htm
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/118-Bus/pg_tca300bus.webarchive"
        )
    endif ()

    # 17 Generator Dynamic System ##############################
    if ( NOT EXISTS "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/17-Generator" )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/dyn17/dd17cdf.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/17-Generator/dd17cdf.txt"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/dyn17/dd17cldat.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/17-Generator/dd17cldat.txt"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/Formats/cdf.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/17-Generator/cdf.txt"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/dyn17/pg_tcadd17.htm
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/17-Generator/pg_tcadd17.webarchive"
        )
    endif ()

    # 30 Bus Dynamic System ####################################
    if ( NOT EXISTS "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/30-Bus" )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/dyn30/dyn30dat.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/30-Bus/dyn30dat.txt"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/dyn30/pg_tcadyn30.htm
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases/30-Bus/pg_tcadyn30.webarchive"
        )
    endif ()

    # 50 Generator Dynamic System ##############################
    if ( NOT EXISTS "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/04-IEEE-Dynamic_Test_Cases/50-Generator" )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/dyn50/dd50cdf.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/04-IEEE-Dynamic_Test_Cases/50-Generator/dd50cdf.txt"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/dyn50/dd50cldat.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/04-IEEE-Dynamic_Test_Cases/50-Generator/dd50cldat.txt"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/dyn50/dd50exdat.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/04-IEEE-Dynamic_Test_Cases/50-Generator/dd50exdat.txt"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/dyn50/pg_tcadd50.htm
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/04-IEEE-Dynamic_Test_Cases/50-Generator/pg_tcadd50.txt"
        )
    endif ()

    # Reliability Test System (RTS) - 1979 #####################
    if ( NOT EXISTS "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1979-RTS" )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts79/ieeerts79.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1979-RTS/ieeerts79.txt"
        )
    endif ()

    # Reliability Test System (RTS) - 1996 #####################
    #
    if ( NOT EXISTS "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS" )
        #
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/pg_tcarts.htm
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/pg_tcarts.webarchive"
        )
        #
        # Bus Data
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-01.doc
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Bus-Data/Table-01.doc"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-01.wpd
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Bus-Data/Table-01.wpd"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-01.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Bus-Data/Table-01.txt"
        )
        #
        # Weekly Loads
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-02.doc
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Weekly-Loads/Table-02.doc"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-02.wpd
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Weekly-Loads/Table-02.wpd"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-02.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Weekly-Loads/Table-02.txt"
        )
        #
        # Daily Loads
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-03.doc
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Weekly-Loads/Table-03.doc"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-03.wpd
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Weekly-Loads/Table-03.wpd"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-03.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Weekly-Loads/Table-03.txt"
        )
        #
        # Hourly Loads
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-04.doc
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Hourly-Loads/Table-04.doc"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-04.wpd
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Hourly-Loads/Table-04.wpd"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-04.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Hourly-Loads/Table-04.txt"
        )
        #
        # Bus Loads
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-05.doc
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Bus-Loads/Table-05.doc"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-05.wpd
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Bus-Loads/Table-05.wpd"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-05.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Bus-Loads/Table-05.txt"
        )
        #
        # Generator reliability
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-06.doc
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Generator-Reliability/Table-06.doc"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-06.wpd
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Generator-Reliability/Table-06.wpd"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-06.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Generator-Reliability/Table-06.txt"
        )
        #
        # Generator parameters
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-07.doc
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Generator-Reliability/Table-07.doc"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-07.wpd
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Generator-Reliability/Table-07.wpd"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-07.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Generator-Reliability/Table-07.txt"
        )
        #
        # Generator startup heat input
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-08.doc
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Generator-Startup-Heat-Input/Table-08.doc"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-08.wpd
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Generator-Startup-Heat-Input/Table-08.wpd"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-08.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Generator-Startup-Heat-Input/Table-08.txt"
        )
        #
        # Generator heat rates
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-09.doc
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Generator-Heat-Rates/Table-09.doc"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-09.wpd
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Generator-Heat-Rates/Table-09.wpd"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-09.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Generator-Heat-Rates/Table-09.txt"
        )
        #
        # Generator cycling and ramp rates
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-10.doc
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Generator-Cycling-And-Ramp-Rates/Table-10.doc"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-10.wpd
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Generator-Cycling-And-Ramp-Rates/Table-10.wpd"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-10.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Generator-Cycling-And-Ramp-Rates/Table-10.txt"
        )
        #
        # Emissions
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-11.doc
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Emissions/Table-11.doc"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-11.wpd
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Emissions/Table-11.wpd"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-11.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Emissions/Table-11.txt"
        )
        #
        # Branch data
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-12.doc
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Branch-Data/Table-12.doc"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-12.wpd
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Branch-Data/Table-12.wpd"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-12.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Branch-Data/Table-12.txt"
        )
        #
        # DC line data
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-13.doc
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/DC-Line-Data/Table-13.doc"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-13.wpd
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/DC-Line-Data/Table-13.wpd"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-13.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/DC-Line-Data/Table-13.txt"
        )
        #
        # Breaker reliability data
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-14.doc
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Breaker-Reliability-Data/Table-14.doc"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-14.wpd
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Breaker-Reliability-Data/Table-14.wpd"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-14.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Breaker-Reliability-Data/Table-14.txt"
        )
        #
        # Generator dynamic data
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-15.doc
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Generator-Dynamic-Data/Table-15.doc"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-15.wpd
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Generator-Dynamic-Data/Table-15.wpd"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/rts/rts96/Table-15.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS/1996-RTS/Generator-Dynamic-Data/Table-15.txt"
        )
    endif ()

    # Voltage Collapse Sensitivities ###########################
    #
    if ( NOT EXISTS "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/06-IEEE-Voltage_Collapse_Sensitivities" )
        # 118 bus test case
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/sensitivity/sensreadme.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/06-IEEE-Voltage_Collapse_Sensitivities/sensreadme.txt"
        )
        # k factor values
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/sensitivity/sensk.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/06-IEEE-Voltage_Collapse_Sensitivities/sensk.txt"
        )
    endif ()

    # Edinburgh Dynamic Test Cases - Case 39 ###################
    #
    if ( NOT EXISTS "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/08-Edinburgh_Power_Flow_Test_Cases/39_Bus_Case" )
        file ( DOWNLOAD
            https://www.maths.ed.ac.uk/optenergy/NetworkData/39buscase/case39_RCost.m
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/08-Edinburgh_Power_Flow_Test_Cases/39_Bus_Case/case39_RCost.m"
        )
        file ( DOWNLOAD
            https://www.maths.ed.ac.uk/optenergy/NetworkData/39buscase/case39.pdf
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/08-Edinburgh_Power_Flow_Test_Cases/39_Bus_Case/case39.pdf"
        )
        file ( DOWNLOAD
            https://www.maths.ed.ac.uk/optenergy/NetworkData/39buscase/
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/08-Edinburgh_Power_Flow_Test_Cases/39_Bus_Case/case39.webarchive"
        )
    endif ()

    # Edinburgh Dynamic Test Cases - Iceland ###################
    #
    if ( NOT EXISTS "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/08-Edinburgh_Power_Flow_Test_Cases/Iceland" )
        file ( DOWNLOAD
            https://www.maths.ed.ac.uk/optenergy/NetworkData/iceland/iceland.m
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/08-Edinburgh_Power_Flow_Test_Cases/Iceland/iceland.m"
        )
        file ( DOWNLOAD
            https://www.maths.ed.ac.uk/optenergy/NetworkData/iceland/iceland.pdf
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/08-Edinburgh_Power_Flow_Test_Cases/Iceland/iceland.pdf"
        )
        file ( DOWNLOAD
            https://www.maths.ed.ac.uk/optenergy/NetworkData/iceland/
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/08-Edinburgh_Power_Flow_Test_Cases/Iceland/iceland.webarchive"
        )
    endif ()

    # Edinburgh Dynamic Test Cases - Reduced GB Network ########
    #
    if ( NOT EXISTS "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/08-Edinburgh_Power_Flow_Test_Cases/Reduced_GB_Network" )
        file ( DOWNLOAD
            https://www.maths.ed.ac.uk/optenergy/NetworkData/reducedGB/GBreducednetwork.m
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/08-Edinburgh_Power_Flow_Test_Cases/Reduced_GB_Network/GBreducednetwork.m"
        )
        file ( DOWNLOAD
            https://www.maths.ed.ac.uk/optenergy/NetworkData/reducedGB/GBreducednetwork.pdf
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/08-Edinburgh_Power_Flow_Test_Cases/Reduced_GB_Network/GBreducednetwork.pdf"
        )
        file ( DOWNLOAD
            https://www.maths.ed.ac.uk/optenergy/NetworkData/reducedGB/
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/08-Edinburgh_Power_Flow_Test_Cases/Reduced_GB_Network/reducedGB.webarchive"
        )
    endif ()

    # Edinburgh Dynamic Test Cases - GB Network ################
    #
    if ( NOT EXISTS "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/08-Edinburgh_Power_Flow_Test_Cases/GB_Network" )
        file ( DOWNLOAD
            https://www.maths.ed.ac.uk/optenergy/NetworkData/fullGB/GBnetwork.m
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/08-Edinburgh_Power_Flow_Test_Cases/GB_Network/GBnetwork.m"
        )
        file ( DOWNLOAD
            https://www.maths.ed.ac.uk/optenergy/NetworkData/fullGB/GB_graph.pdf
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/08-Edinburgh_Power_Flow_Test_Cases/GB_Network/GB_graph.pdf"
        )
        file ( DOWNLOAD
            https://www.maths.ed.ac.uk/optenergy/NetworkData/fullGB/
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/08-Edinburgh_Power_Flow_Test_Cases/GB_Network/fullGB.webarchive"
        )
        #
        file ( DOWNLOAD
            https://www.maths.ed.ac.uk/optenergy/NetworkData/introduction.html
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/08-Edinburgh_Power_Flow_Test_Cases/introduction.webarchive"
        )
        file ( DOWNLOAD
            https://www.maths.ed.ac.uk/optenergy/NetworkData/dataformat.html
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/08-Edinburgh_Power_Flow_Test_Cases/dataformat.webarchive"
        )
        file ( DOWNLOAD
            https://www.maths.ed.ac.uk/optenergy/NetworkData/howtouse.html
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/08-Edinburgh_Power_Flow_Test_Cases/HowToUseThisArchive.webarchive"
        )
        file ( DOWNLOAD
            https://www.maths.ed.ac.uk/optenergy/NetworkData/submission.html
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/08-Edinburgh_Power_Flow_Test_Cases/submission.webarchive"
        )
    endif ()

    # Edinburgh Dynamic Test Cases - Dynamic Iceland ###########
    #
    if ( NOT EXISTS "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/09-Edinburgh_Dynamic_Test_Cases/Iceland" )
        file ( DOWNLOAD
            https://www.maths.ed.ac.uk/optenergy/NetworkData/icelandDyn/d_iceland.m
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/09-Edinburgh_Dynamic_Test_Cases/Iceland/d_iceland.m"
        )
        file ( DOWNLOAD
            https://www.maths.ed.ac.uk/optenergy/NetworkData/icelandDyn/iceland.pdf
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/09-Edinburgh_Dynamic_Test_Cases/Iceland/iceland.pdf"
        )
        file ( DOWNLOAD
            https://www.maths.ed.ac.uk/optenergy/NetworkData/icelandDyn/
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/09-Edinburgh_Dynamic_Test_Cases/Iceland/icelandDyn.webarchive"
        )
        #
        file ( DOWNLOAD
            https://www.maths.ed.ac.uk/optenergy/NetworkData/introduction.html
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/09-Edinburgh_Dynamic_Test_Cases/introduction.webarchive"
        )
        file ( DOWNLOAD
            https://www.maths.ed.ac.uk/optenergy/NetworkData/dataformat.html
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/09-Edinburgh_Dynamic_Test_Cases/dataformat.webarchive"
        )
        file ( DOWNLOAD
            https://www.maths.ed.ac.uk/optenergy/NetworkData/howtouse.html
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/09-Edinburgh_Dynamic_Test_Cases/HowToUseThisArchive.webarchive"
        )
        file ( DOWNLOAD
            https://www.maths.ed.ac.uk/optenergy/NetworkData/submission.html
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/09-Edinburgh_Dynamic_Test_Cases/submission.webarchive"
        )
    endif ()

    # Data Formats #############################################
    #
    if ( NOT EXISTS "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/18-IEEE-Data_Formats" )
        # IEEE Common Data Format
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/formats/cdf.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/18-IEEE-Data_Formats/cdf.txt"
        )
        # PTI Power Flow Data Format
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/formats/pti.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/18-IEEE-Data_Formats/pti.txt"
        )
        # PECO PSAP Format
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/formats/psap.txt
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/18-IEEE-Data_Formats/psap.txt"
        )
    endif ()

    # Power System Application Data Dictionary - PSADD #########
    #
    if ( NOT EXISTS "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/19-Power_System_Application_Data_Dictionary" )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/psadd/psadd.doc
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/19-Power_System_Application_Data_Dictionary/psadd.doc"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/psadd/readme.doc
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/19-Power_System_Application_Data_Dictionary/readme.doc"
        )
        file ( DOWNLOAD
            https://labs.ece.uw.edu/pstca/psadd/pg_tcapsadd.htm
            "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/19-Power_System_Application_Data_Dictionary/pg_tcapsadd.webarchive"
        )
    endif ()
endif ()

####################################################################
# Generated Wind Farm Data from ITI 2017 ###########################
####################################################################
# Publication:
#
# A Simulated-Annealing-Based Approach for Wind Farm Cabling
#
# e-Energy '17: Proceedings of the Eighth International Conference
#               on Future Energy Systems
# 2017, Pages 203–215
# Website: https://doi.org/10.1145/3077839.3077843
####################################################################

set ( EGOA_DOWNLOAD_DIRECTORY_WINDFARM "${PROJECT_INCLUDE_DIR}/data/Windfarms" )
file ( MAKE_DIRECTORY "${EGOA_DOWNLOAD_DIRECTORY_WINDFARM}/Networks" )

if ( EGOA_DOWNLOAD_WINDFARM AND NOT EXISTS "${EGOA_DOWNLOAD_DIRECTORY_WINDFARM}/Networks/2017-iti-windfarm-benchmarksets" )
    message( STATUS "${MY_SPACE}Download generated wind farm data (ITI 2017) from \"https://i11www.iti.kit.edu/_media/projects/windfarmcabling/windfarm-benchmarksets.zip\" into \"${EGOA_DOWNLOAD_DIRECTORY_WINDFARM}/Networks/2017-iti-windfarm-benchmarksets/\".")

    file ( DOWNLOAD
        https://i11www.iti.kit.edu/_media/projects/windfarmcabling/windfarm-benchmarksets.zip
        "${EGOA_DOWNLOAD_DIRECTORY_WINDFARM}/Networks/windfarm-benchmarksets.zip"
        # URL_HASH SHA512=52eff0790e78e2718e81e4ee2e0fc965180900d236e05822501019c8148a249529f7194e616c28394960a3086911af361165073cdf24195c7e5f1d603e463112
        # SHOW_PROGRESS
    )

    execute_process (
        COMMAND ${CMAKE_COMMAND} -E tar xzf ${EGOA_DOWNLOAD_DIRECTORY_WINDFARM}/Networks/windfarm-benchmarksets.zip
        WORKING_DIRECTORY ${EGOA_DOWNLOAD_DIRECTORY_WINDFARM}/Networks/
    )

    execute_process (
        COMMAND mv ${EGOA_DOWNLOAD_DIRECTORY_WINDFARM}/Networks/windfarm-benchmarksets ${EGOA_DOWNLOAD_DIRECTORY_WINDFARM}/Networks/2017-iti-windfarm-benchmarksets
        WORKING_DIRECTORY ${EGOA_DOWNLOAD_DIRECTORY_WINDFARM}/Networks/
    )

    execute_process (
        COMMAND rm -r ${EGOA_DOWNLOAD_DIRECTORY_WINDFARM}/Networks/windfarm-benchmarksets
        WORKING_DIRECTORY ${EGOA_DOWNLOAD_DIRECTORY_WINDFARM}/Networks/
    )

    file ( REMOVE ${EGOA_DOWNLOAD_DIRECTORY_WINDFARM}/Networks/windfarm-benchmarksets.zip )
endif ( )

message( STATUS "")
