%weather model of the world

load topo topo topomap1    % load data 
whos('topo','topomap1')

x = 0:359;                                % longitude
y = -89:90;                               % latitude

figure
contour(x,y,topo,[0 0])

axis equal                                % set axis units to be the same size
box on                                    % display bounding box

ax = gca;                                 % get current axis               
ax.XLim = [0 360];                        % set x limits
ax.YLim = [-90 90];                       % set y limits
ax.XTick = [0 60 120 180 240 300 360];    % define x ticks
ax.YTick = [-90 -60 -30 0 30 60 90];      % define y ticks

%phase one complete

image([0 360],[-90 90], flip(topo), 'CDataMapping', 'scaled')
colormap(topomap1)

axis equal                                % set axis units to be the same size

ax = gca;                                 % get current axis               
ax.XLim = [0 360];                        % set x limits
ax.YLim = [-90 90];                       % set y limits
ax.XTick = [0 60 120 180 240 300 360];    % define x ticks
ax.YTick = [-90 -60 -30 0 30 60 90];      % define y ticks

%phase 2

clf
[x,y,z] = sphere(50);          % create a sphere 
s = surface(x,y,z);            % plot spherical surface

s.CData = topo;                % set color data to topographic data
s.FaceColor = 'texturemap';    % use texture mapping
s.EdgeColor = 'none';          % remove edges
s.FaceLighting = 'gouraud';    % preferred lighting for curved surfaces
s.SpecularStrength = 0.4;      % change the strength of the reflected light

light('Position',[-1 0 1])     % add a light

axis square off                % set axis to square and remove axis
view([-30,30])                 % set the viewing angle

%phase 3, polarizing the function