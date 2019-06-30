if nn > 1 && nn < 2*nMax/3
    tilEz(:,16,:) = tilEz(:,16,:) + ((exp(-(4*(t-tau)/tau).^2)*ones(Nx1,1,Nz))-(exp(-(4*(t-ht-tau)/tau).^2)*ones(Nx1,1,Nz)));
end
EEz(nn)=tilEz(1,16,1);