%Differentials plot3

x = linspace(-1,2,20);
y = exp(x);
dy = diffxy(x,y);
dy2 = diffxy(x,dy);  % Or, could use >> dy2 = diffxy(x,y,[],2);
figure('Color','white');
plot(x,(y-dy)./y,'b*',x,(y-dy2)./y,'b^')

Dy = gradient(y)./gradient(x);
Dy2 = gradient(Dy)./gradient(x);
hold on
plot(x,(y-Dy)./y,'r*',x,(y-Dy2)./y,'r^')
title('Relative error in derivative approximation')
legend('diffxy: dy/dx','diffxy: d^2y/dx^2',...
       'gradient: dy/dx','gradient: d^2y/dx^2')
hold off

