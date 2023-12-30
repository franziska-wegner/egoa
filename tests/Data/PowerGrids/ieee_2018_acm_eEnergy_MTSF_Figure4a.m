%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%   Paper: The Maximum Transmission Switching Flow Problem
%     DOI: 10.1145/3208903.3208910
%    ISBN: 978-1-4503-5767-8/18/06
% Network: Figure 4 b
%
% ACM e-Energy ’18, June 12–15, 2018, Karlsruhe, Germany
%
%   Created on: Feb 20, 2019
%       Author: Franziska Wegner
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% vertex s has vertex identifier 1
% vertex u has vertex identifier 2
% vertex v has vertex identifier 3
% vertex t has vertex identifier 4
%
% (1,2) -> (s,u) with cap(s,u) =  x and b(s,u) = 1
% (1,3) -> (s,v) with cap(s,v) = 4x and b(s,v) = 1
% (1,4) -> (s,t) with cap(s,t) = 3x and b(s,t) = 1
% (2,3) -> (u,v) with cap(u,v) =  x and b(u,v) = 1
% (3,4) -> (v,t) with cap(v,t) =  x and b(v,t) = 1
%
% OPT_{DCMPF}  = 8/3 x
% OPT_{DCMTSF} =   4 x  ( Network should be set to bounded )
%
% Note that we use here x = 1.
%
% see [Figure 4a; Section 5; Grastien et al., 2018]
% or slide 20 in https://i11www.iti.kit.edu/_media/members/franziska_wegner/2018-07-18_franziska-wegner_energieinformatik_teil13_vl2_the-maximum-transmission-switching-flow-problem.pdf
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function mpc = mtsf_case4_fig4_a
mpc.version = '2';
mpc.baseMVA = 1.0;

%% bus data
%   bus_i   type    Pd  Qd  Gs  Bs  area    Vm  Va  baseKV  zone    Vmax    Vmin
mpc.bus = [
    1    3   0.0    0.0    0.0     0.0     1      1.00000    -0.00000  240.0   1      1.10000     0.90000;
    2    1   0.0    0.0    0.0     0.0     1      1.00000     0.00000  240.0   1      1.10000     0.90000;
    3    1   0.0    0.0    0.0     0.0     1      1.00000    -0.00000  240.0   1      1.10000     0.90000;
    4    1   8.0    1.1    0.0     0.0     1      1.00000    -0.00000  240.0   1      1.10000     0.90000;
];

%% generator data
%   bus Pg  Qg  Qmax    Qmin    Vg  mBase   status  Pmax    Pmin    Pc1 Pc2 Qc1min  Qc1max  Qc2min  Qc2max  ramp_agc    ramp_10 ramp_30 ramp_q  apf
mpc.gen = [
    1      1.234     1.111     2.0      0.0     1.1     1.0     1     8.0       0.0     0.0     0.0     0.0     0.0     0.0     0.0     0.0     0.0     0.0     0.0     0.0;
];

%% branch data
%   fbus    tbus    r   x   b   rateA   rateB   rateC   ratio   angle   status  angmin  angmax
mpc.branch = [
    1    2   0.000   1.0     0.0     1.00    0.0     0.0     0.0     0.0     1   -30.0   30.0;
    1    3   0.000   1.0     0.0     4.00    0.0     0.0     0.0     0.0     1   -30.0   30.0;
    1    4   0.000   1.0     0.0     3.00    0.0     0.0     0.0     0.0     1   -30.0   30.0;
    2    3   0.000   1.0     0.0     1.00    0.0     0.0     0.0     0.0     1   -30.0   30.0;
    3    4   0.000   1.0     0.0     1.00    0.0     0.0     0.0     0.0     1   -30.0   30.0;
];
