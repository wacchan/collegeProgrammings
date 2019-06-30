r = [16000; 0; 0; 0.9];
gm = 5050000000000;
rmax = 20;
h = 0.0001;
t = 0:h:rmax;
[t,z] = ode45(@rdot,t,r,'',gm);
temp = tempo(cos(z(:, 3)),1/h);
dis1 = ['üŠúF@', num2str(temp)];
disp(dis1);

onetemp = 0:h:temp;
x = z(:, 1).*cos(z(:, 3));
y = z(:, 1).*sin(z(:, 3));
plot(x,y,'');