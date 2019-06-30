function x4out = x4dot(t, x, mu, m, g, r, a)
n = 3*m*g*r*(mu*cos(a)-sin(a)/3)*(1-exp(-180/(110-x(1))))/2;
xdot1 = x(2);
xdot2 = 2*g*sin(a)/3 - 2*n/(3*m*r);
x4out = [xdot1; xdot2];