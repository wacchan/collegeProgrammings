syms x y z ;
eqn1=x^2+8*x+3==0;
solx=solve(eqn1, x);

eqn2=y^2-3*y+7==0;
soly=solve(eqn2, y);

eqn3=z^2+1==0;
solz=solve(eqn3, z);

hold on
grid on
axis([-10 10 -10 10]);
a=[0 0];
plot(a,[-100 100]);
plot([-100 100], a);
scatter(solx, [0 1]);
scatter(soly, [0 1]);
scatter(solz, [0 1]);
legend('y', 'x','1','2','3');