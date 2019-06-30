
mx = 17;
my15=32;
mz=17;

if nn ==1
    tilEz(iEz,my15,kEz) = tilEz(iEz,my15,kEz) + (exp(-(4*(t-tau)/tau)^2));
elseif nn > 1 && nn < 2*nMax/3
    %tilEz(:,16,:) = tilEz(:,16,:) + ((exp(-(4*(t-tau)/tau).^2)*ones(Nx1,1,Nz))-(exp(-(4*(t-ht-tau)/tau).^2)*ones(Nx1,1,Nz)));
    tilEz(iEz,my15,kEz) = tilEz(iEz,my15,kEz) + exp(-(4*(t-tau)/tau)^2) - exp(-(4*(t-ht-tau)/tau)^2);
end
%EEz(nn)=tilEz(1,16,1);
EEz(nn)=tilEz(mx,my15,mz);