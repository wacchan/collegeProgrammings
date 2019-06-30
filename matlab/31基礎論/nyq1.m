syms s ans1;
eqn=s^2+2*s-5;
sols=solve(eqn, s);

eqnans=(1+10/(ans1*ans1+2*ans1-5));
solans=solve(eqnans, ans1);

hold on
grid on

a=[0 0];
scatter(sols, imag(sols));
scatter(solans, imag(solans));
legend('-1Å}Å„6','ans');
s=tf('s');
sys=tf(10/(s*s+2*s-5));
nyquist(sys);