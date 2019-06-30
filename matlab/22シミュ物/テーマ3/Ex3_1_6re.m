N = 32;
h = 1/N;
x = 0:h:1;

r = 1/2;
%r = 1/6;

y = zeros(length(x), 1);

for i=1:length(x)
    y(i) = sin(pi*x(i));
end

for n = 0:r*h^2:1
    y(2:N) = y(2:N)+r*(y(3:N+1)-2*y(2:N)+y(1:N-1));
end

X = 0:0.01:1;
Y = exp(-pi^2).*sin(pi*X);

plot(x, y, X, Y);