common_initialization;
t=0;
nMax=1;
E_3_2_sfos;
for nn=1:nMax
    Update_Ex_for_free_boundary; % Ex の更新
    Update_Ey_for_free_boundary; % Ey の更新
    Update_Ez_for_free_boundary; % Ez の更新
    E_3_2_AuEf; % 電界の追加の更新
    t=t+ht/2;
    Update_H_field; %磁界の更新
    t=t+ht/2;
end

Vmax = 100*10.^(-3)/32;
tau = 1/(2.5*10.^9);
t=0:tau/100:2*tau;
Vt=Vmax*exp(-(4*(t-tau)/tau).^2);
plot(t,Vt,'r',t,EEz(1:length(t)),'b');