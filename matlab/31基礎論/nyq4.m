syms s a3;

eqns=s*(s+5)*(0.1*s+1)*(s-1)^4;
sols=solve(eqns, s);

eqnans=1+ ( (10*a3^3)/ ( a3*(a3+5)*(0.1*a3+1)*(a3-1)^4 ) );
solans=solve(eqnans, a3);

grid on
hold on

scatter(sols, imag(sols));
scatter(solans, imag(solans));
axis([-13 5 -5 5]);
legend('pc', 'ans');
s=tf('s');
sys=tf(( (10*s^3)/ ( s*(s+5)*(0.1*s+1)*(s-1)^4 ) ));
nyquist(sys);