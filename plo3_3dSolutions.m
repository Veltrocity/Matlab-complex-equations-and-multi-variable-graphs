%plot3 amd various gradients

pdeplot3D(model,'ColorMapData',u)

model = createpde(2);
importGeometry(model,'Tetrahedron.stl');
pdegplot(model,'FaceLabels','on','FaceAlpha',0.5)
view(-40,24)

applyBoundaryCondition(model,'dirichlet','face',4,'u',[0,0]);

f = [1;10];
a = 0;
c = [2;0;4;1;3;8;1;0;2;1;2;4];
specifyCoefficients(model,'m',0,'d',0,'c',c,'a',a,'f',f);

generateMesh(model);

results = solvepde(model);
u = results.NodalSolution;

pdeplot3D(model,'ColorMapData',u(:,1))
view(-175,4)
title('u(1)')

figure
pdeplot3D(model,'ColorMapData',u(:,2))
view(-175,4)
title('u(2)')