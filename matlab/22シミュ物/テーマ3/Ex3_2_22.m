%�p�����[�^�Z�b�g
N=32;
h=1/N;
x=0+h:h:1;
v=5;

%r�̑I��(�ǂ��炩����̃R�����g���O������)
r=1/2;
%r=1/6;

%�s��̍쐬
y=zeros(N-1,1);
ny=zeros(N-1,1);

%�����l��`
for i=1:length(x)-1
  y(i)=exp((5*x(i))/2)*sin(pi*x(i));
end

%�����@����
for n = 0:r*h^2:1
    ny(1)=y(1)+(r*(y(2)-2*y(1))-((r*h*v)/2)*(y(2)));
    for i=2:N-2
        ny(i)=y(i)+r*(y(i+1)-2*y(i)+y(i-1))-(((r*h*v)/2)*(y(i+1)-y(i-1)));
    end
    ny(N-1)=y(N-1)+(r*(-2*y(N-1)+y(N-2))+(((r*h*v)/2)*y(N-2)));
    y=ny;
end


Xt=0:0.01:1;
Yt=exp(5*Xt/2-(25/4+pi^2)).*sin(pi*Xt);
plot(x(1:31),y(:,length(n)),Xt,Yt)