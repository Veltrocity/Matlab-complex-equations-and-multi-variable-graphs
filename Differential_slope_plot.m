%Differential slope plotting

% Load some sample data:
[X,Y,Z] = peaks(1000);
Z = Z/5;

% Calculate local slopes:

sl = slope2(X,Y,Z,'degrees');

% Plot surface slopes:
surf(X,Y,Z,sl)
shading flat
cb = colorbar;

% Make it pretty:
ylabel(cb,'local slope (degrees)')
camlight
axis tight
material dull
view(-16,38)

%doesnt work
%need more libs and more undefined functions
