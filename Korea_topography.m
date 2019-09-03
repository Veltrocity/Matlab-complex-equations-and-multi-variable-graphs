%testing loading in world geogrpahy and checking geoid and loading 'korea"

load (korea);
[klat,klon] = meshgrat(map,refvec);

[cmap,clim] = demcmap(map);

axesm('miller','MapLatLimit',[30 45],'MapLonLimit',[115 135]);
tightmap
surflsrm(klat,klon,map,[-130 50],cmap,clim)


























