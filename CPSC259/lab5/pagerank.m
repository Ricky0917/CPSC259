% -------------------------------------------------------------------
%  Generated by MATLAB on 2-Dec-2022 20:54:31
%  MATLAB version: 9.13.0.2105380 (R2022b) Update 2
% -------------------------------------------------------------------
                                   

ConnectivityMatrix = ...
  [0 1 1 0;
   1 0 1 0;
   1 1 0 0;
   0 0 0 0];

D = zeros(4,4);
D(1,1) = 0.5;
D(2,2) = 0.5;
D(3,3) = 0.5;
D = sparse(D);

PageRank = [0.31746031746031744; 0.31746031746031744; 0.31746031746031744; ...
            0.047619047619047623];

Q = ...
  [1 1 1 1;
   1 1 1 1;
   1 1 1 1;
   1 1 1 1];

StochasticMatrix = ...
  [0 0.5 0.5 0.25;
   0.5 0 0.5 0.25;
   0.5 0.5 0 0.25;
   0 0 0 0.25];

TransitionMatrix = ...
  [0.037500000000000006 0.4625 0.4625 0.25;
   0.4625 0.037500000000000006 0.4625 0.25;
   0.4625 0.4625 0.037500000000000006 0.25;
   0.037500000000000006 0.037500000000000006 0.037500000000000006 0.25];

column = 4;

columns = 4;

columnsums = [2 2 2 0];

dimension = 4;

i = 100;

p = 0.85;

row = 1;

rows = 4;

zerocolumns = [1 2 3];

