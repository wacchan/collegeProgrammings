common_initialization;
t=0;
nMax=1;
E_2_2_sfos;
for nn=1:nMax
    Update_Ex_for_free_boundary; % Ex �̍X�V
    Update_Ey_for_free_boundary; % Ey �̍X�V
    Update_Ez_for_free_boundary; % Ez �̍X�V
    E_2_2_AuEf; % �d�E�̒ǉ��̍X�V
    t=t+ht/2;
    Update_H_field; %���E�̍X�V
    t=t+ht/2;
end

Emax = 1;
tau = 1/(2.5*10.^9);
t = 0:tau/100:3*tau;
Ez = Emax*exp(-(4*(t-tau)/tau).^2);
plot(t,EEz(1:length(t)),'b');