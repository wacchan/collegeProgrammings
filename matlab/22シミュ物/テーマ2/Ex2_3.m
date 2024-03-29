x = [0.50; 1.00; 1.50; -1.00];
ma = 2.00;
mb = 1.00;
l = 2.00;
k = 1.00;

xmax = 20;
h = 0.0001;
t = 0:h:xmax;
[t,z] = ode45(@xdot,t,x,'',k,l,ma,mb);

p = ma.*z(:,2)+mb.*z(:,4);%�S�^����
e = (ma.*z(:,2).^2+mb.*z(:,4).^2+k*(z(:,3)-z(:,1)-l).^2)/2;

subplot(1,2,1);
plot(t,z(:,1),t,z(:,3),'r');
subplot(1,2,2);
plot(t,p,t,e,'r');
axis([0 20 -1 10]);