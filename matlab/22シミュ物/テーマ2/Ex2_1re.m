x = [0.5; 0; 1.5; 0]; %(3)
%x = [0.5; 0; 1; 0];  %(4)
%x = [0.5; 0.5; 1; -0.5];  %(5)
ma = 1;
mb = 1;
l = 2;
k = 1;
xmax = 20;
h = 0.0001;
t = 0:h:xmax;
[t,z] = ode45(@xdot,t,x,'',k,l,ma,mb);
plot(t,z(:,1),t,z(:,3),'r');
axis([0 20 -1 3]);

zwide1 = wide(z(:,1));
zwide3 = wide(z(:,3));5;

zdist = distance([z(:,1), z(:,3)]);

ztemp1 = tempo(z(:,1),1/h);
ztemp3 = tempo(z(:,3),1/h);

X = ['xa(t)‚ÌU• ', num2str(zwide1), ', üŠú ', num2str(ztemp1)];
X2 = ['xb(t)‚ÌU• ', num2str(zwide3), ', üŠú ', num2str(ztemp3)];
X3 = ['’†SŠÔ‚Ì‹——£', num2str(zdist)];

disp(X);
disp(X2);
disp(X3);