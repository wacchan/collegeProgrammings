function yout = ydot(t,y)
n = 32;
h = 1/n;
a = zeros(n-1,n-1);
for i=1:n-1
    a(i,i) = -2/(h^2);
end
for i=1:n-2
    a(i+1,i) = 1/(h^2);
    a(i,i+1) = 1/(h^2);
end
yout = a*y;