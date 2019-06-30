N = 32;
h = 1/N;
x = 0+h:h:1;

%r = 1/2;
r = 1/6;

y = zeros(N-1, 1);
ny = zeros(N-1, 1);

for i=1:length(x)-1
    y(i) = sin(pi*x(i));
end

for n = 0:r*h^2:1
    ny(1) = y(1)+r*(y(2)-2*y(1));
        ny(2:N-2) = y(2:N-2)+r*(y(3:N-1)-2*y(2:N-2)+y(1:N-3));
    ny(N-1) = y(N-1)+r*(-2*y(N-1)+y(N-2));
    y = ny;
end

X = 0:0.01:1;
Y = exp(-pi^2).*sin(pi*X);

plot(x(1:31), y(:,length(n)),X,Y);