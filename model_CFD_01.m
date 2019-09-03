

%can't get it to work, something about unedfined function
% Point distribution.
n_p = 18;   % Number of radial points.
n_z = 20;   % Number of points lengthwise.
th = linspace(0,2*pi,n_p);
p = [];
for r=[0.05 0.1 0.2 0.3]
  for z_i=linspace(-1,1,n_z)
    p = [ p; [ r*cos(th(1:end-1)) z_i*ones(1,n_p-1)  r*sin(th(1:end-1)) ;
               r*sin(th(1:end-1)) r*cos(th(1:end-1)) z_i*ones(1,n_p-1)  ;
               z_i*ones(1,n_p-1)  r*sin(th(1:end-1)) r*cos(th(1:end-1)) ]' ];
  end
end

% Triangulate points.
t = delaunay( p );

% Remove triangulated cells outside the cylinders.
pc = [ mean( reshape( p(t,1), size(t) )' )' ...
       mean( reshape( p(t,2), size(t) )' )' ...
       mean( reshape( p(t,3), size(t) )' )' ];   % Cell center coordinates.
t = t( any( [ sqrt( pc(:,1).^2 + pc(:,2).^2 )' ;
              sqrt( pc(:,1).^2 + pc(:,3).^2 )' ;
              sqrt( pc(:,2).^2 + pc(:,3).^2 )' ] <= r+sqrt(eps) ), : );

% Generate distance function distribution.
u = min([ sqrt( p(:,1).^2 + p(:,2).^2 )' ;
          sqrt( p(:,1).^2 + p(:,3).^2 )' ;
          sqrt( p(:,2).^2 + p(:,3).^2 )' ])';
p = p'; t = t';   % Transpose to change to row ordering.

grid.p = p;   % Grid/mesh points.
grid.c = t;   % Grid/mesh cells.

grid.a = gridadj( grid.c, size(grid.p,1) );   % Grid cell adjacency.
grid.b = gridbdr( grid.p, grid.c, grid.a );   % Grid boundary data.
grid.s = ones(1,size(grid.c,2));

% Set subdomain number 1 for all cells.

plotgrid( grid );

plotgrid( grid, 'renderer', 'plotly' );


