%Fractal take 1, bare with me

c = imread('dla.gif');
imagesc(~c)
colormap gray
axis square

c = imread('Apollonian_gasket.gif');
c = (c<198);
imagesc(~c)
colormap gray
axis square
figure
boxcount(c)
figure
boxcount(c,'slope')

%need more libs and directories
%Doesnt work