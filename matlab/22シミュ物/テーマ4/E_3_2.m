common_initialization;
t=0;
nMax=1;
E_3_2_sfos;
for nn=1:nMax
    Update_Ex_for_free_boundary; % Ex �̍X�V
    Update_Ey_for_free_boundary; % Ey �̍X�V
    Update_Ez_for_free_boundary; % Ez �̍X�V
    E_3_2_AuEf; % �d�E�̒ǉ��̍X�V
    t=t+ht/2;
    Update_H_field; %���E�̍X�V
    t=t+ht/2;
end

Vmax = 100*10.^(-3)/32;
tau = 1/(2.5*10.^9);
t=0:tau/100:2*tau;
Vt=Vmax*exp(-(4*(t-tau)/tau).^2);
plot(t,Vt,'r',t,EEz(1:length(t)),'b');