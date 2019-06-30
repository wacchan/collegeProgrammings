syms x;
eqn1=x^5+15*x^4+85*x^3+225*x^2+274*x+120==0;
solx=solve(eqn1, x);


hold on
grid on
axis([-10 10 -10 10]);
a=[0 0];
plot(a,[-100 100]);
plot([-100 100], a);
scatter(solx, [0 1 2 3 4]);
legend('y', 'x','1');