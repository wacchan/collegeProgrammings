x=-2:0.1:2;
y=-3:0.1:3;

numx=length(x);
numy=length(y);
Z=zeros(numy,numx);


for i=1:numy
   baseZ=(x+y(i)).*exp(-x.^2-y(i).^2);
    Z(i,:)=baseZ;
end
baseSURF=surf(x,y,Z);
axis([-3 3 -3 3 -7 7]);
get(gca,'sortmethod');
for t=0.1:0.1:10
    v=5*sin(pi*t);
    
    for i=1:numy
         baseZ=(x+y(i)+v).*exp(-x.^2-y(i).^2);

        Z(i,:)=baseZ;
    end
    set(baseSURF,'zdata',Z);
    drawnow;
end
