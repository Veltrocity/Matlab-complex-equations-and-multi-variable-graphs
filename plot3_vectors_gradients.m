%plot3 VECTORS

x = 1:10;
disp(x);

fx =  gradient(x);

x = -2:0.2:2;
y = x';
z = x .* exp(-x.^2 - y.^2);
[px,py] = gradient(z);

figure
contour(x,y,z)
hold on
quiver(x,y,px,py)
hold off

%phase 1; 2d plot

y = sin(-1:0.25:0.5);
yp = gradient(y,0.25);
y_guess = y(end) + yp(end)*(0.5005 - 0.5)
y_actual = sin(0.5005)

x = -3:0.2:3;
y = x';
f = x.^2 .* y.^3;
surf(x,y,f)
xlabel('x')
ylabel('y')
zlabel('z')

%phase 2 3d plot, looks pretty




