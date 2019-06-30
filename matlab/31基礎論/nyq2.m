syms s ans2;
eqn=(s+1)*(s+10)*s==0;
sols=solve(eqn, s);

%eqnans2=1 + ( (20* (ans2^2+ans2+0.5) ) / ( (ans2+1) * (ans2+10) *ans2) ) ==0 ;
eqnans2=ans2^3 + 31*ans2^2 + 30*ans2 + 10==0;
solans=solve(eqnans2, ans2);

hold on
grid on

axis([-2 2 -2 2]);
scatter(sols, imag(sols));
scatter(solans, imag(solans));
legend('','ans');
s=tf('s');
sys=tf( (20*(s^2+s+0.5)) / ((s+1)*(s+10)*s) );
nyquist(sys);