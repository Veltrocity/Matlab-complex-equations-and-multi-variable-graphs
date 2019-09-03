%CFD model 02

% Define help fea finite element struct.
fea.grid = grid;            % Assign grid to fea struct.
fea.sdim = {'x' 'y' 'z'};   % Assign space dimension coordinate names.
fea.dvar = {'u'};           % Assign help dependent variable name.
fea.sfun = {'sflag1'};      % Assign linear interpolation.

% Check and parse fea struct and assign solution data field.
fea.sol.u = u(:);
fea = parseprob( fea );

postplot( fea, 'surfexpr', 'u+sin(2*pi*x)', ...
               'renderer', 'plotly' );