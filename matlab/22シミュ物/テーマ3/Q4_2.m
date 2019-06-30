N=32;
h=1/N;
i=0:32;
x=i*h;
z0=sin(pi*x);
r=1/2;
v=5;
dt=1/(r*h^2);
t=(1/dt:(1/dt):1);
true=exp((v.*x)/2-((v^2)/4+pi^2)).*sin(pi.*x);

yVec=exp(v.*x.*1/2).*sin(pi*x);
yNewVec=zeros(33,1);
n=1:length(t);

for n=1:length(t)
    yNewVec(2)=yVec(2)+r*(yVec(3)-2*yVec(2)+yVec(1))-v*(1/2)*(h)*r*(yVec(3)-yVec(1));
    yNewVec(3:N-1)=yVec(3:N-1)+r*(yVec(2:N-2)-2*yVec(3:N-1)+yVec(4:N))-v*(1/2)*(h)*r*(yVec(4:N)-yVec(2:N-2));
    yNewVec(N)=yVec(N)+r*(yVec(N-1)-2*yVec(N)+yVec(N+1))-v*(1/2)*(h)*r*(yVec(N+1)-yVec(N-1));
    yVec=yNewVec; 
end
yVec(1)=0;
yVec(N+1)=0;

subplot(1,3,1);
plot(x,yVec,x,true);
subplot(1,3,2);
plot(x,yVec);
subplot(1,3,3);
plot(x,true);