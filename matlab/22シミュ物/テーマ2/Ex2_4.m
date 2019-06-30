x = [0; 10];
mu = 0.5;
m = 10;
g = 9.81;
r = 0.5;
a = pi/8;

tmax = 20;
h = 0.0001;
t = 0:h:tmax;
[t, z] = ode45(@x4dot, t, x, '', mu, m, g, r, a);
zzero = z(:, 2) < 0;
zzero2 = find(zzero);
zstop = abs(zzero2(1) - 0)*h;
zstop2 = round(zstop, 3,'significant');
zdist = round(z(zzero2(1),1), 3,'significant');
X = ['’âŽ~‚·‚é‚Ü‚Å@ ', num2str(zstop2), ', ‹——£ ', num2str(zdist)];
disp(X);
plot(t,z);
