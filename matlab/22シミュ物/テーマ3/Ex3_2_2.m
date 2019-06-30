N = 32;
h = 1/N;
x = 0:h:1;
v = 5;

r = 1/2;
%r = 1/6;

y = zeros(length(x), 1);
ny = zeros(length(x), 1);

for i=1:length(x)-1
    y(i) = exp((v*x(i))/2)*sin(pi*x(i));
end

for n = 0:r*h^2:1
    y(2:N) = y(2:N)+(r*(y(1:N-1)-2*y(2:N)+y(3:N+1))-(((r*h*v)/2)*(y(3:N+1)-y(1:N-1))));
end

Xt = 0:0.01:1;
Yt = exp(5*Xt/2-(25/4+pi^2)).*sin(pi*Xt);

plot(x, y,'r',Xt,Yt);