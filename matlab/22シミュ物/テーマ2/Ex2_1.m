%x = [0.5; 1.0; 1.5000; -1.0];
x = [0; 0; 2; 0];
ma = 1;
mb = 1;
l = 2;
k = 1;
t = 0:0.0001:20;
[t,z] = ode45(@xdot,t,x,'',k,l,ma,mb);
plot(t,z(:,1),t,z(:,3),'r');
axis([0 20 -0.5 2.5]);

zmin = min(z);
zmax = max(z);
zwide1 = abs(zmax(1)-zmin(1));
zwide1 = round(zwide1, 3,'significant');
zwide3 = abs(zmax(3)-zmin(3));
zwide3 = round(zwide3, 3,'significant');

zdist = abs( (zmax(1)+zmin(1))/2 - (zmax(3)+zmin(3))/2 );
zdist = round(zdist, 3,'significant');

zlmax1 = ilocalmax(z(:,1));
zlocalm1 = find(zlmax1(:, 1));
ztemp1 = abs(zlocalm1(2)-zlocalm1(3))/10000;
ztemp1 = round(ztemp1, 3,'significant');

zlmax3 = ilocalmax(z(:, 3));
zlocalm3 = find(zlmax3(:, 1));
ztemp3 = abs(zlocalm3(2)-zlocalm3(3))/10000;
ztemp3 = round(ztemp3, 3,'significant');

X = ['xa(t)‚ÌU• ', num2str(zwide1), ', üŠú ', num2str(ztemp1)];
X2 = ['xb(t)‚ÌU• ', num2str(zwide3), ', üŠú ', num2str(ztemp3)];
X3 = ['’†SŠÔ‚Ì‹——£', num2str(zdist)];

disp(X);
disp(X2);
disp(X3);