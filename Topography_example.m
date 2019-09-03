% Load and tweak peaks data:
[Y,X,Z] = peaks;
Z(Z<0)=0; 
X = flipud(X*35); 
Y = Y*35; 
Z = Z*25; 
% Plot peaks surface
figure('pos',[50 50 900 660])
hp = surf(X,Y,Z);
axis([-100 100 -100 100 0 200])
colormap(hot(256))
shading interp
lighting gouraud
camlight
zoom(1.5)
hold on

frames = 300; % number of frames in our movie show. 
% Plane 1: Periwinkle plane flies left to right: 
y1 = linspace(-250,400,frames); 
x1 = zeros(size(y1)); 
z1 = 100*ones(size(y1)); 
path1 = plot3(x1,y1,z1,'.-','color',[0.5569 0.5098 0.9961]);
% Plane 2: Red plane flies right to left: 
y2 = fliplr(y1); 
x2 = x1; 
z2 = z1+50; 
path2 = plot3(x2,y2,z2,'r.-');
% Plane 3: Gray and blue plane flies 'round the mountain: 
x3 = zeros(size(x2)); 
x3(201:273) = -80*sind((0:15:3*360)-90)-80;
y3 = zeros(size(x2)); 
y3(1:175) = -250; 
y3(176:200) = linspace(-250,0,25);
y3(201:273) = 80*cosd((0:15:3*360)-90);
y3(274:end) = linspace(0,250,length(y3)-273); 
z3 = 120+40*cos(linspace(pi,4*pi,length(y3)))+y3/4;
path3 = plot3(x3,y3,z3,'b.-');
% Set view: 
view([70 33])
axis([-100 100 -100 100 0 200])
grid off
set(gca,'color','none')
axis off

