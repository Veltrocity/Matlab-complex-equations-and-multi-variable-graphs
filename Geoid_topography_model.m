% %geoid models, with meshgrid
% 
% figure('Color','white')
% load geoid;
% contour3m(geoid,geoidrefvec,50,'LineColor','black');
% 
% hold on
% geoshow(geoid,geoidrefvec,'DisplayType','surface');
% 
% title('EGM96 Global Geoid Heights with 50 Contour Levels');
% 
% view(3)

load geoid 
load coastlines
figure; 
axesm robinson
geoshow(geoid,geoidlegend,'DisplayType','texturemap')
colorbar('southoutside')
geoshow(coastlat,coastlon,'color','k')

