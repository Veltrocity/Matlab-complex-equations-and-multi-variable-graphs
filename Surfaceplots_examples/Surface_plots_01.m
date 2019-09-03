%surface plots

x = -4:1:4;             % The range of x values.
y = -4:1:4;             % The range of y values.
[X,Y] = meshgrid (x,y); % This generates the actual grid of x and y values.

Z=Y.^2+X.^2;            % The function we're plotting.
% Remember to use the correct vector notation for all operations (such as
% using the '.^' operator to do piecewise powers).

figure(1);              % Generating a new window to plot in.
surf(X,Y,Z)             % The surface plotting function.

%figure 1 complete

figure(2);                  % Generating a new window to plot in.
x1 = -4:.1:4;               % The range of x values.
y1 = -4:.1:4;               % The range of y values.
[X1,Y1] = meshgrid (x1,y1); % This generates the actual grid of x and y values.
Z1=Y1.^2+X1.^2;             % The function we're plotting.
surf(X1,Y1,Z1)              % The surface plotting function.