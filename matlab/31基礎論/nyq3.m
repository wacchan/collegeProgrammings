%ˆÀ’è
syms s a3;

eqns=s^2*(s+5)*(0.1*s+1);
sols=solve(eqns, s);

eqnans=1+ ( (10)/ ( a3^2*(a3+5)*(0.1*a3+1) ) );
solans=solve(eqnans, a3);

grid on
hold on

scatter(sols, imag(sols));
scatter(solans, imag(solans));
axis([-13 5 -5 5]);
legend('pc', 'ans');
s=tf('s');
sys=tf(( (10)/ ( s^2*(s+5)*(0.1*s+1) ) ));
nyquist(sys);