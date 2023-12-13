[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](http://www.gnu.org/licenses/gpl-3.0)   [![CMake on multiple platforms](https://github.com/franziska-wegner/egoa/actions/workflows/cmake-multi-platform.yml/badge.svg?branch=master)](https://github.com/franziska-wegner/egoa/actions/workflows/cmake-multi-platform.yml)   [![CodeQL](https://github.com/franziska-wegner/egoa/actions/workflows/codeql.yml/badge.svg?branch=master)](https://github.com/franziska-wegner/egoa/actions/workflows/codeql.yml) <a href="https://scan.coverity.com/projects/franziska-wegner-egoa"><img alt="Coverity Scan Build Status" src="https://scan.coverity.com/projects/29511/badge.svg"/></a>   [![codecov](https://codecov.io/gh/franziska-wegner/egoa/graph/badge.svg?token=OL0N2WXV4I)](https://codecov.io/gh/franziska-wegner/egoa)
<h1 align="center">EGOA - Energy Grid Optimization and Analysis</h1>

Energy Grid Optimization and Analysis (EGOA) is a framework for energy grid analysis and planning. This framework is based on the PhD thesis <a href="http://dx.doi.org/10.5445/IR/1000120612">"Combinatorial Problems in Energy Networks -- Graph Theoretic Models and Algorithms"</a>. The Git repository of the PhD thesis is available under <a href="https://github.com/franziska-wegner/PhD_Thesis--Combinatorial_Problems_in_Energy_Networks--Graph_Theoretic_Models_and_Algorithms">Combinatorial_Problems_in_Energy_Networks</a>. 

<h2>Workflow Status</h2>

|  |  |
|-----:|-----------|
| Linux & Windows & MacOS Build Status: | [![CMake on multiple platforms](https://github.com/franziska-wegner/egoa/actions/workflows/cmake-multi-platform.yml/badge.svg?branch=master)](https://github.com/franziska-wegner/egoa/actions/workflows/cmake-multi-platform.yml)|
| [CodeQL](https://codeql.github.com) Scan Build Status: | [![CodeQL](https://github.com/franziska-wegner/egoa/actions/workflows/codeql.yml/badge.svg?branch=master)](https://github.com/franziska-wegner/egoa/actions/workflows/codeql.yml) |
| Project Documentation: | [Code Documentation by Doxygen](https://franziska-wegner.github.io/egoa) |
| Coverity Scan Build Status: | <a href="https://scan.coverity.com/projects/franziska-wegner-egoa"><img alt="Coverity Scan Build Status" src="https://scan.coverity.com/projects/29511/badge.svg"/></a> |
| Code Coverage: | [![codecov](https://codecov.io/gh/franziska-wegner/egoa/graph/badge.svg?token=OL0N2WXV4I)](https://codecov.io/gh/franziska-wegner/egoa) |

<h2>Installation</h2>

This is a Cmake project and can be run in any C++ IDE (Integrated Development Environment) that is on the market and supports CMake. You have to define a certain set of parameters dependent ozn your system and what you wish to run in general. The following description will help you with the initial setup. The links to frameworks that can be linked to this project are given in addition.

<h3>Required Preinstallations</h3>

The Qt project can be installed on a Mac using

```
brew install qt
```

and on Ubuntu using 

```
sudo apt-get install qt
```

The compiler clang and gcc can be installed on a Mac using the following command or you use the Apple clang compiler if necessary. 

```
brew install llvm
brew install gcc
```

If the tests are enabled `"EGOA_TEST_FRAMEWORK": "OfflineGoogleTestFramework"` the `"EGOA_TEST_FRAMEWORK_LOCATION"`, e.g., `"EGOA_TEST_FRAMEWORK_LOCATION": "external/googletest"`, needs a valid path to the test framework. If you prefer to manualy set the path, the <a href="https://github.com/google/googletest/tree/main">google test framework</a> can be cloned from https://github.com/google/googletest/tree/main, which is the easiest way to have a up-to-date version of the repository. Using the above example configuration run:

```
> cd egoa
> cd external
> git clone https://github.com/google/googletest.git
```

<h3>CMake Parameter Overrides</h3>

The repository provides an intial set of parameters in the sublimetext project file that can be found under `egoa.sublime-project`. In addition, there are scripts that support with server and local runs that have a initial CMake parameter configuration and can be adapted to the particular needs under [egoa/scripts/Build](https://github.com/franziska-wegner/egoa/tree/master/scripts/Build) and monitoring scripts under [egoa/scripts/Experiments](https://github.com/franziska-wegner/egoa/tree/master/scripts/Experiments).
An essential CMake setting parameter is the build directory that should be changed according to your file system, e.g., `"build_folder": "/Users/fwegner/Documents/Repositories/Public/EGOA/egoa/build-debug"`. 

<details>
<summary>Example CMake Configuration for SublimeText</summary>

```
"cmake": {
    "build_folder": "/Users/fwegner/Documents/Repositories/Public/EGOA/build-debug",
    "command_line_overrides": {
        "Boost_NO_SYSTEM_PATHS": "TRUE",
        "EGOA_BUILD_TYPE": "Debug",
        "EGOA_DOWNLOAD_CPPAD": "OFF",
        "EGOA_DOWNLOAD_EIGEN": "OFF",
        "EGOA_DOWNLOAD_GOOGLE_TEST_FRAMEWORK": "OFF",
        "EGOA_DOWNLOAD_IEEE": "ON",
        "EGOA_DOWNLOAD_PYPSA_EUR": "ON",
        "EGOA_DOWNLOAD_PYPSA_ITI_COLLABORATION": "ON",
        "EGOA_DOWNLOAD_SCIGRID": "ON",
        "EGOA_DOWNLOAD_WINDFARM": "ON",
        "EGOA_ENABLE_ASSERTION": "ON",
        "EGOA_ENABLE_BONMIN": "OFF",
        "EGOA_ENABLE_BOOST": "OFF",
        "EGOA_ENABLE_CPLEX": "OFF",
        "EGOA_ENABLE_DOCUMENTATION": "ON",
        "EGOA_ENABLE_EXCEPTION_HANDLING": "ON",
        "EGOA_ENABLE_GUROBI": "OFF",
        "EGOA_ENABLE_IPOPT": "OFF",
        "EGOA_ENABLE_OGDF": "OFF",
        "EGOA_ENABLE_OPENMP": "OFF",
        "EGOA_ENABLE_TESTS": "ON",
        "EGOA_ENABLE_VERBOSE_MAKEFILE": "ON",
        "EGOA_PEDANTIC_AS_ERRORS": "OFF",
        "EGOA_PEDANTIC_MODE": "ON",
        "EGOA_TEST_FRAMEWORK": "OnlineGoogleTestFramework",
        "EGOA_TEST_FRAMEWORK_LOCATION": "external/GoogleTestFramework",
        "EGOA_THREAD_LIMIT": "0",
        "EGOA_WARNINGS_AS_ERRORS": "ON",
        "Boost_DIRECTORIES": "/opt/homebrew/opt/boost/",
        "BONMIN_ROOT_DIR": "/Users/fwegner/Documents/Repositories/Public/EGOA/external_libraries/Bonming-1.8/build",
        "CMAKE_CXX_COMPILER": "/opt/homebrew/opt/llvm/bin/clang++",
        "CMAKE_C_COMPILER": "/opt/homebrew/opt/llvm/bin/clang",
        "COIN_INCLUDE_DIR": "/Users/fwegner/Documents/Repositories/Public/EGOA/external_libraries/ogdf-debug/include",
        "COIN_LIBRARY_DIR": "/Users/fwegner/Documents/Repositories/Public/EGOA/external_libraries/ogdf-debug",
        "CPLEX_HOME": "/Applications/CPLEX_Studio128",
        "GUROBI_ROOT_DIR": "/Library/gurobi800/mac64/",
        "OGDF_AUTOGEN_INCLUDE_DIR": "/Users/fwegner/Documents/Repositories/Public/EGOA/external_libraries/ogdf-debug/include",
        "OGDF_INCLUDE_DIR": "/Users/fwegner/Documents/Repositories/Public/EGOA/external_libraries/ogdf20170723-debug/include",
        "OGDF_LIBRARY_DIR": "/Users/fwegner/Documents/Repositories/Public/EGOA/external_libraries/ogdf-debug",
        "OPENMP_INCLUDES": "/opt/homebrew/opt/llvm/include",
        "OPENMP_LIBRARIES": "/opt/homebrew/opt/llvm/lib",
    },
}
```

</details>

Most parameters represent flags and can be enabled with `ON` if available and `OFF` if not available. Dependent on the flag the required path to the framework or tool has to be set accordingly (see above). There are flags that enable downloads for data sets and frameworks, and start with `EGOA_DOWNLOAD_<framework|dataset>`. The recommendation is to start with a minimum of enabled tools and extend if necessary.

This framework provides a set of unittests that uses the Google Test Framework as base. The CMake files allow two different setups of the test framework that are known by online and offline configuration. The CMake parameter for the online version are `"EGOA_TEST_FRAMEWORK": "OnlineGoogleTestFramework"` OR `"EGOA_TEST_FRAMEWORK": "OfflineGoogleTestFramework"` with the pointer to the installation directory of the Google test framework repository, e.g., `"EGOA_TEST_FRAMEWORK_LOCATION": "external/GoogleTestFramework"`. 

<details>
<summary>Successful Initial CMake Run</summary>

```
-- 
-- /Users/fwegner/Documents/Repositories/Public/EGOA/egoa
-- 
-- /Users/fwegner/Documents/Repositories/Public/EGOA/egoa/build-debug
-- Set OpenMP variables
--  OMP_WAIT_POLICY:      ACTIVE
--  OMP_STACKSIZE:      
--  OMP_SCHEDULE:       
--  OMP_PROC_BIND:        TRUE
--  OMP_THREAD_LIMIT:     0
--  Number of processors:   8
--  OMP_NUM_THREADS:      8
-- 
--  Compiler extra flags:      -pedantic -Werror  -Wall -Wextra -Wunused-result -Wno-error=unused-but-set-variable -Wno-error=conversion -Wshadow -Wno-error=zero-length-array 
-- 
-- Download of data sets:
--  Download PyPSA Europe data from https://github.com/PyPSA/pypsa-eur.git into /Users/fwegner/Documents/Repositories/Public/EGOA/egoa/data/PowerGrids/PyPSA/pypsa-eur.
--  Download PyPSA ITI Collaboration data from https://git.scc.kit.edu/FN/iti-collaboration.git into /Users/fwegner/Documents/Repositories/Public/EGOA/egoa/data/PowerGrids/PyPSA/pypsa-iti-collaboration.
--  Download IEEE Power Grid data.
-- 
-- Looking for Qt6
-- Could NOT find WrapVulkanHeaders (missing: Vulkan_INCLUDE_DIR) 
-- Could NOT find WrapVulkanHeaders (missing: Vulkan_INCLUDE_DIR) 
--  Found Qt6 Core module in "/opt/homebrew/lib/QtCore.framework/Versions/A/QtCore" 
--  Found Qt6 Quick module in "/opt/homebrew/lib/QtQuick.framework/Versions/A/QtQuick" 
--  Found Qt6 Widgets module in "/opt/homebrew/lib/QtWidgets.framework/Versions/A/QtWidgets" 
--  Found Qt6 Concurrent module in "/opt/homebrew/lib/QtConcurrent.framework/Versions/A/QtConcurrent" 
SRC=/Users/fwegner/Documents/Repositories/Public/EGOA/egoa and Binary=/Users/fwegner/Documents/Repositories/Public/EGOA/egoa/build-debug
--  Doxygen:      /opt/homebrew/bin/doxygen
-- Google Test Framework
--  EGOA_ENABLE_TESTS:      ON
-- 
-- Neither OGDF nor COIN include directory and library are added to the project.
-- 
-- Compiler:
--  CMAKE_C_COMPILER:   /opt/homebrew/opt/llvm/bin/clang
--  CMAKE_CXX_COMPILER:   /opt/homebrew/opt/llvm/bin/clang++
--  make VERBOSE = 1? :   TRUE
-- 
-- Other important targets:
--  qt6:        add libraries of QT6
--  doc:        build doxygen documentation
--  EGOA Exceptions:    ON
--  EGOA Assertions:    ON
-- 
-- Build type is set to:    Debug
-- Build files have been written to:  /Users/fwegner/Documents/Repositories/Public/EGOA/egoa/build-debug
-- Runtime output directory:    /Users/fwegner/Documents/Repositories/Public/EGOA/egoa/build-debug/bin
-- Archive output directory:    /Users/fwegner/Documents/Repositories/Public/EGOA/egoa/build-debug/lib
-- Library output directory:    /Users/fwegner/Documents/Repositories/Public/EGOA/egoa/build-debug/lib
-- 
-- Configuring done (3.2s)
-- Generating done (0.1s)
-- Build files have been written to: /Users/fwegner/Documents/Repositories/Public/EGOA/egoa/build-debug
[Finished in 3.4s]
```
</details>


<h2>Recommended IDEs</h2>

A general recommendation is CLION and Sublimetext. However, Visual Studio and others work fine as well.

<h2>Documentation</h2>

The repository's public code documentation is available under [Code Documentation by Doxygen](https://franziska-wegner.github.io/egoa). For the purpose of code documentation, the <a href="https://www.doxygen.nl">Doxygen</a> framework is used. It provides a simple and well formed way of code documentation for C++. Run 

    make doc

to compile and generate the repository's documentation. The `DoxyfileConfig.in` can be adapted and supports HTML (see `GENERATE_HTML`), LaTex (see `GENERATE_LATEX`), RTF (see `GENERATE_RTF`), MAN page (see `GENERATE_MAN`), XML (see `GENERATE_XML`), and DOCBOOK (see `GENERATE_DOCBOOK`) output of the documentation. Initially only html and latex is generated. The output directory is under`./documentation` and can be changed at `OUTPUT_DIRECTORY` if necessary.

<h2>Benchmark Data Sets</h2>

As mentioned in "CMake Parameter Overrides" the CMake file downloads a lot of benchmark cases itself denoted by `EGOA_DOWNLOAD_<dataset>`, which helps you to start your work faster. Each successful CMake run shows the downloaded dataset directories by

```
...
-- Download of data sets:
--  Download PyPSA Europe data from https://github.com/PyPSA/pypsa-eur.git into /home/runner/work/egoa/egoa/data/PowerGrids/PyPSA/pypsa-eur.
--  Download PyPSA ITI Collaboration data from https:/git.scc.kit.edu/FN/iti-collaboration.git into /home/runner/work/egoa/egoa/data/PowerGrids/PyPSA/pypsa-iti-collaboration.
--  Download SciGRID Power data (version 0.1) from "https://www.power.scigrid.de/releases_archive/scigrid-0.1-data-only.zip" into '/home/runner/work/egoa/egoa/data/PowerGrids/SciGrid/scigrid-0.1-data-only/".
--  Download SciGRID Power data (version 0.2) from "https://www.power.scigrid.de/releases_archive/scigrid-0.2-data-only.zip" into "/home/runner/work/egoa/egoa/data/PowerGrids/SciGrid/scigrid-0.2-data-only/".
--  Download SciGRID Power data (conference version) from "https://www.power.scigrid.de/releases_archive/scigrid-conference-de-data-only.zip" into "/home/runner/work/egoa/egoa/data/PowerGrids/SciGrid/scigrid-conference-de-data-only/".
--  Download SciGRID Power data (conference version) from "https://www.power.scigrid.de/releases_archive/scigrid-conference-eu-data-only.zip" into "/home/runner/work/egoa/egoa/data/PowerGrids/SciGrid/scigrid-conference-eu-data-only/".
--  Download IEEE Power Grid data.
--  Download generated wind farm data (ITI 2017) from "https://i1wwww.iti.kit.edu/media/projects/windfarmcabling/windfarm-benchmarksets.zip" into "/home/runner/work/egoa/egoa/data/Windfarms/Networks/2017-iti-windfarm-benchmarksets/".
...
```

At the moment this is limited to PyPSA, the IEEE cases, and the windfarm cases; and will be extended to other test cases. At the end the following data is on you hard drive in the `egoa/data` after an initial CMake run with all download flags enabled. Note that `(+)` means that the folder is empty at the moment and we need a reliable place to upload the data for research with the right license or the repository went offline/is not public.

<details open>
<summary>Windfarm</summary>

```
+ Cabletypes
- Networks
    + 2017-iti-windfarm-benchmarksets
```

</details>

<details open>
<summary>IEEE</summary>

```
IEEE
+ 00-Matpower-Data
(+) 02-gml 
+ 03-IEEE-Power_Flow_Test_Cases
+ 04-IEEE-Dynamic_Test_Cases
+ 05-IEEE-Reliability_Test_Systems-RTS
+ 06-IEEE-Voltage Collapse_Sensitivities
(+) 07-PEGASE_Test_Cases
+ 08-Edinburgh_Power_Flow_Test_Cases
+ 09-Edinburgh_Dynamic_Test_Cases
(+) 10-NESTA
(+) 11-Dimacs
(+) 12-Hitting-Sets
(+) 13-Publication_Test_Cases
(+) 14-EIRGrid_Test_Cases
(+) 15-Synthetic_Power_Grid_Test_Cases
(+) 16-Literature_Based_Power_Flow_Test_Cases
(+) 17-Small_Signal_Stability_Test_Cases
+ 18-IEEE-Data_Formats
+ 19-Power_System_Application_Data_Dictionary
```

</details>

<details>
<summary>PyPSA</summary>

```
- pypsa-eur
  - data
    - entsoegridkit
      • buses.csv
      • converters.csv
      • generators.csv
      • lines.csv
      • links.csv
      • transformers.csv
    - existing_infrastructure
      • existing_heating_raw.csv
      • offwind_capacity_IRENA.csv
      • onwind_capacity_IRENA.csv
      • solar_capacity_IRENA.csv
    - retro
      • comparative_level_investment.csv
      • data_building_stock.csv
      • electricity_taxes_eu.csv
      • floor_area_missing.csv
      • retro_cost_germany.csv
      • u_values_poland.csv
      • window_assumptions.csv
    • agg_p_nom_minmax.csv
    • attributed_ports.json
    • custom_powerplants.csv
    • district_heat_share.csv
    • eia_hydro_annual_generation.csv
    • geth2015_hydro_capacities.csv
    • heat_load_profile.csv
    • heat_load_profile_BDEW.csv
    • heat_load_profile_DK_AdamJensen.csv
    • hydrogen_salt_cavern_potentials.csv
    • links_p_nom.csv
    • links_tyndp.csv
    • nuclear_p_max_pu.csv
    • parameter_corrections.yaml
    • unit_commitment.csv
    • urban_percent.csv
- pypsa-iti-collaboration
+ elec_s1024_AT
+ elec_s1024_BE
+ elec_s1024_BG
+ elec_s1024_CH
+ elec_s1024_CZ
+ elec_s1024_DK
+ elec_s1024_HR
+ elec_s1024_HU
+ elec_s1024_IE
+ elec_s1024_NL
+ elec_s1024_NO
+ elec_s1024_PL
+ elec_s1024_PT
+ elec_s1024_RO
+ elec_s1024_SE
+ elec_s1024_SI
+ elec_s1024_SK
```

</details>

<details>
<summary>SciGrid</summary>

```
+ scigrid-0.1-data-only
+ scigrid-0.2-data-only
+ scigrid-conference-de-data-only
+ scigrid-conference-eu-data-only
```

</details>

<h2>Resources</h2>

https://www.doxygen.nl
https://github.com/franziska-wegner/PhD_Thesis--Combinatorial_Problems_in_Energy_Networks--Graph_Theoretic_Models_and_Algorithms
http://dx.doi.org/10.5445/IR/1000120612

<h2>License</h2>

This work---including recursively all subfolder contents and files---is licensed under <a href="https://www.gnu.org/licenses/gpl-3.0.html">GNU General Public License (GPL) v3</a>.

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/9/93/GPLv3_Logo.svg/2880px-GPLv3_Logo.svg.png" width="100" />
